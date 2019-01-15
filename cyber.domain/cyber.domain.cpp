#include "cyber.domain.hpp"
#include <cyber.system/cyber.system.hpp>
#include <cyber.token/cyber.token.hpp>
#include <eosiolib/eosio.hpp>
#include <eosiolib/transaction.hpp>
#include <eosiolib/dispatcher.hpp>

#include "domain_validate.cpp"

namespace eosiosystem {


// constants
const uint32_t seconds_per_hour      = 60 * 60;
// const uint32_t seconds_per_day       = 24 * seconds_per_hour;    // declared in eosio::system header…
const uint32_t seconds_per_year      = 365 * seconds_per_day;   // note: it's 52*7=364 in eos

// config
const uint32_t checkwin_interval = seconds_per_hour;
const uint32_t min_time_from_last_win = seconds_per_day;
const uint32_t min_time_from_last_bid = seconds_per_day;

using namespace eosio;

void validate_domain_name(const domain_name& n);
void validate_username(const username& n);


symbol core_symbol() {
    // const static auto sym = system_contract::get_core_symbol();  // requires system contract, which is not ready yet
    const static auto sym = symbol("SYS", 4);
    return sym;
}

void domain::checkwin() {
    require_auth(_self);
    const int64_t now = ::now();                // int64 to prevent overflows (can only happen if something broken)
    auto tnow = time_point_sec(now);

    auto state = state_singleton(_self, _self.value);
    bool exists = state.exists();
    auto s = exists ? state.get() : domain_bid_state{tnow, tnow};
    if (exists) {
        auto diff = now - s.last_checkwin.utc_seconds;
        eosio_assert(diff >= 0, "SYSTEM: last_checkwin is in future");  // must be impossible
        if (diff != checkwin_interval) {
            eosio_assert(diff > checkwin_interval, "checkwin called too early");
            print("checkwin delayed\n");
        }
        if (now - s.last_win.utc_seconds > min_time_from_last_win) {
            domain_bid_tbl bids(_self, _self.value);
            auto idx = bids.get_index<"highbid"_n>();
            auto highest = idx.begin();
            if (highest != idx.end() &&
                highest->high_bid > 0 &&
                now - highest->last_bid_time.utc_seconds > min_time_from_last_bid
            ) {
                s.last_win = tnow;
                idx.modify(highest, same_payer, [&](auto& b) {
                    b.high_bid = -b.high_bid;
                });
            }
        }
        s.last_checkwin = tnow;
    }
    state.set(s, _self);

    print("schedule next\n");
    auto sender_id = s.last_checkwin.utc_seconds;
    transaction tx;
    tx.actions.emplace_back(action{permission_level(_self, active_permission), _self, "checkwin"_n, std::tuple<>()});
    tx.delay_sec = checkwin_interval;
    tx.send(sender_id, _self);
}


void domain::biddomain(name bidder, const domain_name& name, asset bid) {
    require_auth(bidder);
    validate_domain_name(name);
    eosio_assert(!is_domain(name), "domain already exists");
    eosio_assert(bid.symbol == core_symbol(), "asset must be system token");
    eosio_assert(bid.amount > 0, "insufficient bid");

    INLINE_ACTION_SENDER(eosio::token, transfer)(
        token_account, {{bidder, active_permission}},
        {bidder, names_account, bid, std::string("bid domain ") + name}
    );

    domain_bid_tbl bids(_self, _self.value);
    print(bidder, " bid ", bid, " on ", name, "\n");

    const auto set_bid = [&](auto& b) {
        b.high_bidder = bidder;
        b.high_bid = bid.amount;
        b.last_bid_time = time_point_sec{::now()};
    };
    auto idx = bids.get_index<"domain"_n>();
    auto current = idx.find(name);
    if (current == idx.end()) {
        bids.emplace(bidder, [&](auto& b) {
            b.id = bids.available_primary_key();
            b.domain = name;
            set_bid(b);
        });
    } else {
        eosio_assert(current->high_bid > 0, "this auction has already closed");
        eosio_assert((bid.amount - current->high_bid)*10 >= current->high_bid, "must increase bid by 10%");
        eosio_assert(current->high_bidder != bidder, "account is already highest bidder");

        // the scope was newname.value, but we have string, so simplify.
        // downside: refund sum can be accumulated over several domains
        domain_bid_refund_tbl refunds(_self, _self.value);
        auto to_refund = asset(current->high_bid, core_symbol());
        auto itr = refunds.find(current->high_bidder.value);
        if (itr != refunds.end()) {
            refunds.modify(itr, same_payer, [&](auto& r) {
                r.amount += to_refund;
            });
        } else {
            refunds.emplace(bidder, [&](auto& r) {
                r.bidder = current->high_bidder;
                r.amount = to_refund;
            });
        }

        transaction tx;
        tx.actions.emplace_back(permission_level{_self, active_permission},
            _self, "biddmrefund"_n, std::make_tuple(current->high_bidder, name)
        );
        tx.delay_sec = 0;
        uint128_t deferred_id = current->high_bidder.value; // note: high 64 bits was newname.value
        cancel_deferred(deferred_id);
        tx.send(deferred_id, bidder);

        idx.modify(current, bidder, set_bid);
    }
}

// note: domain name is only used for transfer memo
void domain::biddmrefund(name bidder, const domain_name& name) {
    domain_bid_refund_tbl refunds(_self, _self.value);  // the scope was newname.value, but we have string, so simplify
    auto itr = refunds.find(bidder.value);
    eosio_assert(itr != refunds.end(), "refund not found");
    INLINE_ACTION_SENDER(eosio::token, transfer)(
        token_account, {{names_account, active_permission}, {bidder, active_permission}},
        {names_account, bidder, asset(itr->amount), std::string("refund bid on domain ")+name}
    );
    refunds.erase(itr);
}

// name is already validated at this point
void domain_native::newdomain(name creator, const domain_name& name) {
    if (creator != _self) {
        auto dot = name.find('.');
        bool tld = dot == std::string::npos;    // Top Level Domain; TODO: decide what to do with SLD
        if (tld) {
            // auction
            domain_bid_tbl bids(_self, _self.value);
            auto idx = bids.get_index<"domain"_n>();
            auto bid = idx.find(name);
            eosio_assert(bid != idx.end(), "no active bid for domain");
            eosio_assert(bid->high_bidder == creator, "only highest bidder can claim");
            eosio_assert(bid->high_bid < 0, "auction for domain is not closed yet");
            idx.erase(bid);
        } else {
            // only domain owner can create subdomains
            const domain_name suffix = name.substr(dot+1, name.size()-dot-1);
            eosio_assert(is_domain(suffix), "parent domain do not exists");
            eosio_assert(creator == get_domain_owner(suffix), "only owner of parent domain can create subdomain");
        }
    }
}

// TODO: std::map to ensure unique?
void domain::declarenames(const std::vector<name_info>& domains) {
    eosio_assert(domains.size(), "declarenames don't accept empty list");
    std::vector<domain_name> prev;
    for (const auto& info: domains) {
        const auto& domain = info.domain;
        const auto& dacc = info.account;
        // TODO: it's handy to have domain name in assert messages
        validate_domain_name(domain);
        eosio_assert(std::find(prev.begin(), prev.end(), domain) == prev.end(), "same domain declared several times");
        eosio_assert(is_domain(domain), "domain don't exists");
        eosio_assert(dacc == resolve_domain(domain), "domain resolves to different account");
        prev.push_back(domain);
        for (const auto& u: info.users) {
            validate_username(u);
            eosio_assert(is_username(dacc, u), "username don't exists in domain");
        }
    }
}

} // eosiosystem


EOSIO_DISPATCH(eosiosystem::domain,
    (newdomain)(checkwin)(biddomain)(biddmrefund)(declarenames)
)
