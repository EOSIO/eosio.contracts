#include <eosio.token/eosio.token.hpp>

namespace eosio
{
   void token::create()
   {
      require_auth(get_self());

      auto newtsym_code = symbol.code("NEWT", 4); // NEWT is the token symbol with precisin 4
      check(sym.code() == newtsym_code, "You can't create but NEWT token.")

      stats statstable(get_self(), sym.code().raw());
      auto existing = statstable.find(sym.code().raw());
      check(existing == statstable.end(), "token with symbol already created");

      statstable.emplace(get_self(), [&](auto &s) {
         s.supply.symbol = maximum_supply.symbol;
         s.max_supply = maximum_supply;
         s.issuer = issuer;
      });
   }

   void token::issue(const asset &quantity, const string &memo)
   {
      require_auth(get_self());

      auto sym = quantity.symbol;
      auto newtsym_code = symbol.code("NEWT", 4); // NEWT is the token symbol with precisin 4
      check(sym.code() == newtsym_code, "You can't create but NEWT token.")
      check(sym.is_valid(), "invalid symbol name");
      check(memo.size() <= 256, "memo has more than 256 bytes");

      stats statstable(get_self(), sym.code().raw());
      auto existing = statstable.find(sym.code().raw());
      check(existing != statstable.end(), "token with symbol does not exist, create token before issue");

      const auto& existing_token = *existing;
      require_auth( existing_token.issuer );

      check(quantity.is_valid(), "invalid quantity");
      check(quantity.amount > 0, "must issue positive quantity");
      check(quantity.symbol == existing_token.supply.symbol, "symbol precision mismatch");
      check(quantity.amount <= existing_token.max_supply.amount - existing_token.supply.amount, 
                                 "quantity exceeds available supply");

      statstable.modify(st, same_payer, [&](auto &s) {
         s.supply += quantity;
      });

      add_balance(st.issuer, quantity, st.issuer);
   }

   void token::retire(const asset &quantity, const string &memo)
   {
      auto sym = quantity.symbol;
      check(sym.is_valid(), "invalid symbol name");
      check(memo.size() <= 256, "memo has more than 256 bytes");

      auto newtsym_code = symbol.code("NEWT", 4); // NEWT is the token symbol with precisin 4
      check(sym.code() == newtsym_code, "You can't retire but NEWT token.")

      stats statstable(get_self(), sym.code().raw());
      auto existing = statstable.find(sym.code().raw());
      check(existing != statstable.end(), "token with symbol does not exist");
      const auto &st = *existing;

      require_auth(st.issuer);
      check(quantity.is_valid(), "invalid quantity");
      check(quantity.amount > 0, "must retire positive quantity");

      check(quantity.symbol == st.supply.symbol, "symbol precision mismatch");

      statstable.modify(st, same_payer, [&](auto &s) {
         s.supply -= quantity;
      });

      sub_balance(st.issuer, quantity);
   }

   void token::transfer(const name &from,
                        const name &to,
                        const asset &quantity,
                        const string &memo)
   {
      check(from != to, "cannot transfer to self");
      require_auth(from);
      check(is_account(to), "to account does not exist");
      auto sym = quantity.symbol.code();

      auto newtsym_code = symbol.code("NEWT", 4); // NEWT is the token symbol with precisin 4
      check(sym == newtsym_code, "You can't create but NEWT token.")

      stats statstable(get_self(), sym.raw());
      const auto &st = statstable.get(sym.raw());

      require_recipient(from);
      require_recipient(to);

      check(quantity.is_valid(), "invalid quantity");
      check(quantity.amount > 0, "must transfer positive quantity");
      check(quantity.symbol == st.supply.symbol, "symbol precision mismatch");
      check(memo.size() <= 256, "memo has more than 256 bytes");

      auto payer = has_auth(to) ? to : from;

      sub_balance(from, quantity);
      add_balance(to, quantity, payer);
   }

   void token::sub_balance(const name &owner, const asset &value)
   {
      accounts from_acnts(get_self(), owner.value);

      const auto &from = from_acnts.get(value.symbol.code().raw(), "no balance object found");
      check(from.balance.amount >= value.amount, "overdrawn balance");

      from_acnts.modify(from, owner, [&](auto &a) {
         a.balance -= value;
      });
   }

   void token::add_balance(const name &owner, const asset &value, const name &ram_payer)
   {
      accounts to_acnts(get_self(), owner.value);
      auto to = to_acnts.find(value.symbol.code().raw());
      if (to == to_acnts.end())
      {
         to_acnts.emplace(ram_payer, [&](auto &a) {
            a.balance = value;
         });
      }
      else
      {
         to_acnts.modify(to, same_payer, [&](auto &a) {
            a.balance += value;
         });
      }
   }

   void token::open(const name &owner, const symbol &symbol, const name &ram_payer)
   {
      require_auth(ram_payer);

      check(is_account(owner), "owner account does not exist");

      auto sym_code_raw = symbol.code().raw();
      stats statstable(get_self(), sym_code_raw);
      const auto &st = statstable.get(sym_code_raw, "symbol does not exist");
      check(st.supply.symbol == symbol, "symbol precision mismatch");

      accounts acnts(get_self(), owner.value);
      auto it = acnts.find(sym_code_raw);
      if (it == acnts.end())
      {
         acnts.emplace(ram_payer, [&](auto &a) {
            a.balance = asset{0, symbol};
         });
      }
   }

   void token::close(const name &owner, const symbol &symbol)
   {
      require_auth(owner);
      accounts acnts(get_self(), owner.value);
      auto it = acnts.find(symbol.code().raw());
      check(it != acnts.end(), "Balance row already deleted or never existed. Action won't have any effect.");
      check(it->balance.amount == 0, "Cannot close because the balance is not zero.");
      acnts.erase(it);
   }

   void token::airgrab(const name &owner)
   {
      require_auth(owner);
      require_recipient(owner);

      auto sym = symbol.code("NEWT", 4); // NEWT is the token symbol with precisin 4
      asset newtasset(100, sym);         // allow 100 tokens to be airgragbed 
      
      // Check if the user have airgrabbed their tokens
      airgrabs airgrab_table(get_self(), sym.raw());

      auto it = airgrab_table.find(owner.value);
      check(it == airgrab_table.end(), "You have already airgrabbed your tokens");

      transfer(_self, owner, newtasset, std::string("Airgrab, if I may."));

      // Register the airgrab so it will not be able to do it the second time
      airgrab_table.emplace(owner, [&](auto &row) {
         row.account = owner;
      });
   }
}