#pragma once
#include "util.hpp"
#include <eosiolib/eosio.hpp>
#include <variant>

namespace cyber {


using namespace eosio;

template<typename T, int L>
struct param_wrapper: T {
    param_wrapper() = default;
    param_wrapper(T& x): T(x) {};
    param_wrapper(T&& x): T(std::move(x)) {};
    operator T() { return this; }
};


// Base to inherit other parameters
struct parameter {

    // validates parameter value(s), throws assert if invalid
    virtual void validate() const {};

    // returns true if parameter can't be changed after initialization; TODO: must not present in local witness params
    virtual bool immutable() const { return false; }

    // NOTE: the following fields are unused now, `golos.config` will need them later
    // compares parameters to use in median calculation
    // returns true by default, which means no comparer set, override if can use median
    virtual bool operator<(const parameter& other) const { return true; };

    // used to detect is parameter can be used in median.
    // by default checks if default comparer set, this means parameter can't be used in median
    virtual bool can_median() const { return !(*this < *this); }
};

struct immutable_parameter: parameter {
    bool immutable() const override {
        return true;
    }
};

struct param_helper {

    template<typename T>
    static void check_params(const std::vector<T>& params, bool initialized) {
        eosio::print("check_params, size: ", params.size(), "\n");
        eosio_assert(params.size(), "empty params not allowed");
        check_duplicates(params);
        eosio::print("check_params: no dups\n");
        if (initialized) {
            check_immutables(params);
            eosio::print("check_params: all mutable\n");
        }
        validate_params(params);
        eosio::print("check_params: valid\n");
    }

    template<typename T>
    static void check_immutables(const std::vector<T>& params) {
        for (const auto& param: params) {
            std::visit([](const parameter& p) {
                eosio_assert(!p.immutable(), "can't change immutable parameter");
            }, param);
        }
    }

    template<typename T>
    static void validate_params(const std::vector<T>& params) {
        for (const auto& param: params) {
            std::visit([](const parameter& p) {
                p.validate();
            }, param);
        }
    }

    template<typename T>
    static void check_duplicates(const std::vector<T>& params) {
        using idx_type = decltype(params[0].index());
        idx_type prev_idx = 0;
        bool first = true;
        for (const auto& p: params) {
            auto i = p.index();
            if (!first) {
                eosio_assert(i > prev_idx, i < prev_idx
                    ? "parameters must be ordered by variant index"
                    : "params contain several copies of the same parameter");
            }
            prev_idx = i;
            first = false;
        }
    }

    /**
     * Validate and store contract parameters using visitor
     *
     * @brief helper to store parameters to state singleton
     * @tparam V - type of visitor (inherited from set_params_visitor)
     * @tparam T - type of parameters variant
     * @param params - vector of parameters
     * @param singleton - storage singleton to read from and write to
     * @param ram_payer - account, who pays for storage (usually contract._self)
     * @returns - constructed setter visitor if needed for further processing
     */
    template<typename V, typename T, typename S>
    static V set_parameters(std::vector<T> params, S& singleton, name ram_payer) {
        using state_type = decltype(singleton.get());
        auto update = singleton.exists();
        eosio_assert(update || params.size() == state_type::params_count, "must provide all parameters in initial set");
        check_params(params, update);

        auto s = update ? singleton.get() : state_type{};
        auto setter = V(s);
        bool changed = false;
        for (const auto& param: params) {
            changed |= std::visit(setter, param);   // why we have no ||= ?
        }
        eosio_assert(changed, "at least one parameter must change");    // don't add actions, which do nothing
        singleton.set(setter.state, ram_payer);
        return setter;
    }


    template<typename T>
    static T get_median(std::vector<T>& params) {
        auto l = params.size();
        eosio_assert(l > 0, "empty params not allowed");
        T r = params[0];
        eosio_assert(r.can_median(), "parameter can't be used as median");   // must not normally happen
        if (l > 1) {
            std::nth_element(params.begin(), params.begin() + l / 2, params.end());
            r = params[l / 2];
        }
        return r;
    }

    template<typename T>
    static bool have_majority(const std::vector<T>& params, size_t req_count, T& major) {
        auto l = params.size();
        eosio_assert(l > 0, "empty params not allowed");
        // eosio_assert(l >= req_count, "req_count is too large to reach");
        if (l < req_count) {
            return false; //req_count is too large to reach
        }
        eosio_assert(l/2 + 1 <= req_count, "req_count is too small, it must be at least 50%+1");
        std::map<T,int> same;
        int max_count = -1;
        T max_value;
        for (const auto& p: params) {
            auto count = same[p];
            count++;
            same[p] = count;
            if (count > max_count) {
                max_count = count;
                max_value = p;
                if (count >= req_count) {
                    major = max_value;
                    return true;
                }
            }
            if (l + max_count < req_count) {
                return false;   // no chance to reach req_count
            }
            l--;
        }
        return false;
    }

    // TODO: add selection: median/majority/orher
    template<typename T, typename S, typename F>
    static bool recalculate_state(T& top, S& state, F field, int threshold) {
        using ParamType = typename member_pointer_info<F>::value_type;
        std::vector<ParamType> param_top(top.size());
        std::transform(top.begin(), top.end(), param_top.begin(), [&](const auto& p) {
            return p.*field;
        });
        ParamType major;
        bool majority = param_helper::have_majority(param_top, threshold, major);
        if (majority && major != state.*field) {
            state.*field = major;
            return true;
        }
        return false;
    }

    /**
     * Get contract parameters, individually set by top witnesses
     *
     * @brief helper to obtain top parameters to calculate median or majority value
     * @tparam Tbl - multi-index table, where parameters stored. Must be singleton
     * @tparam Item - type of parameters struct
     * @param code - contract to get parameters for
     * @param top - top witnesses
     */
    template<typename Tbl, typename Item>   // TODO: Item can be derived from Tbl
    static std::vector<Item> get_top_params(name code, const std::vector<name>& top) {
        std::vector<Item> r;
        for (const auto& w: top) {
            Tbl p{code, w.value};           // NOTE: convention to store parameters in account scope
            if (p.exists())
                r.emplace_back(p.get());
        }
        return r;
    }

};

/**
 * Base for visitors to update parameters struct
 *
 * @brief add operator() for each parameter type and call `set_param` to do all common stuff
 * @tparam T - parameters struct type
 */
template<typename T>
struct set_params_visitor {
    T& state;
    bool no_same;   // disallows setting same parameter value

    set_params_visitor(T& s, bool fail_on_same = false): state(s), no_same(fail_on_same) {}

    template<typename P, typename F>
    bool set_param(const P& value, F field) {
        bool changed = state.*field != value;
        if (no_same) {
            eosio_assert(changed, "can't set same parameter value");   // TODO: add parameter name to assert message
        }
        if (changed) {
            state.*field = value;
        }
        return changed;
    }
};

// TODO: combine both visitors to reduce boilerplate required to write in contract
/**
 * Base for visitors to recalculate parameters state
 *
 * @brief add operator() for each parameter type
 * @tparam T - global storage type
 */
template<typename T>
struct state_params_update_visitor {
    T& state;
    const std::vector<T>& top;
    bool changed = false;

    state_params_update_visitor(T& s, const std::vector<T>& t): state(s), top(t) {}

    template<typename F>
    void update_state(F field, int threshold) {
        bool ch = param_helper::recalculate_state(top, state, field, threshold);
        if (ch) {
            changed = true;
        }
    }
};


} // commun
