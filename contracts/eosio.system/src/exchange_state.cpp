#include <eosio.system/exchange_state.hpp>

namespace eosiosystem {

   asset exchange_state::convert_to_exchange( connector& reserve, const asset& payment )
   {
      const double S0 = supply.amount;
      const double R0 = reserve.balance.amount;
      const double dR = payment.amount;
      const double F  = reserve.weight;

      double dS = S0 * ( std::pow(1. + dR / R0, F) - 1. );
      if ( dS < 0 ) dS = 0; // rounding errors
      reserve.balance += payment;
      supply.amount   += int64_t(dS);
      return asset( int64_t(dS), supply.symbol );
   }

   asset exchange_state::convert_from_exchange( connector& reserve, const asset& tokens )
   {
      const double R0 = reserve.balance.amount;
      const double S0 = supply.amount;
      const double dS = -tokens.amount; // tokens are subtracted from supply
      const double Fi = double(1) / reserve.weight;

      double dR = R0 * ( std::pow(1. + dS / S0, Fi) - 1. ); // dR < 0
      if ( dR > 0 ) dR = 0; // rounding errors 
      reserve.balance.amount -= int64_t(-dR);
      supply                 -= tokens;
      return asset( int64_t(-dR), reserve.balance.symbol );
   }

   asset exchange_state::convert( const asset& from, const symbol& to )
   {
      const auto& sell_symbol  = from.symbol;
      const auto& base_symbol  = base.balance.symbol;
      const auto& quote_symbol = quote.balance.symbol;
      check( sell_symbol != to, "cannot convert to the same symbol" );

      asset out( 0, to );
      if ( sell_symbol == base_symbol && to == quote_symbol ) {
         const asset tmp = convert_to_exchange( base, from );
         out = convert_from_exchange( quote, tmp );
      } else if ( sell_symbol == quote_symbol && to == base_symbol ) {
         const asset tmp = convert_to_exchange( quote, from );
         out = convert_from_exchange( base, tmp );
      } else {
         check( false, "invalid conversion" );
      }
      return out;
   }

   asset exchange_state::direct_convert( const asset& from, const symbol& to ) {
      const auto& sell_symbol  = from.symbol;
      const auto& base_symbol  = base.balance.symbol;
      const auto& quote_symbol = quote.balance.symbol;
      check( sell_symbol != to, "cannot convert to the same symbol" );

      asset out( 0, to );
      if ( sell_symbol == base_symbol && to == quote_symbol ) {
         out = get_direct_bancor_output( base.balance, quote.balance, from );
         base.balance  += from;
         quote.balance -= out;
      } else if ( sell_symbol == quote_symbol && to == base_symbol ) {
         out = get_direct_bancor_output( quote.balance, base.balance, from );
         quote.balance += from;
         base.balance  -= out;
      } else {
         check( false, "invalid conversion" );
      }
      return out;
   }

   asset exchange_state::get_direct_bancor_output( const asset& inp_reserve,
                                                   const asset& out_reserve,
                                                   const asset& inp )
   {
      const double ib = inp_reserve.amount;
      const double ob = out_reserve.amount;
      const double in = inp.amount;

      int64_t out = int64_t( (in * ob) / (ib + in) );

      if ( out < 0 ) out = 0;

      return asset( out, out_reserve.symbol );
   }

} /// namespace eosiosystem
