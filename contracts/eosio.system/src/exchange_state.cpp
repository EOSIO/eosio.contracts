#include <eosio.system/exchange_state.hpp>

namespace eosiosystem {
   asset exchange_state::convert_to_exchange( connector& c, asset in ) {

      real_type R(supply.amount);
      real_type C(c.balance.amount/* + in.amount*/);
      real_type F(c.weight);
      real_type T(in.amount);
      real_type ONE(1.0);

      real_type E = -R * (ONE - std::pow( ONE + T / C, F) );
      int64_t issued = int64_t(E);

      supply.amount += issued;
      c.balance.amount += in.amount;

      return asset( issued, supply.symbol );
   }

   asset exchange_state::convert_from_exchange( connector& c, asset in ) {
      check( in.symbol== supply.symbol, "unexpected asset symbol input" );

      real_type R(supply.amount /*- in.amount*/);
      real_type C(c.balance.amount);
      real_type F(1.0/c.weight);
      real_type E(in.amount);
      real_type ONE(1.0);


     // potentially more accurate: 
     // The functions std::expm1 and std::log1p are useful for financial calculations, for example, 
     // when calculating small daily interest rates: (1+x)n
     // -1 can be expressed as std::expm1(n * std::log1p(x)). 
     // real_type T = C * std::expm1( F * std::log1p(E/R) );
      
      real_type T = C * (std::pow( ONE + E/R, F) - ONE);
      int64_t out = int64_t(T);

      supply.amount -= in.amount;
      c.balance.amount -= out;

      return asset( out, c.balance.symbol );
   }

   asset exchange_state::convert( asset from, const symbol& to ) {
      auto sell_symbol  = from.symbol;
      auto ex_symbol    = supply.symbol;
      auto base_symbol  = base.balance.symbol;
      auto quote_symbol = quote.balance.symbol;

      //print( "From: ", from, " TO ", asset( 0,to), "\n" );
      //print( "base: ", base_symbol, "\n" );
      //print( "quote: ", quote_symbol, "\n" );
      //print( "ex: ", supply.symbol, "\n" );

      if( sell_symbol != ex_symbol ) {
         if( sell_symbol == base_symbol ) {
            from = convert_to_exchange( base, from );
         } else if( sell_symbol == quote_symbol ) {
            from = convert_to_exchange( quote, from );
         } else { 
            check( false, "invalid sell" );
         }
      } else {
         if( to == base_symbol ) {
            from = convert_from_exchange( base, from ); 
         } else if( to == quote_symbol ) {
            from = convert_from_exchange( quote, from ); 
         } else {
            check( false, "invalid conversion" );
         }
      }

      if( to != from.symbol )
         return convert( from, to );

      return from;
   }

   asset exchange_state::direct_convert( const asset& from, const symbol& to ) {
      const auto& sell_symbol  = from.symbol;
      const auto& base_symbol  = base.balance.symbol;
      const auto& quote_symbol = quote.balance.symbol;
      check( sell_symbol != to, "cannot convert to the same symbol" );
      asset out( 0, to );
      if ( from.symbol == base_symbol && to == quote_symbol ) {
         out = get_bancor_output( base.balance, quote.balance, from );
         base.balance  += from;
         quote.balance -= out;
      } else if ( from.symbol == quote_symbol && to == base_symbol ) {
         out = get_bancor_output( quote.balance, base.balance, from );
         quote.balance += from;
         base.balance  -= out;
      } else {
         check( false, "invalid conversion" );
      }
      return out;
   }

   asset exchange_state::get_bancor_output( const asset& inp_balance,
                                            const asset& out_balance,
                                            const asset& inp )
   {
      const double ib = double(inp_balance.amount);
      const double ob = double(out_balance.amount);
      const double in = double(inp.amount);

      int64_t out = int64_t( (in * ob) / (ib + in) );

      if ( out < 0 ) out = 0;

      return asset( out, out_balance.symbol );
   }

} /// namespace eosiosystem
