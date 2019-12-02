#include <eosio.system/eosio.system.hpp>
#include <math.h>

namespace eosiosystem {

void system_contract::adjust_resources(name payer, name account, symbol core_symbol, int64_t net_delta,
                                       int64_t cpu_delta, bool must_not_be_managed) {
   if (!net_delta && !cpu_delta)
      return;

   user_resources_table totals_tbl(get_self(), account.value);
   auto                 tot_itr = totals_tbl.find(account.value);
   if (tot_itr == totals_tbl.end()) {
      tot_itr = totals_tbl.emplace(payer, [&](auto& tot) {
         tot.owner      = account;
         tot.net_weight = asset{ net_delta, core_symbol };
         tot.cpu_weight = asset{ cpu_delta, core_symbol };
      });
   } else {
      totals_tbl.modify(tot_itr, same_payer, [&](auto& tot) {
         tot.net_weight.amount += net_delta;
         tot.cpu_weight.amount += cpu_delta;
      });
   }
   check(0 <= tot_itr->net_weight.amount, "insufficient staked total net bandwidth");
   check(0 <= tot_itr->cpu_weight.amount, "insufficient staked total cpu bandwidth");

   {
      bool ram_managed = false;
      bool net_managed = false;
      bool cpu_managed = false;

      auto voter_itr = _voters.find(account.value);
      if (voter_itr != _voters.end()) {
         ram_managed = has_field(voter_itr->flags1, voter_info::flags1_fields::ram_managed);
         net_managed = has_field(voter_itr->flags1, voter_info::flags1_fields::net_managed);
         cpu_managed = has_field(voter_itr->flags1, voter_info::flags1_fields::cpu_managed);
      }

      if (must_not_be_managed)
         eosio::check(!net_managed && !cpu_managed, "something is managed which shouldn't be");

      if (!(net_managed && cpu_managed)) {
         int64_t ram_bytes, net, cpu;
         get_resource_limits(account, ram_bytes, net, cpu);
         set_resource_limits(
               account, ram_managed ? ram_bytes : std::max(tot_itr->ram_bytes + ram_gift_bytes, ram_bytes),
               net_managed ? net : tot_itr->net_weight.amount, cpu_managed ? cpu : tot_itr->cpu_weight.amount);
      }
   }

   if (tot_itr->is_empty()) {
      totals_tbl.erase(tot_itr);
   }
} // system_contract::adjust_resources

void system_contract::process_rentbw_queue(symbol core_symbol, rentbw_state& state, rentbw_order_table& orders,
                                           uint32_t max_items) {
   time_point_sec now       = eosio::current_time_point();
   auto           idx       = orders.get_index<"byexpires"_n>();
   int64_t        total_net = 0;
   int64_t        total_cpu = 0;
   while (max_items--) {
      auto it = idx.begin();
      if (it == idx.end() || it->expires > now)
         break;
      total_net = it->net_weight;
      total_cpu = it->cpu_weight;
      adjust_resources(get_self(), it->owner, core_symbol, -it->net_weight, -it->cpu_weight);
      idx.erase(it);
   }
   state.net.utilization -= total_net;
   state.cpu.utilization -= total_cpu;
   adjust_resources(get_self(), reserv_account, core_symbol, total_net, total_cpu, true);
}

void update_weight(time_point_sec now, rentbw_state_resource& res) {
   if (now >= res.target_timestamp)
      res.weight = res.target_weight;
   else
      res.weight = res.initial_weight + //
                   int128_t(res.target_weight - res.initial_weight) *
                         (now.utc_seconds - res.initial_timestamp.utc_seconds) /
                         (res.target_timestamp.utc_seconds - res.initial_timestamp.utc_seconds);
}

void update_utilization(time_point_sec now, rentbw_state_resource& res) {
   if (res.utilization >= res.adjusted_utilization)
      res.adjusted_utilization = res.utilization;
   else
      res.adjusted_utilization = //
            res.utilization +
            (res.adjusted_utilization - res.utilization) *
                  exp((now.utc_seconds - res.utilization_timestamp.utc_seconds) / double(-res.decay_secs));
   res.utilization_timestamp = now;
}

void system_contract::update_rentbw_state(rentbw_state& state) {
   time_point_sec now = eosio::current_time_point();
   update_weight(now, state.net);
   update_weight(now, state.cpu);
   update_utilization(now, state.net);
   update_utilization(now, state.cpu);
}

void system_contract::configrentbw(rentbw_config& args) {
   require_auth(get_self());
   time_point_sec         now         = eosio::current_time_point();
   auto                   core_symbol = get_core_symbol();
   rentbw_state_singleton state_sing{ get_self(), 0 };
   auto                   state = state_sing.get_or_default();

   auto update = [&](auto& state, auto& args, auto& delta_weight) {
      if (args.current_weight == args.target_weight)
         args.target_timestamp = now;
      else
         eosio::check(args.target_timestamp > now, "target_timestamp must be in the future");
      eosio::check(args.target_weight >= args.current_weight, "weight can't shrink over time");
      eosio::check(args.current_weight >= state.utilization, "weight can't shrink below utilization");
      eosio::check(args.exponent >= 1, "exponent must be >= 1");
      eosio::check(args.decay_secs >= 1, "decay_secs must be >= 1");
      eosio::check(args.total_price.symbol == core_symbol, "total_price doesn't match core symbol");
      eosio::check(args.total_price.amount > 0, "total_price must be positive");
      eosio::check(args.min_rent_price.symbol == core_symbol, "min_rent_price doesn't match core symbol");

      delta_weight = args.current_weight - state.weight;

      state.weight            = args.current_weight;
      state.initial_weight    = args.current_weight;
      state.target_weight     = args.target_weight;
      state.initial_timestamp = now;
      state.target_timestamp  = args.target_timestamp;
      state.exponent          = args.exponent;
      state.decay_secs        = args.decay_secs;
      state.total_price       = args.total_price;
      state.min_rent_price    = args.min_rent_price;
   };

   eosio::check(args.rent_days > 0, "rent_days must be > 0");
   state.rent_days = args.rent_days;

   int64_t net_delta = 0;
   int64_t cpu_delta = 0;
   update(state.net, args.net, net_delta);
   update(state.cpu, args.cpu, cpu_delta);

   adjust_resources(get_self(), reserv_account, core_symbol, net_delta, cpu_delta, true);
   state_sing.set(state, get_self());
} // system_contract::configrentbw

void system_contract::rentbw(const name& payer, const name& receiver, uint32_t days, int64_t net, int64_t cpu,
                             const asset& max_payment) {
   require_auth(payer);
   rentbw_state_singleton state_sing{ get_self(), 0 };
   rentbw_order_table     orders{ get_self(), 0 };
   eosio::check(state_sing.exists(), "rentbw hasn't been initialized");
   auto state       = state_sing.get();
   auto core_symbol = get_core_symbol();
   process_rentbw_queue(core_symbol, state, orders, 2);
   update_rentbw_state(state);
   state_sing.set(state, get_self());
}

} // namespace eosiosystem
