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
	  struct [[eosio::table]] submission {
        uint64_t         id;
        uint64_t         ballot_id;
        name             proposer;
        name             receiver;
        std::string      title;
        std::string      ipfs_location;
        uint16_t         cycles;
        uint64_t         amount;
        uint64_t         fee;
        
        auto primary_key() const { return id; }
        EOSLIB_SERIALIZE(submission, (id)(ballot_id)(proposer)(receiver)(title)(ipfs_location)(cycles)(amount)(fee))
      };

      struct [[eosio::table("wpenv"), eosio::contract("eosio.saving")]] wp_env {
        name     publisher;
        uint32_t cycle_duration;
        uint16_t fee_percentage;
        uint64_t fee_min;
		uint64_t start_delay;

        uint64_t primary_key() const { return publisher.value; }
        EOSLIB_SERIALIZE(wp_env, (publisher)(cycle_duration)(fee_percentage)(fee_min)(start_delay))
      };
      wp_env wp_env_struct;

      typedef eosio::multi_index< "submissions"_n, submission> submissions;
      typedef singleton<"wpenv"_n, wp_env> wp_environment_singleton;

      wp_environment_singleton wpenv;

      workerproposal(name self, name code, datastream<const char*> ds);

      ~workerproposal();

	  [[eosio::action]]
	  void setenv(wp_env new_environment);

	  [[eosio::action]]
      void submit(name proposer, std::string title, uint16_t cycles, std::string ipfs_location, asset amount, name receiver);

	  [[eosio::action]]
      void claim(uint64_t prop_id);    
};
