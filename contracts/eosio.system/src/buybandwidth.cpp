#include <eosio.system/eosio.system.hpp>

namespace eosiosystem {

void system_contract::configbuybw(buybw_config& args) {
   time_point_sec        now         = eosio::current_time_point();
   auto                  core_symbol = get_core_symbol();
   buybw_state_singleton state_sing{ get_self(), 0 };
   auto                  state = state_sing.get_or_default();

   auto update = [&](auto& state, auto& args) {
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
      eosio::check(args.min_purchase_price.symbol == core_symbol, "min_purchase_price doesn't match core symbol");

      state.weight             = args.current_weight;
      state.initial_weight     = args.current_weight;
      state.target_weight      = args.target_weight;
      state.initial_timestamp  = now;
      state.target_timestamp   = args.target_timestamp;
      state.exponent           = args.exponent;
      state.decay_secs         = args.decay_secs;
      state.total_price        = args.total_price;
      state.min_purchase_price = args.min_purchase_price;
   };

   eosio::check(args.purchase_days > 0, "purchase_days must be > 0");
   update(state.net, args.net);
   update(state.cpu, args.cpu);
   state.purchase_days = args.purchase_days;

   state_sing.set(state, get_self());
}

void system_contract::buybandwidth(const name& payer, const name& receiver, uint32_t days, int64_t net, int64_t cpu,
                                   const asset& max_payment) {
   //
}

} // namespace eosiosystem
