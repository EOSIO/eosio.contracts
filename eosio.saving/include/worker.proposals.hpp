#include <trail.voting.hpp>
#include <trail.system.hpp>

#include <eosiolib/eosio.hpp>
#include <eosiolib/permission.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/action.hpp>
#include <eosiolib/singleton.hpp>

using namespace std;
using namespace eosio;

class [[eosio::contract("eosio.saving")]] workerproposal : public contract {
    public:

      workerproposal(name self, name code, datastream<const char*> ds);

      ~workerproposal();

		  [[eosio::action]]
      void submit(name proposer, std::string title, uint16_t cycles, std::string ipfs_location, asset amount, name receiver);

		  [[eosio::action]]
      void linkballot(uint64_t prop_id, uint64_t ballot_id, name proposer);

		  [[eosio::action]]
      void claim(uint64_t prop_id, name proposer);

      struct [[eosio::table]] proposal {
        uint64_t         id;
        uint64_t         ballot_id;
        name             proposer;
        name             receiver;
        std::string      title;
        std::string      ipfs_location;
        uint16_t         cycles;
        uint64_t         amount;
        uint64_t         fee;
        uint32_t         begin_time;
        uint32_t         end_time;
        uint8_t          status; // 0 = INACTIVE, 1 = ACTIVE
        uint16_t         current_cycle;
        
        auto primary_key() const { return id; }
        EOSLIB_SERIALIZE(proposal, (id)(ballot_id)(proposer)(receiver)(title)(ipfs_location)(cycles)(amount)(fee)(begin_time)(end_time)(status)(current_cycle))
      };

      struct [[eosio::table("wpenv"), eosio::contract("eosio.saving")]] wp_env {
        name     publisher;
        uint32_t cycle_duration;
        uint16_t fee_percentage;
        uint64_t fee_min;

        uint64_t primary_key() const { return publisher.value; }
        EOSLIB_SERIALIZE(wp_env, (publisher)(cycle_duration)(fee_percentage)(fee_min))
      };
      wp_env wp_env_struct;

      typedef eosio::multi_index< "proposals"_n, proposal> proposals;
      typedef singleton<"wpenv"_n, wp_env> wp_environment_singleton;

      wp_environment_singleton wpenv;    
};
