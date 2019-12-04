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

void system_contract::process_rentbw_queue(time_point_sec now, symbol core_symbol, rentbw_state& state,
                                           rentbw_order_table& orders, uint32_t max_items, int64_t& net_delta_available,
                                           int64_t& cpu_delta_available) {
   auto idx = orders.get_index<"byexpires"_n>();
   while (max_items--) {
      auto it = idx.begin();
      if (it == idx.end() || it->expires > now)
         break;
      net_delta_available += it->net_weight;
      cpu_delta_available += it->cpu_weight;
      adjust_resources(get_self(), it->owner, core_symbol, -it->net_weight, -it->cpu_weight);
      idx.erase(it);
   }
   state.net.utilization -= net_delta_available;
   state.cpu.utilization -= cpu_delta_available;
}

void update_weight(time_point_sec now, rentbw_state_resource& res, int64_t& delta_available) {
   if (now >= res.target_timestamp)
      res.weight_ratio = res.target_weight_ratio;
   else
      res.weight_ratio = res.initial_weight_ratio + //
                         int128_t(res.target_weight_ratio - res.initial_weight_ratio) *
                               (now.utc_seconds - res.initial_timestamp.utc_seconds) /
                               (res.target_timestamp.utc_seconds - res.initial_timestamp.utc_seconds);
   // !!! check bounds of weight_ratio
   int64_t new_weight = res.assumed_stake_weight * int128_t(rentbw_frac) / res.weight_ratio - res.assumed_stake_weight;
   delta_available += new_weight - res.weight;
   res.weight = new_weight;
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

void system_contract::configrentbw(rentbw_config& args) {
   require_auth(get_self());
   time_point_sec         now         = eosio::current_time_point();
   auto                   core_symbol = get_core_symbol();
   rentbw_state_singleton state_sing{ get_self(), 0 };
   auto                   state = state_sing.get_or_default();

   int64_t net_delta_available = 0;
   int64_t cpu_delta_available = 0;
   if (state_sing.exists()) {
      update_weight(now, state.net, net_delta_available);
      update_weight(now, state.cpu, cpu_delta_available);
   }

   auto update = [&](auto& state, auto& args) {
      if (!args.current_weight_ratio) {
         if (state.weight_ratio)
            args.current_weight_ratio = state.weight_ratio;
         else
            args.current_weight_ratio = state.initial_weight_ratio;
      }
      if (!args.target_weight_ratio)
         args.target_weight_ratio = state.target_weight_ratio;
      if (!args.assumed_stake_weight)
         args.assumed_stake_weight = state.assumed_stake_weight;
      if (!args.target_timestamp.utc_seconds)
         args.target_timestamp = state.target_timestamp;
      if (!args.exponent)
         args.exponent = state.exponent;
      if (!args.decay_secs)
         args.decay_secs = state.decay_secs;
      if (!args.target_price.amount && state.target_price.amount)
         args.target_price = state.target_price;

      // !!! examine checks
      if (args.current_weight_ratio == args.target_weight_ratio)
         args.target_timestamp = now;
      else
         eosio::check(args.target_timestamp > now, "target_timestamp must be in the future");
      eosio::check(args.current_weight_ratio > 0, "current_weight_ratio is too small");
      eosio::check(args.current_weight_ratio <= rentbw_frac, "current_weight_ratio is too large");
      eosio::check(args.target_weight_ratio > 0, "target_weight_ratio is too small");
      eosio::check(args.target_weight_ratio <= args.current_weight_ratio, "weight can't grow over time");
      eosio::check(args.assumed_stake_weight >= 1,
                   "assumed_stake_weight must be at least 1; a much larger value is recommended");
      eosio::check(args.exponent >= 1, "exponent must be >= 1");
      eosio::check(args.decay_secs >= 1, "decay_secs must be >= 1");
      eosio::check(args.target_price.symbol == core_symbol, "target_price doesn't match core symbol");
      eosio::check(args.target_price.amount > 0, "target_price must be positive");

      state.assumed_stake_weight = args.assumed_stake_weight;
      state.initial_weight_ratio = args.current_weight_ratio;
      state.target_weight_ratio  = args.target_weight_ratio;
      state.initial_timestamp    = now;
      state.target_timestamp     = args.target_timestamp;
      state.exponent             = args.exponent;
      state.decay_secs           = args.decay_secs;
      state.target_price         = args.target_price;
   };

   if (!args.rent_days)
      args.rent_days = state.rent_days;
   if (!args.min_rent_price.amount && state.min_rent_price.amount)
      args.min_rent_price = state.min_rent_price;

   eosio::check(args.rent_days > 0, "rent_days must be > 0");
   eosio::check(args.min_rent_price.symbol == core_symbol, "min_rent_price doesn't match core symbol");
   eosio::check(args.min_rent_price.amount > 0, "min_rent_price must be positive");

   state.rent_days      = args.rent_days;
   state.min_rent_price = args.min_rent_price;

   update(state.net, args.net);
   update(state.cpu, args.cpu);

   update_weight(now, state.net, net_delta_available);
   update_weight(now, state.cpu, cpu_delta_available);
   eosio::check(state.net.weight >= state.net.utilization, "weight can't shrink below utilization");
   eosio::check(state.cpu.weight >= state.cpu.utilization, "weight can't shrink below utilization");

   adjust_resources(get_self(), reserv_account, core_symbol, net_delta_available, cpu_delta_available, true);
   state_sing.set(state, get_self());
} // system_contract::configrentbw

int64_t calc_rentbw_price(const rentbw_state_resource& state, double utilization) {
   return ceil(state.target_price.amount * pow(utilization / state.weight, state.exponent));
}

void system_contract::rentbwexec(const name& user, uint16_t max) {
   require_auth(user);
   rentbw_state_singleton state_sing{ get_self(), 0 };
   rentbw_order_table     orders{ get_self(), 0 };
   eosio::check(state_sing.exists(), "rentbw hasn't been initialized");
   auto           state       = state_sing.get();
   time_point_sec now         = eosio::current_time_point();
   auto           core_symbol = get_core_symbol();

   int64_t net_delta_available = 0;
   int64_t cpu_delta_available = 0;
   process_rentbw_queue(now, core_symbol, state, orders, max, net_delta_available, cpu_delta_available);
   update_weight(now, state.net, net_delta_available);
   update_weight(now, state.cpu, cpu_delta_available);
   update_utilization(now, state.net);
   update_utilization(now, state.cpu);

   adjust_resources(get_self(), reserv_account, core_symbol, net_delta_available, cpu_delta_available, true);
   state_sing.set(state, get_self());
}

void system_contract::rentbw(const name& payer, const name& receiver, uint32_t days, int64_t net_frac, int64_t cpu_frac,
                             const asset& max_payment) {
   require_auth(payer);
   rentbw_state_singleton state_sing{ get_self(), 0 };
   rentbw_order_table     orders{ get_self(), 0 };
   eosio::check(state_sing.exists(), "rentbw hasn't been initialized");
   auto           state       = state_sing.get();
   time_point_sec now         = eosio::current_time_point();
   auto           core_symbol = get_core_symbol();
   eosio::check(max_payment.symbol == core_symbol, "max_payment doesn't match core symbol");
   eosio::check(days == state.rent_days, "days doesn't match configuration");
   eosio::check(net_frac >= 0, "net_frac can't be negative");
   eosio::check(cpu_frac >= 0, "cpu_frac can't be negative");
   eosio::check(net_frac <= rentbw_frac, "net can't be more than 100%");
   eosio::check(cpu_frac <= rentbw_frac, "cpu can't be more than 100%");

   int64_t net_delta_available = 0;
   int64_t cpu_delta_available = 0;
   process_rentbw_queue(now, core_symbol, state, orders, 2, net_delta_available, cpu_delta_available);
   update_weight(now, state.net, net_delta_available);
   update_weight(now, state.cpu, cpu_delta_available);
   update_utilization(now, state.net);
   update_utilization(now, state.cpu);

   eosio::asset fee{ 0, core_symbol };
   auto         process = [&](int64_t frac, int64_t& amount, rentbw_state_resource& state) {
      if (!frac)
         return;
      amount = int128_t(frac) * state.weight / rentbw_frac;
      fee.amount += calc_rentbw_price(state, state.adjusted_utilization + amount) -
                    calc_rentbw_price(state, state.adjusted_utilization);
      state.utilization += amount;
      eosio::check(state.utilization <= state.weight, "market doesn't have enough resources available");
   };

   int64_t net_amount = 0;
   int64_t cpu_amount = 0;
   process(net_frac, net_amount, state.net);
   process(cpu_frac, cpu_amount, state.cpu);
   eosio::check(fee <= max_payment, "calculated fee exceeds max_payment");
   eosio::check(fee >= state.min_rent_price, "calculated fee is below minimum; try renting more");

   orders.emplace(payer, [&](auto& order) {
      order.id         = orders.available_primary_key();
      order.owner      = receiver;
      order.net_weight = net_amount;
      order.cpu_weight = cpu_amount;
      order.expires    = now + eosio::days(days);
   });

   adjust_resources(payer, receiver, core_symbol, net_amount, cpu_amount, true);
   adjust_resources(get_self(), reserv_account, core_symbol, net_delta_available, cpu_delta_available, true);
   channel_to_rex(payer, fee, true);
   state_sing.set(state, get_self());
}

} // namespace eosiosystem
