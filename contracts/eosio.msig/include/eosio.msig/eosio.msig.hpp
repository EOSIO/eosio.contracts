#pragma once

#include <eosio/binary_extension.hpp>
#include <eosio/eosio.hpp>
#include <eosio/ignore.hpp>
#include <eosio/transaction.hpp>

namespace eosio {
   /**
    *  Clone of `eosio::binary_extension` that includes `operator=` to avoid
    *  bumping the `eosio.cdt` dependency version of the v1.8.x patch release of
    *  `eosio.contracts`.
    */
   template <typename T>
   class eosio_msig_binary_extension {
      public:
         using value_type = T;

         constexpr eosio_msig_binary_extension() {}
         constexpr eosio_msig_binary_extension( const T& ext )
         :_has_value(true)
         {
            ::new (&_data) T(ext);
         }
         constexpr eosio_msig_binary_extension( T&& ext )
         :_has_value(true)
         {
            ::new (&_data) T(std::move(ext));
         }
          /** construct contained type in place */
         template <typename... Args>
         constexpr eosio_msig_binary_extension( std::in_place_t, Args&&... args )
         :_has_value(true)
         {
            ::new (&_data) T(std::forward<Args>(args)...);
         }

         constexpr eosio_msig_binary_extension( const eosio_msig_binary_extension& other )
         :_has_value(other._has_value)
         {
            if( other._has_value ) ::new (&_data) T( *other );
         }

         constexpr eosio_msig_binary_extension( eosio_msig_binary_extension&& other )
         :_has_value(other._has_value)
         {
            if( other._has_value ) {
               ::new (&_data) T( *std::move(other) );
               other._has_value = false;
            }
         }

         /// @cond INTERNAL
         ~eosio_msig_binary_extension() { reset(); }

         /// @cond INTERNAL
         constexpr eosio_msig_binary_extension& operator= (const eosio_msig_binary_extension& other) {
            if (has_value())
               reset();

            if (other.has_value()) {
               ::new (&_data) T(*other);
               _has_value = true;
            }
            return *this;
         }

         /// @cond INTERNAL
         constexpr eosio_msig_binary_extension& operator= (eosio_msig_binary_extension&& other) {
            if (has_value())
               reset();

            if (other.has_value()) {
               ::new (&_data) T(*other);
               _has_value = true;
               other._has_value = false;
            }
            return *this;
         }
         /** test if container is holding a value */
         constexpr explicit operator bool()const { return _has_value; }
         /** test if container is holding a value */
         constexpr bool has_value()const { return _has_value; }

          /** get the contained value */
         constexpr T& value()& {
            if (!_has_value) {
               check(false, "cannot get value of empty eosio_msig_binary_extension");
            }
            return _get();
         }

         /// @cond INTERNAL

          /** get the contained value */
         constexpr const T& value()const & {
            if (!_has_value) {
               check(false, "cannot get value of empty eosio_msig_binary_extension");
            }
            return _get();
         }

          /** get the contained value or a user specified default
          * @pre def should be convertible to type T
          * */
         template <typename U>
         constexpr auto value_or( U&& def ) -> std::enable_if_t<std::is_convertible<U, T>::value, T&>& {
            if (_has_value)
               return _get();
            return def;
         }
       
         constexpr T value_or() const { return (_has_value) ? _get() : T{}; }

         constexpr T* operator->() {
            return &_get();
         }
         constexpr const T* operator->()const {
            return &_get();
         }

         constexpr T& operator*()& {
            return _get();
         }
         constexpr const T& operator*()const& {
            return _get();
         }
         constexpr const T&& operator*()const&& {
            return std::move(_get());
         }
         constexpr T&& operator*()&& {
            return std::move(_get());
         }

         template<typename ...Args>
         T& emplace(Args&& ... args)& {
            if (_has_value) {
               reset();
            }

            ::new (&_data) T( std::forward<Args>(args)... );
            _has_value = true;

            return _get();
         }

         void reset() {
            if( _has_value ) {
               _get().~value_type();
               _has_value = false;
            }
         }

         /// @endcond

       private:
         bool _has_value = false;
         typename std::aligned_storage<sizeof(T), alignof(T)>::type _data;

