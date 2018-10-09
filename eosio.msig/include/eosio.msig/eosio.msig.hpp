#pragma once
#include <eosiolib/eosio.hpp>
#include <eosiolib/transaction.hpp>

namespace eosio {

   class multisig : public contract {
      public:
         multisig( name self ):contract(self){}

         void propose();
         void approve( name proposer, name proposal_name, permission_level level );
         void unapprove( name proposer, name proposal_name, permission_level level );
         void cancel( name proposer, name proposal_name, name canceler );
         void exec( name proposer, name proposal_name, name executer );
         void invalidate( name account );

      private:
         struct proposal {
            name                            proposal_name;
            std::vector<char>               packed_transaction;

            uint64_t primary_key()const { return proposal_name.value; }
         };
         typedef eosio::multi_index< "proposal"_n, proposal > proposals;

         struct old_approvals_info {
            name                            proposal_name;
            std::vector<permission_level>   requested_approvals;
            std::vector<permission_level>   provided_approvals;

            uint64_t primary_key()const { return proposal_name.value; }
         };
         typedef eosio::multi_index< "approvals"_n, old_approvals_info > old_approvals;

         struct approval {
            permission_level level;
            time_point       time;
         };

         struct approvals_info {
            uint8_t                 version = 1;
            name                    proposal_name;
            //requested approval doesn't need to cointain time, but we want requested approval
            //to be of exact the same size ad provided approval, in this case approve/unapprove
            //doesn't change serialized data size. So, we use the same type.
            std::vector<approval>   requested_approvals;
            std::vector<approval>   provided_approvals;

            uint64_t primary_key()const { return proposal_name.value; }
         };
         typedef eosio::multi_index< "approvals2"_n, approvals_info > approvals;

         struct invalidation {
            name         account;
            time_point   last_invalidation_time;

            uint64_t primary_key() const { return account.value; }
         };

         typedef eosio::multi_index< "invals"_n, invalidation > invalidations;
};

} /// namespace eosio
