#include <eosio.system/eosio.system.hpp>

namespace eosiosystem {

void system_contract::configcpu31(int64_t delta_weight, int64_t target_weight,
                                  const time_point_sec& target_timestamp,
                                  double exponent, uint32_t window,
                                  const asset& peak_price,
                                  const asset& min_purchase_price) {
  //
}

void system_contract::confignet31(int64_t delta_weight, int64_t target_weight,
                                  const time_point_sec& target_timestamp,
                                  double exponent, uint32_t window,
                                  const asset& peak_price,
                                  const asset& min_purchase_price) {
  //
}

void system_contract::buycpu31(const name& payer, const name& receiver,
                               int64_t amount, const asset& max_payment) {
  //
}

void system_contract::buynet31(const name& payer, const name& receiver,
                               int64_t amount, const asset& max_payment) {
  //
}

}  // namespace eosiosystem