         constexpr T& _get() {
            return *reinterpret_cast<T*>(&_data);
         }

         constexpr const T& _get()const {
            return *reinterpret_cast<const T*>(&_data);
         }
   };

   /// @cond IMPLEMENTATIONS

   /**
    *  Serialize a eosio_msig_binary_extension into a stream
    *
    *  @ingroup eosio_msig_binary_extension
    *  @brief Serialize a eosio_msig_binary_extension
    *  @param ds - The stream to write
    *  @param opt - The value to serialize
    *  @tparam DataStream - Type of datastream buffer
    *  @return DataStream& - Reference to the datastream
    */
   template<typename DataStream, typename T>
   inline DataStream& operator<<(DataStream& ds, const eosio::eosio_msig_binary_extension<T>& be) {
     ds << be.value_or();
     return ds;
   }

   /**
    *  Deserialize a eosio_msig_binary_extension from a stream
    *
    *  @ingroup eosio_msig_binary_extension
    *  @brief Deserialize a eosio_msig_binary_extension
    *  @param ds - The stream to read
    *  @param opt - The destination for deserialized value
    *  @tparam DataStream - Type of datastream buffer
    *  @return DataStream& - Reference to the datastream
    */
   template<typename DataStream, typename T>
   inline DataStream& operator>>(DataStream& ds, eosio::eosio_msig_binary_extension<T>& be) {
     if( ds.remaining() ) {
        T val;
        ds >> val;
        be.emplace(val);
     }
     return ds;
   }

   /**
    * The `eosio.msig` system contract allows for creation of proposed transactions which require authorization from a list of accounts, approval of the proposed transactions by those accounts required to approve it, and finally, it also allows the execution of the approved transactions on the blockchain.
    *
    * In short, the workflow to propose, review, approve and then executed a transaction it can be described by the following:
    * - first you create a transaction json file,
    * - then you submit this proposal to the `eosio.msig` contract, and you also insert the account permissions required to approve this proposal into the command that submits the proposal to the blockchain,
    * - the proposal then gets stored on the blockchain by the `eosio.msig` contract, and is accessible for review and approval to those accounts required to approve it,
    * - after each of the appointed accounts required to approve the proposed transactions reviews and approves it, you can execute the proposed transaction. The `eosio.msig` contract will execute it automatically, but not before validating that the transaction has not expired, it is not cancelled, and it has been signed by all the permissions in the initial proposal's required permission list.
    */
   class [[eosio::contract("eosio.msig")]] multisig : public contract {
      public:
         using contract::contract;

