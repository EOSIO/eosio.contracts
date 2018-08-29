#pragma once
#include <eosiolib/eosio.hpp>
#include <eosiolib/transaction.hpp>

namespace eosio {

   class multisig : public contract {
      public:
         multisig( account_name self ):contract(self){}

         void propose();
         void approve( account_name proposer, name proposal_name, permission_level level );
         void unapprove( account_name proposer, name proposal_name, permission_level level );
         void cancel( account_name proposer, name proposal_name, account_name canceler );
         void exec( account_name proposer, name proposal_name, account_name executer );
         void invalidate( account_name account );

      private:
         struct proposal {
            name                       proposal_name;
            vector<char>               packed_transaction;

            auto primary_key()const { return proposal_name.value; }
         };
         typedef eosio::multi_index<N(proposal),proposal> proposals;

         struct old_approvals_info {
            name                       proposal_name;
            vector<permission_level>   requested_approvals;
            vector<permission_level>   provided_approvals;

            auto primary_key()const { return proposal_name.value; }
         };
         typedef eosio::multi_index<N(approvals), old_approvals_info> old_approvals;

         struct approval {
            permission_level level;
            uint64_t         time;
         };

         struct approvals_info {
            uint8_t                    version;
            name                       proposal_name;
            vector<permission_level>   requested_approvals;
            vector<approval>           provided_approvals;

            auto primary_key()const { return proposal_name.value; }
         };
         typedef eosio::multi_index<N(approvals2), approvals_info> approvals;

         struct invalidation {
            account_name account;
            uint64_t     last_invalidation_time;

            auto primary_key() const { return account; }
         };

         typedef eosio::multi_index<N(invals), invalidation> invalidations;
};

} /// namespace eosio
