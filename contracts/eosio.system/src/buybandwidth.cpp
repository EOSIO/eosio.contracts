#include <eosio.system/eosio.system.hpp>

namespace eosiosystem {

void system_contract::adjust_resources(name payer, name account, int64_t net_delta, int64_t cpu_delta,
                                       bool must_not_be_managed) {
   if (!net_delta && !cpu_delta)
      return;

   user_resources_table totals_tbl(get_self(), account.value);
   auto                 tot_itr = totals_tbl.find(account.value);
   if (tot_itr == totals_tbl.end()) {
      tot_itr = totals_tbl.emplace(payer, [&](auto& tot) {
         tot.owner      = account;
         tot.net_weight = net_delta;
         tot.cpu_weight = cpu_delta;
      });
   } else {
      totals_tbl.modify(tot_itr, same_payer, [&](auto& tot) {
         tot.net_weight += net_delta;
         tot.cpu_weight += cpu_delta;
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

void system_contract::configbuybw(buybw_config& args) {
   time_point_sec        now         = eosio::current_time_point();
   auto                  core_symbol = get_core_symbol();
   buybw_state_singleton state_sing{ get_self(), 0 };
   auto                  state = state_sing.get_or_default();

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
      eosio::check(args.min_purchase_price.symbol == core_symbol, "min_purchase_price doesn't match core symbol");

      delta_weight = args.current_weight - state.weight;

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
   state.purchase_days = args.purchase_days;

   int64_t net_delta = 0;
   int64_t cpu_delta = 0;
   update(state.net, args.net, net_delta);
   update(state.cpu, args.cpu, cpu_delta);

   adjust_resources(get_self(), reserv_account, net_delta, cpu_delta, true);
   state_sing.set(state, get_self());
}

void system_contract::buybandwidth(const name& payer, const name& receiver, uint32_t days, int64_t net, int64_t cpu,
                                   const asset& max_payment) {
   //
}

} // namespace eosiosystem