         /**
          * Propose action, creates a proposal containing one transaction.
          * Allows an account `proposer` to make a proposal `proposal_name` which has `requested`
          * permission levels expected to approve the proposal, and if approved by all expected
          * permission levels then `trx` transaction can we executed by this proposal.
          * The `proposer` account is authorized and the `trx` transaction is verified if it was
          * authorized by the provided keys and permissions, and if the proposal name doesn’t
          * already exist; if all validations pass the `proposal_name` and `trx` trasanction are
          * saved in the proposals table and the `requested` permission levels to the
          * approvals table (for the `proposer` context). Storage changes are billed to `proposer`.
          *
          * @param proposer - The account proposing a transaction
          * @param proposal_name - The name of the proposal (should be unique for proposer)
          * @param requested - Permission levels expected to approve the proposal
          * @param trx - Proposed transaction
          */
         [[eosio::action]]
         void propose(name proposer, name proposal_name,
                      std::vector<permission_level> requested, ignore<transaction> trx);
         /**
          * Approve action approves an existing proposal. Allows an account, the owner of `level` permission, to approve a proposal `proposal_name`
          * proposed by `proposer`. If the proposal's requested approval list contains the `level`
          * permission then the `level` permission is moved from internal `requested_approvals` list to
          * internal `provided_approvals` list of the proposal, thus persisting the approval for
          * the `proposal_name` proposal. Storage changes are billed to `proposer`.
          *
          * @param proposer - The account proposing a transaction
          * @param proposal_name - The name of the proposal (should be unique for proposer)
          * @param level - Permission level approving the transaction
          * @param proposal_hash - Transaction's checksum
          */
         [[eosio::action]]
         void approve( name proposer, name proposal_name, permission_level level,
                       const eosio::binary_extension<eosio::checksum256>& proposal_hash );
         /**
          * Unapprove action revokes an existing proposal. This action is the reverse of the `approve` action: if all validations pass
          * the `level` permission is erased from internal `provided_approvals` and added to the internal
          * `requested_approvals` list, and thus un-approve or revoke the proposal.
          *
          * @param proposer - The account proposing a transaction
          * @param proposal_name - The name of the proposal (should be an existing proposal)
          * @param level - Permission level revoking approval for proposal
          */
         [[eosio::action]]
         void unapprove( name proposer, name proposal_name, permission_level level );
         /**
          * Cancel action cancels an existing proposal.
          *
          * @param proposer - The account proposing a transaction
          * @param proposal_name - The name of the proposal (should be an existing proposal)
          * @param canceler - The account cancelling the proposal (only the proposer can cancel an unexpired transaction, and the canceler has to be different than the proposer)
          *
          * Allows the `canceler` account to cancel the `proposal_name` proposal, created by a `proposer`,
          * only after time has expired on the proposed transaction. It removes corresponding entries from
          * internal proptable and from approval (or old approvals) tables as well.
          */
         [[eosio::action]]
         void cancel( name proposer, name proposal_name, name canceler );
         /**
          * Exec action allows an `executer` account to execute a proposal.
          *
          * Preconditions:
          * - `executer` has authorization,
          * - `proposal_name` is found in the proposals table,
          * - all requested approvals are received,
          * - proposed transaction is not expired,
          * - and approval accounts are not found in invalidations table.
          *
          * If all preconditions are met the transaction is executed as a deferred transaction,
          * and the proposal is erased from the proposals table.
          *
          * @param proposer - The account proposing a transaction
          * @param proposal_name - The name of the proposal (should be an existing proposal)
          * @param executer - The account executing the transaction
          */
         [[eosio::action]]
         void exec( name proposer, name proposal_name, name executer );
         /**
          * Invalidate action allows an `account` to invalidate itself, that is, its name is added to
          * the invalidations table and this table will be cross referenced when exec is performed.
          *
          * @param account - The account invalidating the transaction
          */
         [[eosio::action]]
         void invalidate( name account );

         using propose_action = eosio::action_wrapper<"propose"_n, &multisig::propose>;
         using approve_action = eosio::action_wrapper<"approve"_n, &multisig::approve>;
         using unapprove_action = eosio::action_wrapper<"unapprove"_n, &multisig::unapprove>;
         using cancel_action = eosio::action_wrapper<"cancel"_n, &multisig::cancel>;
         using exec_action = eosio::action_wrapper<"exec"_n, &multisig::exec>;
         using invalidate_action = eosio::action_wrapper<"invalidate"_n, &multisig::invalidate>;
   };

   struct [[eosio::table]] proposal {
      name                                                            proposal_name;
      std::vector<char>                                               packed_transaction;
      eosio::eosio_msig_binary_extension< std::optional<time_point> > earliest_exec_time;

      uint64_t primary_key()const { return proposal_name.value; }
   };
   typedef eosio::multi_index< "proposal"_n, proposal > proposals;

   struct [[eosio::table]] old_approvals_info {
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

   struct [[eosio::table]] approvals_info {
      uint8_t                 version = 1;
      name                    proposal_name;
      //requested approval doesn't need to contain time, but we want requested approval
      //to be of exactly the same size as provided approval, in this case approve/unapprove
      //doesn't change serialized data size. So, we use the same type.
      std::vector<approval>   requested_approvals;
      std::vector<approval>   provided_approvals;

      uint64_t primary_key()const { return proposal_name.value; }
   };
   typedef eosio::multi_index< "approvals2"_n, approvals_info > approvals;

   struct [[eosio::table]] invalidation {
      name         account;
      time_point   last_invalidation_time;

      uint64_t primary_key() const { return account.value; }
   };
   typedef eosio::multi_index< "invals"_n, invalidation > invalidations;

} /// namespace eosio
