#include <boost/test/unit_test.hpp>
#include <eosio/chain/contract_table_objects.hpp>
#include <eosio/chain/global_property_object.hpp>
#include <eosio/chain/resource_limits.hpp>
#include <eosio/chain/wast_to_wasm.hpp>

// #include <cstdlib>
#include <iostream>
// #include <fc/log/logger.hpp>
// #include <eosio/chain/exceptions.hpp>
#include <iomanip>

#include <Runtime/Runtime.h>

#include "eosio.system_tester.hpp"
struct _abi_hash {
   name owner;
   fc::sha256 hash;
};
FC_REFLECT( _abi_hash, (owner)(hash) );

using namespace eosio_system;

BOOST_AUTO_TEST_SUITE(eosio_system_tests)


// BOOST_FIXTURE_TEST_CASE( missed_blocks, eosio_system_tester ) try {
   
//    auto waitForSchedule = [&](vector<account_name> producer_names, int max_votable_producers, int type = -1){
//       int produced = 0;
//       if(type > 0){
//          auto initialPendingVersion = control->head_block_state()->pending_schedule.version;
//          auto initialActiveVersion = control->head_block_state()->active_schedule.version;
//          if(type > 1){
//             while(initialPendingVersion == control->head_block_state()->pending_schedule.version){
//                produce_blocks(1);
//                produced++;
//                // if(produced > max_votable_producers * 12){
//                   // printMetrics(producer_names);
//                // }
//             }
//             std::cout<<produced<<" for pending - ";
//          }

//          produced = 0;
//          while(initialActiveVersion == control->head_block_state()->active_schedule.version){
//             produce_blocks(1);
//             produced++;
//             // if(produced > max_votable_producers * 12){
//                // printMetrics(producer_names);
//             // }
//          }
//          std::cout<<produced<<" for active"<<std::endl;
//       }else if(type < 0){ //static skip
//          produced = 12 * max_votable_producers;
//          produce_blocks( produced );
//          produce_blocks( produced );
         
//          std::cout<<produced<<" for pending - ";
//          std::cout<<produced<<" for active"<<std::endl;
//       }
//    };

//    transfer( "eosio", "alice1111111", core_sym::from_string("650000000.0000"), "eosio" );
//    BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", "alice1111111", core_sym::from_string("300000000.0000"), core_sym::from_string("300000000.0000") ) );

//    //update producer count here   
//    int producer_count = 'z' - 'a' + 1;
//    int max_votable_producers = producer_count > 21 ? 21 : producer_count;
//    // create accounts {defproducera, defproducerb, ..., defproducerz} and register as producers
//    std::vector<account_name> producer_names;
//    {
//          producer_names.reserve(producer_count);
//          const std::string root("defproducer");
//          for ( char c = 'a'; c < 'a'+producer_count; ++c ) {
//             producer_names.emplace_back(root + std::string(1, c));
//          }
//          setup_producer_accounts(producer_names);
//          for (const auto& p: producer_names) {
//             BOOST_REQUIRE_EQUAL( success(), regproducer(p) );
//          }
//    }
//    produce_blocks(max_votable_producers * 12);

//    auto trace_auth = TESTER::push_action(config::system_account_name, updateauth::get_name(), config::system_account_name, mvo()
//                                              ("account", name(config::system_account_name).to_string())
//                                              ("permission", name(config::active_name).to_string())
//                                              ("parent", name(config::owner_name).to_string())
//                                              ("auth",  authority(1, {key_weight{get_public_key( config::system_account_name, "active" ), 1}}, {
//                                                    permission_level_weight{{config::system_account_name, config::eosio_code_name}, 1},
//                                                    permission_level_weight{{config::producers_account_name,  config::active_name}, 1}
//                                              }
//                                              ))
//    );
//    BOOST_REQUIRE_EQUAL(transaction_receipt::executed, trace_auth->receipt->status);

//    //vote for producers
//    {
//       transfer( config::system_account_name, "alice1111111", core_sym::from_string("100000000.0000"), config::system_account_name );
//       BOOST_REQUIRE_EQUAL(success(), stake( "alice1111111", core_sym::from_string("30000000.0000"), core_sym::from_string("30000000.0000") ) );
//       BOOST_REQUIRE_EQUAL(success(), buyram( "alice1111111", "alice1111111", core_sym::from_string("30000000.0000") ) );
//       BOOST_REQUIRE_EQUAL(success(), push_action(N(alice1111111), N(voteproducer), mvo()
//                                                 ("voter",  "alice1111111")
//                                                 ("proxy", name(0).to_string())
//                                                 ("producers", vector<account_name>(producer_names.begin(), producer_names.begin() + max_votable_producers))
//                         )
//       );
//    }

//    waitForSchedule(producer_names, max_votable_producers, 2);

//    auto producer_keys = control->head_block_state()->active_schedule.producers;
//    BOOST_REQUIRE_EQUAL( max_votable_producers, producer_keys.size() );
//    BOOST_REQUIRE_EQUAL( name("defproducera"), producer_names[0] );

//    wdump((control->head_block_state()));
//    wdump((producer_names));
//    wdump((producer_keys));

//    auto metrics = get_gmetrics_state();
//    wdump((metrics));

//    // how many times miss happens
//    int miss_counts = 10;

//    // which producers miss 2 = 2nd in the checking cylce, not in order or votes or anything
//    // and how many blocks to miss 
//    int producers_to_miss[] = { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2};
//    int blocks_to_miss[]    = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10};
   
//    // how many times should vote = length of vote_out / vote_in - 1
//    int voting_count = 4;
   
//    // when to apply the votes
//    int voting_cycle[] = {1, 4, 6, 8};

//    // the first 2,4 is to specify the lengths of the subsequent arrays - i know, lazy
//    // vote-out = who to remove from the top 21 'a' to 'u'
//    // then vote-in = who to add from the leftover 'v' to 'z'
//    // 3 = voting_count + 1
//    int vote_out[5][4] = {{2,4,4,4}, { 2,  3, -1, -1}, { 2,  3,  7,  8}, { 1,  2,  3,  4}, { 5,  6,  7,  8}}; // keep the numbers ordered
//    int vote_in[5][4] =  {{2,4,4,4}, {21, 25, -1, -1}, {21, 22, 23, 24}, {21, 22, 23, 25}, {21, 23, 24, 25}}; 

//    // how many cycles to run
//    int cycles = 80;

//    // helpers
//    int last_missed_prod = 0;
//    int last_voting = 0;
//    int last_register = 0;

//    int register_count = 2;
//    int register_cycle[] = {1, 3};
//    vector<vector<account_name>> registers;
//    vector<vector<account_name>> unregisters;
//    vector<account_name> tmp;

//    std::cout<<"before emplace"<<std::endl;
   
//    tmp = {};
//    registers.emplace_back(tmp);
//    tmp = {"defproducerb"};
//    unregisters.emplace_back(tmp);
   
//    registers.emplace_back(tmp);
//    tmp = {};
//    unregisters.emplace_back(tmp);

//    std::cout<<"after emplace"<<std::endl;

//    auto doVoting = [&](vector<account_name> producers, int cycle_to_apply, int voteout[3][4], int votein[3][4], int max_votable_producers){
//       vector<account_name> voted;
//       voted.reserve(30);

//       int voteoutSize = voteout[0][cycle_to_apply], lastVoteout = 0;
//       int* currentVoteout = voteout[cycle_to_apply+1];
//       int voteinSize = votein[0][cycle_to_apply], lastVotein = 0;
//       int* currentVotein = votein[cycle_to_apply+1];
//       int size = 0;
//       for(int i = 0; i < producer_count; i++){
//          if(lastVoteout < voteoutSize && currentVoteout[lastVoteout] == i){
//             lastVoteout++;
//             continue;
//          } 
//          if(i < max_votable_producers){
//             voted.emplace_back(producers[i]);
//             size++;
//          } else
//          if(lastVotein < voteinSize && currentVotein[lastVotein] == i){
//             lastVotein++;
//             voted.emplace_back(producers[i]);
//             size++;
//             continue;
//          }
//       }

//       std::cout<<"===== VOTING : [";
//       for(int i = 0 ; i < size ; i++){
//          std::cout<<voted[i]<<", ";
//       }
//       std::cout<<"]"<<std::endl;
//       BOOST_REQUIRE_EQUAL(success(), push_action(N(alice1111111), N(voteproducer), mvo()
//             ("voter",  "alice1111111")
//             ("proxy", name(0).to_string())
//             ("producers", voted)
//          )
//       );
//    };
   
//    // produce_blocks(12*max_votable_producers*cycles);
//    // for (const auto& p: unregisters.at(0)) {
//    //    BOOST_REQUIRE_EQUAL( 
//    //       success(), 
//    //       push_action(name(p), N(unregprod), mvo()("producer", p))
//    //    );
//    // }
//    // produce_blocks(12*max_votable_producers*cycles);


//    for(int cycle = 0; cycle < cycles; cycle++){
//       for(int producer = 0; producer < max_votable_producers; producer++){ 
//          for(int block = 0; block < 12; block++){
//             // std::cout<<cycle<<' '<<producer<<' '<<block<<std::endl;
//             if(last_missed_prod < miss_counts && producer == producers_to_miss[last_missed_prod]){
//                std::cout<<"miss blocks["<<blocks_to_miss[last_missed_prod]<<"] aka time["<<(blocks_to_miss[last_missed_prod] * 500 + 500)<<"]"<<std::endl;
//                block += blocks_to_miss[last_missed_prod];
//                produce_block(fc::milliseconds(blocks_to_miss[last_missed_prod] * 500 + 500));
//                last_missed_prod++;
//                printMetrics(producer_names);
//             }
            
//             produce_blocks(1);
//             printMetrics(producer_names);
//          }
//       }

//       if(producer_count > max_votable_producers && last_voting < voting_count && cycle == voting_cycle[last_voting]){
//          doVoting(producer_names, last_voting, vote_out, vote_in, max_votable_producers);
//          last_voting++;

//          waitForSchedule(producer_names, max_votable_producers, 2);
//          printMetrics(producer_names);
//       }

//       if(last_register < register_count && cycle == register_cycle[last_register]){
//          std::cout<<"RUNNING register/unregister "<<last_register<<std::endl;
//          for (const auto& p: registers.at(last_register)) {
//             BOOST_REQUIRE_EQUAL( success(), regproducer(p) );
//          }
//          for (const auto& p: unregisters.at(last_register)) {
//             BOOST_REQUIRE_EQUAL( 
//                success(), 
//                push_action(name(p), N(unregprod), mvo()("producer", p))
//             );
//          }
         
//          waitForSchedule(producer_names, max_votable_producers, 2);
//          printMetrics(producer_names);
//          last_register++;
//       }
//    }
   
//    // produce_blocks(2000);
//    // printMetrics(producer_names);
// } FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( bp_rotations, eosio_system_tester ) try {
   const asset net = core_sym::from_string("80.0000");
   const asset cpu = core_sym::from_string("80.0000");
   const std::vector<account_name> voters = { N(producvotera), N(producvoterb), N(producvoterc), N(producvoterd) };
   for (const auto& v: voters) {
      create_account_with_resources( v, config::system_account_name, core_sym::from_string("1.0000"), false, net, cpu );
      transfer( config::system_account_name, v, core_sym::from_string("100000000.0000"), config::system_account_name );
      BOOST_REQUIRE_EQUAL(success(), stake(v, core_sym::from_string("30000000.0000"), core_sym::from_string("30000000.0000")) );
   }

   std::vector<account_name> producer_names;
   {
      producer_names.reserve('z' - 'a' + 1);
      {
         const std::string root("produceridx");
         for ( char c = 'a'; c <= 'z'; ++c ) {
            producer_names.emplace_back(root + std::string(1, c));
         }
      }
      {
         const std::string root("zidproducer");
         for ( char c = 'a'; c <= 'z'; ++c ) {
            producer_names.emplace_back(root + std::string(1, c));
         }
      }
      setup_producer_accounts(producer_names);
      for (const auto& p: producer_names) {
         BOOST_REQUIRE_EQUAL( success(), regproducer(p) );
         produce_blocks(1);
         BOOST_TEST(0 == get_producer_info(p)["total_votes"].as<double>());
      }
   }

   std::cout<<"before activate"<<std::endl;
   activate_network();
   std::cout<<"after activate"<<std::endl;

   // base votes to make sure anyone can be switched around
   {
      // top 21 !!! << voting 21 will not trigger rotation , but will increase rotation timer >> !!!
      BOOST_REQUIRE_EQUAL(success(), vote(N(producvotera), vector<account_name>(producer_names.begin(), producer_names.begin()+21)));
      produce_blocks(2);

      // high stand-bys
      BOOST_REQUIRE_EQUAL(success(), vote(N(producvoterb), vector<account_name>(producer_names.begin()+21, producer_names.begin()+41)));
      // low stand-bys
      BOOST_REQUIRE_EQUAL(success(), vote(N(producvoterc), vector<account_name>(producer_names.begin()+41, producer_names.end())));
   }
   produce_blocks(2);


   // !!! TODO : PROBLEM !!! to check : rewards snapshot !!!
   // for(int i = 0; i < 10000; i++){
   //    std::cout<<i<<": "<<control->head_block_state()->block->producer<<" : "<<std::endl;
   //    wdump((control->head_block_state()->block->timestamp));
   //    wdump((get_rotation_state()));
   //    produce_blocks(1);
   // }

   //apply next rotation
   auto doRotation = [&](int offset = 6) {
      produce_block(fc::minutes(12*60 - offset)); // propose schedule with rotation
      produce_blocks(360); // give time for schedule to become pending (3 min)
      produce_blocks(360); // give time for schedule to become active (3 min)
   };

   //check active schedule to match expected active bps and rotation
   auto checkSchedule = [&](const vector<account_name>active, const vector<account_name>standby, const vector<producer_key>producers, const account_name& bp_out, const account_name& sbp_in) -> bool{
      bool isExpectedSchedule = true;
      for(int i = 0; i < producers.size() && isExpectedSchedule; i++){
         auto p = std::find(active.begin(), active.end(), producers[i].producer_name);
         
         if(p == active.end()){
            p = std::find(standby.begin(), standby.end(), producers[i].producer_name);

            // the producer from the schedule not in top 21[active] needs to be in 21-51[standby] and to be the rotated standby bp
            isExpectedSchedule = isExpectedSchedule && p != standby.end() && *p == sbp_in;
            continue;
         }
         
         // the producer from the schedule needs to be in top 21[active] and different from rotated bp
         isExpectedSchedule = isExpectedSchedule && *p != bp_out;
      }
      return isExpectedSchedule;
   };

   std::vector<account_name> active, standby;
   std::vector<producer_key> producers;
   int bp_rotated_out, sbp_rotated_in;
   account_name bp_out, sbp_in;
   
   active.reserve(21);
   standby.reserve(30);
   active.insert(active.end(), producer_names.begin(), producer_names.begin()+21);
   standby.insert(standby.end(), producer_names.begin()+21, producer_names.begin()+51);

   // produceridxa should be rotated with produceridxv
   
   std::cout<<"before rotation"<<std::endl;
   doRotation(0);
   std::cout<<"after rotation"<<std::endl;
   bp_rotated_out = 0;
   sbp_rotated_in = 21;
   bp_out = active[bp_rotated_out];
   sbp_in = standby[sbp_rotated_in - 21];
   active[bp_rotated_out] = sbp_in;
   standby[sbp_rotated_in - 21] = bp_out;
   
   producers = control->head_block_state()->active_schedule.producers;
   bool isExpectedSchedule = checkSchedule(active, standby, producers, bp_out, sbp_in);
   BOOST_REQUIRE(isExpectedSchedule);

   auto rotation = get_rotation_state();
   BOOST_REQUIRE(rotation["bp_currently_out"].as_string() == bp_out);
   BOOST_REQUIRE(rotation["sbp_currently_in"].as_string() == sbp_in);
   BOOST_REQUIRE(rotation["bp_out_index"].as_uint64() == bp_rotated_out);
   BOOST_REQUIRE(rotation["sbp_in_index"].as_uint64() == sbp_rotated_in);

   // produceridxb should be rotated with produceridxw
   std::cout<<"before rotation"<<std::endl;
   doRotation();
   std::cout<<"after rotation"<<std::endl;
   // undo last rotation
   active[bp_rotated_out] = bp_out;
   standby[sbp_rotated_in - 21] = sbp_in;

   // do next rotation
   bp_rotated_out = 1;
   sbp_rotated_in = 22;
   bp_out = active[ bp_rotated_out ];
   sbp_in = standby[ sbp_rotated_in - 21 ];
   active[bp_rotated_out] = sbp_in;
   standby[sbp_rotated_in - 21] = bp_out;

   producers = control->head_block_state()->active_schedule.producers;
   isExpectedSchedule = checkSchedule(active, standby, producers, bp_out, sbp_in);
   BOOST_REQUIRE(isExpectedSchedule);

   rotation = get_rotation_state();
   BOOST_REQUIRE(rotation["bp_currently_out"].as_string() == bp_out);
   BOOST_REQUIRE(rotation["sbp_currently_in"].as_string() == sbp_in);
   BOOST_REQUIRE(rotation["bp_out_index"].as_uint64() == bp_rotated_out);
   BOOST_REQUIRE(rotation["sbp_in_index"].as_uint64() == sbp_rotated_in);

   std::vector<account_name> tmpv;
   {
      // zidproducern + zidproducero will be voted in top 21
      // move the last 2 high-standby to the top, changing the order of sbp-in and bp-out , but still keeping them in their respective lists
      tmpv = vector<account_name>(producer_names.begin()+39, producer_names.end());

      // keep low standbys + last 2 high standby
      BOOST_REQUIRE_EQUAL(success(), vote(N(producvoterc), tmpv));

      // produceridxt + produceridxu will fall from top 21 to standby
      active.erase(active.begin()+19, active.begin()+21); 
      standby.insert(standby.begin(), producer_names.begin()+19, producer_names.begin()+21); 

      // zidproducern + zidproducero will be voted in top 21
      active.insert(active.begin(), producer_names.begin()+39, producer_names.begin()+41);
      standby.erase(standby.begin()+18, standby.begin()+20);
   }

   produce_blocks(360); // give time for schedule to become pending (3 min)
   produce_blocks(360); // give time for schedule to become active (3 min)

   producers = control->head_block_state()->active_schedule.producers;
   isExpectedSchedule = checkSchedule(active, standby, producers, bp_out, sbp_in);
   BOOST_REQUIRE(isExpectedSchedule);

   rotation = get_rotation_state();
   // local rotation info is correct and names stick after voting
   BOOST_REQUIRE(rotation["bp_currently_out"].as_string() == bp_out);
   BOOST_REQUIRE(rotation["sbp_currently_in"].as_string() == sbp_in);
   BOOST_REQUIRE(rotation["bp_out_index"].as_uint64() == bp_rotated_out);
   BOOST_REQUIRE(rotation["sbp_in_index"].as_uint64() == sbp_rotated_in);

   // indexes are off by 2 after voting
   BOOST_REQUIRE(active[bp_rotated_out + 2] == sbp_in);
   BOOST_REQUIRE(standby[sbp_rotated_in + 2 - 21] == bp_out);

   {
      // last state
      tmpv = vector<account_name>(producer_names.begin()+39, producer_names.end());
      // produceridxw will be added to the vote
      tmpv.insert(tmpv.begin(), sbp_in);
      
      // move produceridxw to top 21 
      BOOST_REQUIRE_EQUAL(success(), vote(N(producvoterc), tmpv));
      
      // undo last rotation
      active[bp_rotated_out + 2] = bp_out;
      standby[sbp_rotated_in + 2 - 21] = sbp_in;

      // produceridxs will fall from top 21 to standby
      active.pop_back(); 
      standby.insert(standby.begin(), producer_names.begin()+18, producer_names.begin()+19); 

      // produceridxw will be voted in top 21
      active.insert(active.begin(), sbp_in);
      standby.erase(standby.begin() + (sbp_rotated_in + 2 - 21) ); 

      bp_out = "";
      sbp_in = "";
   }

   produce_blocks(360); // give time for schedule to become pending (3 min)
   produce_blocks(360); // give time for schedule to become active (3 min)

   // after reset caused by sbp going out-of-list (promoted to top21 or under 51)
   // the rotaion indexes should stick [1, 22] but names should be ""
   rotation = get_rotation_state();
   BOOST_REQUIRE(rotation["bp_currently_out"].as_string() == bp_out);
   BOOST_REQUIRE(rotation["sbp_currently_in"].as_string() == sbp_in);
   BOOST_REQUIRE(rotation["bp_out_index"].as_uint64() == bp_rotated_out);
   BOOST_REQUIRE(rotation["sbp_in_index"].as_uint64() == sbp_rotated_in);
   
   producers = control->head_block_state()->active_schedule.producers;
   isExpectedSchedule = checkSchedule(active, standby, producers, bp_out, sbp_in);
   BOOST_REQUIRE(isExpectedSchedule);

   doRotation(6);

   // do new rotation as per usual
   // zidproducero should be rotated with produceridxu
   bp_rotated_out = 2;
   sbp_rotated_in = 23;
   bp_out = active[ bp_rotated_out ];
   sbp_in = standby[ sbp_rotated_in - 21 ];
   active[bp_rotated_out] = sbp_in;
   standby[sbp_rotated_in - 21] = bp_out;
   
   rotation = get_rotation_state();
   BOOST_REQUIRE(rotation["bp_currently_out"].as_string() == bp_out);
   BOOST_REQUIRE(rotation["sbp_currently_in"].as_string() == sbp_in);
   BOOST_REQUIRE(rotation["bp_out_index"].as_uint64() == bp_rotated_out);
   BOOST_REQUIRE(rotation["sbp_in_index"].as_uint64() == sbp_rotated_in);
   producers = control->head_block_state()->active_schedule.producers;
   isExpectedSchedule = checkSchedule(active, standby, producers, bp_out, sbp_in);
   BOOST_REQUIRE(isExpectedSchedule);

   //unregister producer zidproducero <rotated bp>
   BOOST_REQUIRE_EQUAL( success(), push_action(N(zidproducero), N(unregprod), mvo()
                                               ("producer",  "zidproducero")
                        )
   );
   
   produce_blocks(360); // give time for schedule to become pending (3 min)
   produce_blocks(360); // give time for schedule to become active (3 min)

   // undo last rotation
   active[bp_rotated_out] = bp_out;
   standby[sbp_rotated_in - 21] = sbp_in;

   // produceridxs will rise to top 21 from standby
   active.emplace_back(producer_names[18]); 
   standby.erase(standby.begin()); 

   // zidproducerp will rise from candidate to standby
   standby.emplace_back();

   // rotations resets
   bp_out = "";
   sbp_in = "";
   
   rotation = get_rotation_state();
   BOOST_REQUIRE(rotation["bp_currently_out"].as_string() == bp_out);
   BOOST_REQUIRE(rotation["sbp_currently_in"].as_string() == sbp_in);
   BOOST_REQUIRE(rotation["bp_out_index"].as_uint64() == bp_rotated_out);
   BOOST_REQUIRE(rotation["sbp_in_index"].as_uint64() == sbp_rotated_in);
   producers = control->head_block_state()->active_schedule.producers;
   isExpectedSchedule = checkSchedule(active, standby, producers, bp_out, sbp_in);
   BOOST_REQUIRE(isExpectedSchedule);

   // after reset, it will go back to normal rotation case 
   // this was tested above the unregister case 
   // standby promotion reset the rotation and went back to normal
} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( buysell, eosio_system_tester ) try {

   BOOST_REQUIRE_EQUAL( core_sym::from_string("0.0000"), get_balance( "alice1111111" ) );

   transfer( "eosio", "alice1111111", core_sym::from_string("1000.0000"), "eosio" );
   BOOST_REQUIRE_EQUAL( success(), stake( "eosio", "alice1111111", core_sym::from_string("200.0000"), core_sym::from_string("100.0000") ) );

   auto total = get_total_stake( "alice1111111" );
   auto init_bytes =  total["ram_bytes"].as_uint64();

   const asset initial_ram_balance = get_balance(N(eosio.ram));
   const asset initial_ramfee_balance = get_balance(N(eosio.ramfee));
   BOOST_REQUIRE_EQUAL( success(), buyram( "alice1111111", "alice1111111", core_sym::from_string("200.0000") ) );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("800.0000"), get_balance( "alice1111111" ) );
   BOOST_REQUIRE_EQUAL( initial_ram_balance + core_sym::from_string("199.0000"), get_balance(N(eosio.ram)) );
   BOOST_REQUIRE_EQUAL( initial_ramfee_balance + core_sym::from_string("1.0000"), get_balance(N(eosio.ramfee)) );

   total = get_total_stake( "alice1111111" );
   auto bytes = total["ram_bytes"].as_uint64();
   auto bought_bytes = bytes - init_bytes;
   wdump((init_bytes)(bought_bytes)(bytes) );

   BOOST_REQUIRE_EQUAL( true, 0 < bought_bytes );

   BOOST_REQUIRE_EQUAL( success(), sellram( "alice1111111", bought_bytes ) );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("998.0049"), get_balance( "alice1111111" ) );
   total = get_total_stake( "alice1111111" );
   BOOST_REQUIRE_EQUAL( true, total["ram_bytes"].as_uint64() == init_bytes );

   transfer( "eosio", "alice1111111", core_sym::from_string("100000000.0000"), "eosio" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("100000998.0049"), get_balance( "alice1111111" ) );
   // alice buys ram for 10000000.0000, 0.5% = 50000.0000 go to ramfee
   // after fee 9950000.0000 go to bought bytes
   // when selling back bought bytes, pay 0.5% fee and get back 99.5% of 9950000.0000 = 9900250.0000
   // expected account after that is 90000998.0049 + 9900250.0000 = 99901248.0049 with a difference
   // of order 0.0001 due to rounding errors
   BOOST_REQUIRE_EQUAL( success(), buyram( "alice1111111", "alice1111111", core_sym::from_string("10000000.0000") ) );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("90000998.0049"), get_balance( "alice1111111" ) );

   total = get_total_stake( "alice1111111" );
   bytes = total["ram_bytes"].as_uint64();
   bought_bytes = bytes - init_bytes;
   wdump((init_bytes)(bought_bytes)(bytes) );

   BOOST_REQUIRE_EQUAL( success(), sellram( "alice1111111", bought_bytes ) );
   total = get_total_stake( "alice1111111" );

   bytes = total["ram_bytes"].as_uint64();
   bought_bytes = bytes - init_bytes;
   wdump((init_bytes)(bought_bytes)(bytes) );

   BOOST_REQUIRE_EQUAL( true, total["ram_bytes"].as_uint64() == init_bytes );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("99901248.0040"), get_balance( "alice1111111" ) );

   BOOST_REQUIRE_EQUAL( success(), buyram( "alice1111111", "alice1111111", core_sym::from_string("100.0000") ) );
   BOOST_REQUIRE_EQUAL( success(), buyram( "alice1111111", "alice1111111", core_sym::from_string("100.0000") ) );
   BOOST_REQUIRE_EQUAL( success(), buyram( "alice1111111", "alice1111111", core_sym::from_string("100.0000") ) );
   BOOST_REQUIRE_EQUAL( success(), buyram( "alice1111111", "alice1111111", core_sym::from_string("100.0000") ) );
   BOOST_REQUIRE_EQUAL( success(), buyram( "alice1111111", "alice1111111", core_sym::from_string("100.0000") ) );
   BOOST_REQUIRE_EQUAL( success(), buyram( "alice1111111", "alice1111111", core_sym::from_string("10.0000") ) );
   BOOST_REQUIRE_EQUAL( success(), buyram( "alice1111111", "alice1111111", core_sym::from_string("10.0000") ) );
   BOOST_REQUIRE_EQUAL( success(), buyram( "alice1111111", "alice1111111", core_sym::from_string("10.0000") ) );
   BOOST_REQUIRE_EQUAL( success(), buyram( "alice1111111", "alice1111111", core_sym::from_string("30.0000") ) );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("99900688.0040"), get_balance( "alice1111111" ) );

   auto newtotal = get_total_stake( "alice1111111" );

   auto newbytes = newtotal["ram_bytes"].as_uint64();
   bought_bytes = newbytes - bytes;
   wdump((newbytes)(bytes)(bought_bytes) );

   BOOST_REQUIRE_EQUAL( success(), sellram( "alice1111111", bought_bytes ) );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("99901242.4175"), get_balance( "alice1111111" ) );

   newtotal = get_total_stake( "alice1111111" );
   auto startbytes = newtotal["ram_bytes"].as_uint64();

   BOOST_REQUIRE_EQUAL( success(), buyram( "alice1111111", "alice1111111", core_sym::from_string("10000000.0000") ) );
   BOOST_REQUIRE_EQUAL( success(), buyram( "alice1111111", "alice1111111", core_sym::from_string("10000000.0000") ) );
   BOOST_REQUIRE_EQUAL( success(), buyram( "alice1111111", "alice1111111", core_sym::from_string("10000000.0000") ) );
   BOOST_REQUIRE_EQUAL( success(), buyram( "alice1111111", "alice1111111", core_sym::from_string("10000000.0000") ) );
   BOOST_REQUIRE_EQUAL( success(), buyram( "alice1111111", "alice1111111", core_sym::from_string("10000000.0000") ) );
   BOOST_REQUIRE_EQUAL( success(), buyram( "alice1111111", "alice1111111", core_sym::from_string("100000.0000") ) );
   BOOST_REQUIRE_EQUAL( success(), buyram( "alice1111111", "alice1111111", core_sym::from_string("100000.0000") ) );
   BOOST_REQUIRE_EQUAL( success(), buyram( "alice1111111", "alice1111111", core_sym::from_string("100000.0000") ) );
   BOOST_REQUIRE_EQUAL( success(), buyram( "alice1111111", "alice1111111", core_sym::from_string("300000.0000") ) );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("49301242.4175"), get_balance( "alice1111111" ) );

   auto finaltotal = get_total_stake( "alice1111111" );
   auto endbytes = finaltotal["ram_bytes"].as_uint64();

   bought_bytes = endbytes - startbytes;
   wdump((startbytes)(endbytes)(bought_bytes) );

   BOOST_REQUIRE_EQUAL( success(), sellram( "alice1111111", bought_bytes ) );

   BOOST_REQUIRE_EQUAL( core_sym::from_string("99396507.4039"), get_balance( "alice1111111" ) );

} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( stake_unstake, eosio_system_tester ) try {
   activate_network();

   produce_blocks( 10 );
   produce_block( fc::hours(3*24) );

   BOOST_REQUIRE_EQUAL( core_sym::from_string("0.0000"), get_balance( "alice1111111" ) );
   transfer( "eosio", "alice1111111", core_sym::from_string("1000.0000"), "eosio" );

   BOOST_REQUIRE_EQUAL( core_sym::from_string("1000.0000"), get_balance( "alice1111111" ) );
   BOOST_REQUIRE_EQUAL( success(), stake( "eosio", "alice1111111", core_sym::from_string("200.0000"), core_sym::from_string("100.0000") ) );

   auto total = get_total_stake("alice1111111");
   BOOST_REQUIRE_EQUAL( core_sym::from_string("210.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("110.0000"), total["cpu_weight"].as<asset>());

   const auto init_eosio_stake_balance = get_balance( N(eosio.stake) );
   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", "alice1111111", core_sym::from_string("200.0000"), core_sym::from_string("100.0000") ) );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("700.0000"), get_balance( "alice1111111" ) );
   BOOST_REQUIRE_EQUAL( init_eosio_stake_balance + core_sym::from_string("300.0000"), get_balance( N(eosio.stake) ) );
   BOOST_REQUIRE_EQUAL( success(), unstake( "alice1111111", "alice1111111", core_sym::from_string("200.0000"), core_sym::from_string("100.0000") ) );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("700.0000"), get_balance( "alice1111111" ) );

   produce_block( fc::hours(3*24-1) );
   produce_blocks(1);
   BOOST_REQUIRE_EQUAL( core_sym::from_string("700.0000"), get_balance( "alice1111111" ) );
   BOOST_REQUIRE_EQUAL( init_eosio_stake_balance + core_sym::from_string("300.0000"), get_balance( N(eosio.stake) ) );
   //after 3 days funds should be released
   produce_block( fc::hours(1) );
   produce_blocks(1);
   BOOST_REQUIRE_EQUAL( core_sym::from_string("1000.0000"), get_balance( "alice1111111" ) );
   BOOST_REQUIRE_EQUAL( init_eosio_stake_balance, get_balance( N(eosio.stake) ) );

   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", "bob111111111", core_sym::from_string("200.0000"), core_sym::from_string("100.0000") ) );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("700.0000"), get_balance( "alice1111111" ) );
   total = get_total_stake("bob111111111");
   BOOST_REQUIRE_EQUAL( core_sym::from_string("210.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("110.0000"), total["cpu_weight"].as<asset>());

   total = get_total_stake( "alice1111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("210.0000").get_amount(), total["net_weight"].as<asset>().get_amount() );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("110.0000").get_amount(), total["cpu_weight"].as<asset>().get_amount() );

   REQUIRE_MATCHING_OBJECT( voter( "alice1111111", core_sym::from_string("300.0000")), get_voter_info( "alice1111111" ) );

   auto bytes = total["ram_bytes"].as_uint64();
   BOOST_REQUIRE_EQUAL( true, 0 < bytes );

   //unstake from bob111111111
   BOOST_REQUIRE_EQUAL( success(), unstake( "alice1111111", "bob111111111", core_sym::from_string("200.0000"), core_sym::from_string("100.0000") ) );
   total = get_total_stake("bob111111111");
   BOOST_REQUIRE_EQUAL( core_sym::from_string("10.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("10.0000"), total["cpu_weight"].as<asset>());
   produce_block( fc::hours(3*24-1) );
   produce_blocks(1);
   BOOST_REQUIRE_EQUAL( core_sym::from_string("700.0000"), get_balance( "alice1111111" ) );
   //after 3 days funds should be released
   produce_block( fc::hours(1) );
   produce_blocks(1);

   REQUIRE_MATCHING_OBJECT( voter( "alice1111111", core_sym::from_string("0.0000") ), get_voter_info( "alice1111111" ) );
   produce_blocks(1);
   BOOST_REQUIRE_EQUAL( core_sym::from_string("1000.0000"), get_balance( "alice1111111" ) );
} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( stake_unstake_with_transfer, eosio_system_tester ) try {
   activate_network();

   issue( "eosio", core_sym::from_string("1000.0000"), config::system_account_name );
   issue( "eosio.stake", core_sym::from_string("1000.0000"), config::system_account_name );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("0.0000"), get_balance( "alice1111111" ) );

   //eosio stakes for alice with transfer flag

   transfer( "eosio", "bob111111111", core_sym::from_string("1000.0000"), "eosio" );
   BOOST_REQUIRE_EQUAL( success(), stake_with_transfer( "bob111111111", "alice1111111", core_sym::from_string("200.0000"), core_sym::from_string("100.0000") ) );

   //check that alice has both bandwidth and voting power
   auto total = get_total_stake("alice1111111");
   BOOST_REQUIRE_EQUAL( core_sym::from_string("210.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("110.0000"), total["cpu_weight"].as<asset>());
   REQUIRE_MATCHING_OBJECT( voter( "alice1111111", core_sym::from_string("300.0000")), get_voter_info( "alice1111111" ) );

   BOOST_REQUIRE_EQUAL( core_sym::from_string("0.0000"), get_balance( "alice1111111" ) );

   //alice stakes for herself
   transfer( "eosio", "alice1111111", core_sym::from_string("1000.0000"), "eosio" );
   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", "alice1111111", core_sym::from_string("200.0000"), core_sym::from_string("100.0000") ) );
   //now alice's stake should be equal to transfered from eosio + own stake
   total = get_total_stake("alice1111111");
   BOOST_REQUIRE_EQUAL( core_sym::from_string("700.0000"), get_balance( "alice1111111" ) );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("410.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("210.0000"), total["cpu_weight"].as<asset>());
   REQUIRE_MATCHING_OBJECT( voter( "alice1111111", core_sym::from_string("600.0000")), get_voter_info( "alice1111111" ) );

   //alice can unstake everything (including what was transfered)
   BOOST_REQUIRE_EQUAL( success(), unstake( "alice1111111", "alice1111111", core_sym::from_string("400.0000"), core_sym::from_string("200.0000") ) );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("700.0000"), get_balance( "alice1111111" ) );

   produce_block( fc::hours(3*24-1) );
   produce_blocks(1);
   BOOST_REQUIRE_EQUAL( core_sym::from_string("700.0000"), get_balance( "alice1111111" ) );
   //after 3 days funds should be released

   produce_block( fc::hours(1) );
   produce_blocks(1);

   BOOST_REQUIRE_EQUAL( core_sym::from_string("1300.0000"), get_balance( "alice1111111" ) );

   //stake should be equal to what was staked in constructor, voting power should be 0
   total = get_total_stake("alice1111111");
   BOOST_REQUIRE_EQUAL( core_sym::from_string("10.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("10.0000"), total["cpu_weight"].as<asset>());
   REQUIRE_MATCHING_OBJECT( voter( "alice1111111", core_sym::from_string("0.0000")), get_voter_info( "alice1111111" ) );

   // Now alice stakes to bob with transfer flag
   BOOST_REQUIRE_EQUAL( success(), stake_with_transfer( "alice1111111", "bob111111111", core_sym::from_string("100.0000"), core_sym::from_string("100.0000") ) );

} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( stake_to_self_with_transfer, eosio_system_tester ) try {
   activate_network();

   BOOST_REQUIRE_EQUAL( core_sym::from_string("0.0000"), get_balance( "alice1111111" ) );
   transfer( "eosio", "alice1111111", core_sym::from_string("1000.0000"), "eosio" );

   BOOST_REQUIRE_EQUAL( wasm_assert_msg("cannot use transfer flag if delegating to self"),
                        stake_with_transfer( "alice1111111", "alice1111111", core_sym::from_string("200.0000"), core_sym::from_string("100.0000") )
   );

} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( stake_while_pending_refund, eosio_system_tester ) try {
   activate_network();

   issue( "eosio", core_sym::from_string("1000.0000"), config::system_account_name );
   issue( "eosio.stake", core_sym::from_string("1000.0000"), config::system_account_name );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("0.0000"), get_balance( "alice1111111" ) );

   //eosio stakes for alice with transfer flag

   transfer( "eosio", "bob111111111", core_sym::from_string("1000.0000"), "eosio" );
   BOOST_REQUIRE_EQUAL( success(), stake_with_transfer( "bob111111111", "alice1111111", core_sym::from_string("200.0000"), core_sym::from_string("100.0000") ) );

   //check that alice has both bandwidth and voting power
   auto total = get_total_stake("alice1111111");
   BOOST_REQUIRE_EQUAL( core_sym::from_string("210.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("110.0000"), total["cpu_weight"].as<asset>());
   REQUIRE_MATCHING_OBJECT( voter( "alice1111111", core_sym::from_string("300.0000")), get_voter_info( "alice1111111" ) );

   BOOST_REQUIRE_EQUAL( core_sym::from_string("0.0000"), get_balance( "alice1111111" ) );

   //alice stakes for herself
   transfer( "eosio", "alice1111111", core_sym::from_string("1000.0000"), "eosio" );
   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", "alice1111111", core_sym::from_string("200.0000"), core_sym::from_string("100.0000") ) );
   //now alice's stake should be equal to transfered from eosio + own stake
   total = get_total_stake("alice1111111");
   BOOST_REQUIRE_EQUAL( core_sym::from_string("700.0000"), get_balance( "alice1111111" ) );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("410.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("210.0000"), total["cpu_weight"].as<asset>());
   REQUIRE_MATCHING_OBJECT( voter( "alice1111111", core_sym::from_string("600.0000")), get_voter_info( "alice1111111" ) );

   //alice can unstake everything (including what was transfered)
   BOOST_REQUIRE_EQUAL( success(), unstake( "alice1111111", "alice1111111", core_sym::from_string("400.0000"), core_sym::from_string("200.0000") ) );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("700.0000"), get_balance( "alice1111111" ) );

   produce_block( fc::hours(3*24-1) );
   produce_blocks(1);
   BOOST_REQUIRE_EQUAL( core_sym::from_string("700.0000"), get_balance( "alice1111111" ) );
   //after 3 days funds should be released

   produce_block( fc::hours(1) );
   produce_blocks(1);

   BOOST_REQUIRE_EQUAL( core_sym::from_string("1300.0000"), get_balance( "alice1111111" ) );

   //stake should be equal to what was staked in constructor, voting power should be 0
   total = get_total_stake("alice1111111");
   BOOST_REQUIRE_EQUAL( core_sym::from_string("10.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("10.0000"), total["cpu_weight"].as<asset>());
   REQUIRE_MATCHING_OBJECT( voter( "alice1111111", core_sym::from_string("0.0000")), get_voter_info( "alice1111111" ) );

   // Now alice stakes to bob with transfer flag
   BOOST_REQUIRE_EQUAL( success(), stake_with_transfer( "alice1111111", "bob111111111", core_sym::from_string("100.0000"), core_sym::from_string("100.0000") ) );

} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( fail_without_auth, eosio_system_tester ) try {
   activate_network();

   issue( "alice1111111", core_sym::from_string("1000.0000"),  config::system_account_name );

   BOOST_REQUIRE_EQUAL( success(), stake( "eosio", "alice1111111", core_sym::from_string("2000.0000"), core_sym::from_string("1000.0000") ) );
   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", "bob111111111", core_sym::from_string("10.0000"), core_sym::from_string("10.0000") ) );

   BOOST_REQUIRE_EQUAL( error("missing authority of alice1111111"),
                        push_action( N(alice1111111), N(delegatebw), mvo()
                                    ("from",     "alice1111111")
                                    ("receiver", "bob111111111")
                                    ("stake_net_quantity", core_sym::from_string("10.0000"))
                                    ("stake_cpu_quantity", core_sym::from_string("10.0000"))
                                    ("transfer", 0 )
                                    ,false
                        )
   );

   BOOST_REQUIRE_EQUAL( error("missing authority of alice1111111"),
                        push_action(N(alice1111111), N(undelegatebw), mvo()
                                    ("from",     "alice1111111")
                                    ("receiver", "bob111111111")
                                    ("unstake_net_quantity", core_sym::from_string("200.0000"))
                                    ("unstake_cpu_quantity", core_sym::from_string("100.0000"))
                                    ("transfer", 0 )
                                    ,false
                        )
   );
   //REQUIRE_MATCHING_OBJECT( , get_voter_info( "alice1111111" ) );
} FC_LOG_AND_RETHROW()


BOOST_FIXTURE_TEST_CASE( stake_negative, eosio_system_tester ) try {
   issue( "alice1111111", core_sym::from_string("1000.0000"),  config::system_account_name );

   BOOST_REQUIRE_EQUAL( wasm_assert_msg("must stake a positive amount"),
                        stake( "alice1111111", core_sym::from_string("-0.0001"), core_sym::from_string("0.0000") )
   );

   BOOST_REQUIRE_EQUAL( wasm_assert_msg("must stake a positive amount"),
                        stake( "alice1111111", core_sym::from_string("0.0000"), core_sym::from_string("-0.0001") )
   );

   BOOST_REQUIRE_EQUAL( wasm_assert_msg("must stake a positive amount"),
                        stake( "alice1111111", core_sym::from_string("00.0000"), core_sym::from_string("00.0000") )
   );

   BOOST_REQUIRE_EQUAL( wasm_assert_msg("must stake a positive amount"),
                        stake( "alice1111111", core_sym::from_string("0.0000"), core_sym::from_string("00.0000") )

   );

   BOOST_REQUIRE_EQUAL( true, get_voter_info( "alice1111111" ).is_null() );
} FC_LOG_AND_RETHROW()


BOOST_FIXTURE_TEST_CASE( unstake_negative, eosio_system_tester ) try {
   issue( "alice1111111", core_sym::from_string("1000.0000"),  config::system_account_name );

   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", "bob111111111", core_sym::from_string("200.0001"), core_sym::from_string("100.0001") ) );

   auto total = get_total_stake( "bob111111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("210.0001"), total["net_weight"].as<asset>());
   auto vinfo = get_voter_info("alice1111111" );
   wdump((vinfo));
   REQUIRE_MATCHING_OBJECT( voter( "alice1111111", core_sym::from_string("300.0002") ), get_voter_info( "alice1111111" ) );


   BOOST_REQUIRE_EQUAL( wasm_assert_msg("must unstake a positive amount"),
                        unstake( "alice1111111", "bob111111111", core_sym::from_string("-1.0000"), core_sym::from_string("0.0000") )
   );

   BOOST_REQUIRE_EQUAL( wasm_assert_msg("must unstake a positive amount"),
                        unstake( "alice1111111", "bob111111111", core_sym::from_string("0.0000"), core_sym::from_string("-1.0000") )
   );

   //unstake all zeros
   BOOST_REQUIRE_EQUAL( wasm_assert_msg("must unstake a positive amount"),
                        unstake( "alice1111111", "bob111111111", core_sym::from_string("0.0000"), core_sym::from_string("0.0000") )

   );

} FC_LOG_AND_RETHROW()


BOOST_FIXTURE_TEST_CASE( unstake_more_than_at_stake, eosio_system_tester ) try {
   activate_network();

   issue( "alice1111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", core_sym::from_string("200.0000"), core_sym::from_string("100.0000") ) );

   auto total = get_total_stake( "alice1111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("210.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("110.0000"), total["cpu_weight"].as<asset>());

   BOOST_REQUIRE_EQUAL( core_sym::from_string("700.0000"), get_balance( "alice1111111" ) );

   //trying to unstake more net bandwith than at stake

   BOOST_REQUIRE_EQUAL( wasm_assert_msg("insufficient staked net bandwidth"),
                        unstake( "alice1111111", core_sym::from_string("200.0001"), core_sym::from_string("0.0000") )
   );

   //trying to unstake more cpu bandwith than at stake
   BOOST_REQUIRE_EQUAL( wasm_assert_msg("insufficient staked cpu bandwidth"),
                        unstake( "alice1111111", core_sym::from_string("0.0000"), core_sym::from_string("100.0001") )

   );

   //check that nothing has changed
   total = get_total_stake( "alice1111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("210.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("110.0000"), total["cpu_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("700.0000"), get_balance( "alice1111111" ) );
} FC_LOG_AND_RETHROW()


BOOST_FIXTURE_TEST_CASE( delegate_to_another_user, eosio_system_tester ) try {
   activate_network();

   issue( "alice1111111", core_sym::from_string("1000.0000"),  config::system_account_name );

   BOOST_REQUIRE_EQUAL( success(), stake ( "alice1111111", "bob111111111", core_sym::from_string("200.0000"), core_sym::from_string("100.0000") ) );

   auto total = get_total_stake( "bob111111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("210.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("110.0000"), total["cpu_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("700.0000"), get_balance( "alice1111111" ) );
   //all voting power goes to alice1111111
   REQUIRE_MATCHING_OBJECT( voter( "alice1111111", core_sym::from_string("300.0000") ), get_voter_info( "alice1111111" ) );
   //but not to bob111111111
   BOOST_REQUIRE_EQUAL( true, get_voter_info( "bob111111111" ).is_null() );

   //bob111111111 should not be able to unstake what was staked by alice1111111
   BOOST_REQUIRE_EQUAL( wasm_assert_msg("insufficient staked cpu bandwidth"),
                        unstake( "bob111111111", core_sym::from_string("0.0000"), core_sym::from_string("10.0000") )

   );
   BOOST_REQUIRE_EQUAL( wasm_assert_msg("insufficient staked net bandwidth"),
                        unstake( "bob111111111", core_sym::from_string("10.0000"),  core_sym::from_string("0.0000") )
   );

   issue( "carol1111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), stake( "carol1111111", "bob111111111", core_sym::from_string("20.0000"), core_sym::from_string("10.0000") ) );
   total = get_total_stake( "bob111111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("230.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("120.0000"), total["cpu_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("970.0000"), get_balance( "carol1111111" ) );
   REQUIRE_MATCHING_OBJECT( voter( "carol1111111", core_sym::from_string("30.0000") ), get_voter_info( "carol1111111" ) );

   //alice1111111 should not be able to unstake money staked by carol1111111

   BOOST_REQUIRE_EQUAL( wasm_assert_msg("insufficient staked net bandwidth"),
                        unstake( "alice1111111", "bob111111111", core_sym::from_string("2001.0000"), core_sym::from_string("1.0000") )
   );

   BOOST_REQUIRE_EQUAL( wasm_assert_msg("insufficient staked cpu bandwidth"),
                        unstake( "alice1111111", "bob111111111", core_sym::from_string("1.0000"), core_sym::from_string("101.0000") )

   );

   total = get_total_stake( "bob111111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("230.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("120.0000"), total["cpu_weight"].as<asset>());
   //balance should not change after unsuccessfull attempts to unstake
   BOOST_REQUIRE_EQUAL( core_sym::from_string("700.0000"), get_balance( "alice1111111" ) );
   //voting power too
   REQUIRE_MATCHING_OBJECT( voter( "alice1111111", core_sym::from_string("300.0000") ), get_voter_info( "alice1111111" ) );
   REQUIRE_MATCHING_OBJECT( voter( "carol1111111", core_sym::from_string("30.0000") ), get_voter_info( "carol1111111" ) );
   BOOST_REQUIRE_EQUAL( true, get_voter_info( "bob111111111" ).is_null() );
} FC_LOG_AND_RETHROW()


BOOST_FIXTURE_TEST_CASE( stake_unstake_separate, eosio_system_tester ) try {
   activate_network();

   issue( "alice1111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("1000.0000"), get_balance( "alice1111111" ) );

   //everything at once
   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", core_sym::from_string("10.0000"), core_sym::from_string("20.0000") ) );
   auto total = get_total_stake( "alice1111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("20.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("30.0000"), total["cpu_weight"].as<asset>());

   //cpu
   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", core_sym::from_string("100.0000"), core_sym::from_string("0.0000") ) );
   total = get_total_stake( "alice1111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("120.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("30.0000"), total["cpu_weight"].as<asset>());

   //net
   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", core_sym::from_string("0.0000"), core_sym::from_string("200.0000") ) );
   total = get_total_stake( "alice1111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("120.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("230.0000"), total["cpu_weight"].as<asset>());

   //unstake cpu
   BOOST_REQUIRE_EQUAL( success(), unstake( "alice1111111", core_sym::from_string("100.0000"), core_sym::from_string("0.0000") ) );
   total = get_total_stake( "alice1111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("20.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("230.0000"), total["cpu_weight"].as<asset>());

   //unstake net
   BOOST_REQUIRE_EQUAL( success(), unstake( "alice1111111", core_sym::from_string("0.0000"), core_sym::from_string("200.0000") ) );
   total = get_total_stake( "alice1111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("20.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("30.0000"), total["cpu_weight"].as<asset>());
} FC_LOG_AND_RETHROW()


BOOST_FIXTURE_TEST_CASE( adding_stake_partial_unstake, eosio_system_tester ) try {
   activate_network();

   issue( "alice1111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", "bob111111111", core_sym::from_string("200.0000"), core_sym::from_string("100.0000") ) );

   REQUIRE_MATCHING_OBJECT( voter( "alice1111111", core_sym::from_string("300.0000") ), get_voter_info( "alice1111111" ) );

   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", "bob111111111", core_sym::from_string("100.0000"), core_sym::from_string("50.0000") ) );

   auto total = get_total_stake( "bob111111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("310.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("160.0000"), total["cpu_weight"].as<asset>());
   REQUIRE_MATCHING_OBJECT( voter( "alice1111111", core_sym::from_string("450.0000") ), get_voter_info( "alice1111111" ) );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("550.0000"), get_balance( "alice1111111" ) );

   //unstake a share
   BOOST_REQUIRE_EQUAL( success(), unstake( "alice1111111", "bob111111111", core_sym::from_string("150.0000"), core_sym::from_string("75.0000") ) );

   total = get_total_stake( "bob111111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("160.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("85.0000"), total["cpu_weight"].as<asset>());
   REQUIRE_MATCHING_OBJECT( voter( "alice1111111", core_sym::from_string("225.0000") ), get_voter_info( "alice1111111" ) );

   //unstake more
   BOOST_REQUIRE_EQUAL( success(), unstake( "alice1111111", "bob111111111", core_sym::from_string("50.0000"), core_sym::from_string("25.0000") ) );
   total = get_total_stake( "bob111111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("110.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("60.0000"), total["cpu_weight"].as<asset>());
   REQUIRE_MATCHING_OBJECT( voter( "alice1111111", core_sym::from_string("150.0000") ), get_voter_info( "alice1111111" ) );

   //combined amount should be available only in 3 days
   produce_block( fc::days(2) );
   produce_blocks(1);
   BOOST_REQUIRE_EQUAL( core_sym::from_string("550.0000"), get_balance( "alice1111111" ) );
   produce_block( fc::days(1) );
   produce_blocks(1);
   BOOST_REQUIRE_EQUAL( core_sym::from_string("850.0000"), get_balance( "alice1111111" ) );

} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( stake_from_refund, eosio_system_tester ) try {
   activate_network();

   issue( "alice1111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", "alice1111111", core_sym::from_string("200.0000"), core_sym::from_string("100.0000") ) );

   auto total = get_total_stake( "alice1111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("210.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("110.0000"), total["cpu_weight"].as<asset>());

   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", "bob111111111", core_sym::from_string("50.0000"), core_sym::from_string("50.0000") ) );

   total = get_total_stake( "bob111111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("60.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("60.0000"), total["cpu_weight"].as<asset>());

   REQUIRE_MATCHING_OBJECT( voter( "alice1111111", core_sym::from_string("400.0000") ), get_voter_info( "alice1111111" ) );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("600.0000"), get_balance( "alice1111111" ) );

   //unstake a share
   BOOST_REQUIRE_EQUAL( success(), unstake( "alice1111111", "alice1111111", core_sym::from_string("100.0000"), core_sym::from_string("50.0000") ) );
   total = get_total_stake( "alice1111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("110.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("60.0000"), total["cpu_weight"].as<asset>());
   REQUIRE_MATCHING_OBJECT( voter( "alice1111111", core_sym::from_string("250.0000") ), get_voter_info( "alice1111111" ) );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("600.0000"), get_balance( "alice1111111" ) );
   auto refund = get_refund_request( "alice1111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("100.0000"), refund["net_amount"].as<asset>() );
   BOOST_REQUIRE_EQUAL( core_sym::from_string( "50.0000"), refund["cpu_amount"].as<asset>() );
   //XXX auto request_time = refund["request_time"].as_int64();

   //alice delegates to bob, should pull from liquid balance not refund
   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", "bob111111111", core_sym::from_string("50.0000"), core_sym::from_string("50.0000") ) );
   total = get_total_stake( "alice1111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("110.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("60.0000"), total["cpu_weight"].as<asset>());
   REQUIRE_MATCHING_OBJECT( voter( "alice1111111", core_sym::from_string("350.0000") ), get_voter_info( "alice1111111" ) );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("500.0000"), get_balance( "alice1111111" ) );
   refund = get_refund_request( "alice1111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("100.0000"), refund["net_amount"].as<asset>() );
   BOOST_REQUIRE_EQUAL( core_sym::from_string( "50.0000"), refund["cpu_amount"].as<asset>() );

   //stake less than pending refund, entire amount should be taken from refund
   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", "alice1111111", core_sym::from_string("50.0000"), core_sym::from_string("25.0000") ) );
   total = get_total_stake( "alice1111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("160.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("85.0000"), total["cpu_weight"].as<asset>());
   refund = get_refund_request( "alice1111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("50.0000"), refund["net_amount"].as<asset>() );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("25.0000"), refund["cpu_amount"].as<asset>() );
   //request time should stay the same
   //BOOST_REQUIRE_EQUAL( request_time, refund["request_time"].as_int64() );
   //balance should stay the same
   BOOST_REQUIRE_EQUAL( core_sym::from_string("500.0000"), get_balance( "alice1111111" ) );

   //stake exactly pending refund amount
   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", "alice1111111", core_sym::from_string("50.0000"), core_sym::from_string("25.0000") ) );
   total = get_total_stake( "alice1111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("210.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("110.0000"), total["cpu_weight"].as<asset>());
   //pending refund should be removed
   refund = get_refund_request( "alice1111111" );
   BOOST_TEST_REQUIRE( refund.is_null() );
   //balance should stay the same
   BOOST_REQUIRE_EQUAL( core_sym::from_string("500.0000"), get_balance( "alice1111111" ) );

   //create pending refund again
   BOOST_REQUIRE_EQUAL( success(), unstake( "alice1111111", "alice1111111", core_sym::from_string("200.0000"), core_sym::from_string("100.0000") ) );
   total = get_total_stake( "alice1111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("10.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("10.0000"), total["cpu_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("500.0000"), get_balance( "alice1111111" ) );
   refund = get_refund_request( "alice1111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("200.0000"), refund["net_amount"].as<asset>() );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("100.0000"), refund["cpu_amount"].as<asset>() );

   //stake more than pending refund
   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", "alice1111111", core_sym::from_string("300.0000"), core_sym::from_string("200.0000") ) );
   total = get_total_stake( "alice1111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("310.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("210.0000"), total["cpu_weight"].as<asset>());
   REQUIRE_MATCHING_OBJECT( voter( "alice1111111", core_sym::from_string("700.0000") ), get_voter_info( "alice1111111" ) );
   refund = get_refund_request( "alice1111111" );
   BOOST_TEST_REQUIRE( refund.is_null() );
   //200 core tokens should be taken from alice's account
   BOOST_REQUIRE_EQUAL( core_sym::from_string("300.0000"), get_balance( "alice1111111" ) );

} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( stake_to_another_user_not_from_refund, eosio_system_tester ) try {
   activate_network();

   issue( "alice1111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", core_sym::from_string("200.0000"), core_sym::from_string("100.0000") ) );

   auto total = get_total_stake( "alice1111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("210.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("110.0000"), total["cpu_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("700.0000"), get_balance( "alice1111111" ) );

   REQUIRE_MATCHING_OBJECT( voter( "alice1111111", core_sym::from_string("300.0000") ), get_voter_info( "alice1111111" ) );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("700.0000"), get_balance( "alice1111111" ) );

   //unstake
   BOOST_REQUIRE_EQUAL( success(), unstake( "alice1111111", core_sym::from_string("200.0000"), core_sym::from_string("100.0000") ) );
   auto refund = get_refund_request( "alice1111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("200.0000"), refund["net_amount"].as<asset>() );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("100.0000"), refund["cpu_amount"].as<asset>() );
   //auto orig_request_time = refund["request_time"].as_int64();

   //stake to another user
   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", "bob111111111", core_sym::from_string("200.0000"), core_sym::from_string("100.0000") ) );
   total = get_total_stake( "bob111111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("210.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("110.0000"), total["cpu_weight"].as<asset>());
   //stake should be taken from alices' balance, and refund request should stay the same
   BOOST_REQUIRE_EQUAL( core_sym::from_string("400.0000"), get_balance( "alice1111111" ) );
   refund = get_refund_request( "alice1111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("200.0000"), refund["net_amount"].as<asset>() );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("100.0000"), refund["cpu_amount"].as<asset>() );
   //BOOST_REQUIRE_EQUAL( orig_request_time, refund["request_time"].as_int64() );

} FC_LOG_AND_RETHROW()

// Tests for voting
BOOST_FIXTURE_TEST_CASE( producer_register_unregister, eosio_system_tester ) try {
   issue( "alice1111111", core_sym::from_string("1000.0000"),  config::system_account_name );

   //fc::variant params = producer_parameters_example(1);
   auto key =  fc::crypto::public_key( std::string("EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV") );
   BOOST_REQUIRE_EQUAL( success(), push_action(N(alice1111111), N(regproducer), mvo()
                                               ("producer",  "alice1111111")
                                               ("producer_key", key )
                                               ("url", "http://block.one")
                                               ("location", 1)
                        )
   );

   auto info = get_producer_info( "alice1111111" );
   BOOST_REQUIRE_EQUAL( "alice1111111", info["owner"].as_string() );
   BOOST_REQUIRE_EQUAL( 0, info["total_votes"].as_double() );
   BOOST_REQUIRE_EQUAL( "http://block.one", info["url"].as_string() );

   //change parameters one by one to check for things like #3783
   //fc::variant params2 = producer_parameters_example(2);
   BOOST_REQUIRE_EQUAL( success(), push_action(N(alice1111111), N(regproducer), mvo()
                                               ("producer",  "alice1111111")
                                               ("producer_key", key )
                                               ("url", "http://block.two")
                                               ("location", 1)
                        )
   );
   info = get_producer_info( "alice1111111" );
   BOOST_REQUIRE_EQUAL( "alice1111111", info["owner"].as_string() );
   BOOST_REQUIRE_EQUAL( key, fc::crypto::public_key(info["producer_key"].as_string()) );
   BOOST_REQUIRE_EQUAL( "http://block.two", info["url"].as_string() );
   BOOST_REQUIRE_EQUAL( 1, info["location"].as_int64() );

   auto key2 =  fc::crypto::public_key( std::string("EOS5eVr9TVnqwnUBNwf9kwMTbrHvX5aPyyEG97dz2b2TNeqWRzbJf") );
   BOOST_REQUIRE_EQUAL( success(), push_action(N(alice1111111), N(regproducer), mvo()
                                               ("producer",  "alice1111111")
                                               ("producer_key", key2 )
                                               ("url", "http://block.two")
                                               ("location", 2)
                        )
   );
   info = get_producer_info( "alice1111111" );
   BOOST_REQUIRE_EQUAL( "alice1111111", info["owner"].as_string() );
   BOOST_REQUIRE_EQUAL( key2, fc::crypto::public_key(info["producer_key"].as_string()) );
   BOOST_REQUIRE_EQUAL( "http://block.two", info["url"].as_string() );
   BOOST_REQUIRE_EQUAL( 2, info["location"].as_int64() );

   //unregister producer
   BOOST_REQUIRE_EQUAL( success(), push_action(N(alice1111111), N(unregprod), mvo()
                                               ("producer",  "alice1111111")
                        )
   );
   info = get_producer_info( "alice1111111" );
   //key should be empty
   BOOST_REQUIRE_EQUAL( fc::crypto::public_key(), fc::crypto::public_key(info["producer_key"].as_string()) );
   //everything else should stay the same
   BOOST_REQUIRE_EQUAL( "alice1111111", info["owner"].as_string() );
   BOOST_REQUIRE_EQUAL( 0, info["total_votes"].as_double() );
   BOOST_REQUIRE_EQUAL( "http://block.two", info["url"].as_string() );

   //unregister bob111111111 who is not a producer
   BOOST_REQUIRE_EQUAL( wasm_assert_msg( "producer not found" ),
                        push_action( N(bob111111111), N(unregprod), mvo()
                                     ("producer",  "bob111111111")
                        )
   );

} FC_LOG_AND_RETHROW()


BOOST_FIXTURE_TEST_CASE( vote_for_producer, eosio_system_tester, * boost::unit_test::tolerance(1e-4) ) try {
   activate_network();

   issue( "alice1111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   fc::variant params = producer_parameters_example(1);
   BOOST_REQUIRE_EQUAL( success(), push_action( N(alice1111111), N(regproducer), mvo()
                                               ("producer",  "alice1111111")
                                               ("producer_key", get_public_key( N(alice1111111), "active") )
                                               ("url", "http://block.one")
                                               ("location", 0 )
                        )
   );
   // ALICE is the SINGLE producer in this test case, so we can also test the total_producer_vote_weight for all the actions

   auto prod = get_producer_info( "alice1111111" );
   BOOST_REQUIRE_EQUAL( "alice1111111", prod["owner"].as_string() );
   BOOST_REQUIRE_EQUAL( 0, prod["total_votes"].as_double() );
   BOOST_REQUIRE_EQUAL( "http://block.one", prod["url"].as_string() );

   issue( "bob111111111", core_sym::from_string("2000.0000"),  config::system_account_name );
   issue( "carol1111111", core_sym::from_string("3000.0000"),  config::system_account_name );

   //bob111111111 makes stake
   BOOST_REQUIRE_EQUAL( success(), stake( "bob111111111", core_sym::from_string("11.0000"), core_sym::from_string("0.1111") ) );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("1988.8889"), get_balance( "bob111111111" ) );
   REQUIRE_MATCHING_OBJECT( voter( "bob111111111", core_sym::from_string("11.1111") ), get_voter_info( "bob111111111" ) );

   BOOST_REQUIRE_EQUAL( get_global_state()["total_producer_vote_weight"].as<double>(), get_producer_info( "alice1111111" )["total_votes"].as_double() );
   
	auto total = get_total_stake("bob111111111");
   //bob111111111 votes for alice1111111
   BOOST_REQUIRE_EQUAL( success(), vote( N(bob111111111), { N(alice1111111) } ) );
   
   //check that producer parameters stay the same after voting
   prod = get_producer_info( "alice1111111" );
   BOOST_TEST( stake2votes(core_sym::from_string("11.1111"), 1, 1) == prod["total_votes"].as_double() );
   BOOST_REQUIRE_EQUAL( "alice1111111", prod["owner"].as_string() );
   BOOST_REQUIRE_EQUAL( "http://block.one", prod["url"].as_string() );
   BOOST_REQUIRE_EQUAL( get_global_state()["total_producer_vote_weight"].as<double>(), get_producer_info( "alice1111111" )["total_votes"].as_double() );

   //carol1111111 makes stake
   BOOST_REQUIRE_EQUAL( success(), stake( "carol1111111", core_sym::from_string("22.0000"), core_sym::from_string("0.2222") ) );
   REQUIRE_MATCHING_OBJECT( voter( "carol1111111", core_sym::from_string("22.2222") ), get_voter_info( "carol1111111" ) );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("2977.7778"), get_balance( "carol1111111" ) );
   
	total = get_total_stake("carol1111111");
	//carol1111111 votes for alice1111111
   BOOST_REQUIRE_EQUAL( success(), vote( N(carol1111111), { N(alice1111111) } ) );
   
   //new stake votes be added to alice1111111's total_votes
   prod = get_producer_info( "alice1111111" );
   BOOST_TEST( stake2votes(core_sym::from_string("22.2222"), 1, 1) + stake2votes(core_sym::from_string("11.1111"), 1, 1) == prod["total_votes"].as_double() );
   BOOST_REQUIRE_EQUAL( get_global_state()["total_producer_vote_weight"].as<double>(), get_producer_info( "alice1111111" )["total_votes"].as_double() );
   
   //bob111111111 increases his stake
   BOOST_REQUIRE_EQUAL( success(), stake( "bob111111111", core_sym::from_string("33.0000"), core_sym::from_string("0.3333") ) );
   
   prod = get_producer_info( "alice1111111" );
   BOOST_TEST( stake2votes(core_sym::from_string("22.2222"), 1, 1) + stake2votes(core_sym::from_string("44.4444"), 1, 1) == prod["total_votes"].as_double() );
   BOOST_REQUIRE_EQUAL( get_global_state()["total_producer_vote_weight"].as<double>(), get_producer_info( "alice1111111" )["total_votes"].as_double() );

	total = get_total_stake("bob111111111");
  
   //alice1111111 stake with transfer to bob111111111
   BOOST_REQUIRE_EQUAL( success(), stake_with_transfer( "alice1111111", "bob111111111", core_sym::from_string("22.0000"), core_sym::from_string("0.2222") ) );
   
   total = get_total_stake("bob111111111");
	total = get_total_stake("carol1111111");
	 
   //should increase alice1111111's total_votes
   prod = get_producer_info( "alice1111111" );
   BOOST_TEST( stake2votes(core_sym::from_string("22.2222"), 1, 1) + stake2votes(core_sym::from_string("66.6666"), 1, 1) == prod["total_votes"].as_double() );
   BOOST_REQUIRE_EQUAL( get_global_state()["total_producer_vote_weight"].as<double>(), get_producer_info( "alice1111111" )["total_votes"].as_double() );

   //carol1111111 unstakes part of the stake
   BOOST_REQUIRE_EQUAL( success(), unstake( "carol1111111", core_sym::from_string("2.0000"), core_sym::from_string("0.0002")/*"2.0000 EOS", "0.0002 EOS"*/ ) );
   
	total = get_total_stake("carol1111111");
  
   //should decrease alice1111111's total_votes
   prod = get_producer_info( "alice1111111" );
   wdump((prod));
   BOOST_TEST( stake2votes(core_sym::from_string("20.2220"), 1, 1) + stake2votes(core_sym::from_string("66.6666"), 1, 1) == prod["total_votes"].as_double() );
   BOOST_REQUIRE_EQUAL( get_global_state()["total_producer_vote_weight"].as<double>(), get_producer_info( "alice1111111" )["total_votes"].as_double() );

   //bob111111111 revokes his vote
   BOOST_REQUIRE_EQUAL( success(), vote( N(bob111111111), vector<account_name>() ) );

	total = get_total_stake("bob111111111");
   total = get_total_stake("alice1111111");
	
   //should decrease alice1111111's total_votes
   prod = get_producer_info( "alice1111111" );
   BOOST_TEST( stake2votes(core_sym::from_string("20.2220"), 1, 1) == prod["total_votes"].as_double() );
   BOOST_REQUIRE_EQUAL( get_global_state()["total_producer_vote_weight"].as<double>(), get_producer_info( "alice1111111" )["total_votes"].as_double() );

   //but eos should still be at stake
   BOOST_REQUIRE_EQUAL( core_sym::from_string("1955.5556"), get_balance( "bob111111111" ) );

   //carol1111111 unstakes rest of eos
   BOOST_REQUIRE_EQUAL( success(), unstake( "carol1111111", core_sym::from_string("20.0000"), core_sym::from_string("0.2220") ) );
   
	total = get_total_stake("carol1111111");
   
   //should decrease alice1111111's total_votes to zero
   prod = get_producer_info( "alice1111111" );
   BOOST_TEST( 0.0 == prod["total_votes"].as_double() );
   BOOST_TEST( get_global_state()["total_producer_vote_weight"].as<double>() == get_producer_info( "alice1111111" )["total_votes"].as_double() );

   //carol1111111 should receive funds in 3 days
   produce_block( fc::days(3) );
   produce_block();
   BOOST_REQUIRE_EQUAL( core_sym::from_string("3000.0000"), get_balance( "carol1111111" ) );

} FC_LOG_AND_RETHROW()


BOOST_FIXTURE_TEST_CASE( unregistered_producer_voting, eosio_system_tester, * boost::unit_test::tolerance(1e-4) ) try {
   issue( "bob111111111", core_sym::from_string("2000.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), stake( "bob111111111", core_sym::from_string("13.0000"), core_sym::from_string("0.5791") ) );
   REQUIRE_MATCHING_OBJECT( voter( "bob111111111", core_sym::from_string("13.5791") ), get_voter_info( "bob111111111" ) );

   //bob111111111 should not be able to vote for alice1111111 who is not a producer
   BOOST_REQUIRE_EQUAL( wasm_assert_msg( "producer is not registered" ),
                        vote( N(bob111111111), { N(alice1111111) } ) );

   //alice1111111 registers as a producer
   issue( "alice1111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   fc::variant params = producer_parameters_example(1);
   BOOST_REQUIRE_EQUAL( success(), push_action( N(alice1111111), N(regproducer), mvo()
                                               ("producer",  "alice1111111")
                                               ("producer_key", get_public_key( N(alice1111111), "active") )
                                               ("url", "")
                                               ("location", 0)
                        )
   );
   //and then unregisters
   BOOST_REQUIRE_EQUAL( success(), push_action( N(alice1111111), N(unregprod), mvo()
                                               ("producer",  "alice1111111")
                        )
   );
   //key should be empty
   auto prod = get_producer_info( "alice1111111" );
   BOOST_REQUIRE_EQUAL( fc::crypto::public_key(), fc::crypto::public_key(prod["producer_key"].as_string()) );

   //bob111111111 should not be able to vote for alice1111111 who is an unregistered producer
   BOOST_REQUIRE_EQUAL( wasm_assert_msg( "producer is not currently registered" ),
                        vote( N(bob111111111), { N(alice1111111) } ) );

} FC_LOG_AND_RETHROW()


BOOST_FIXTURE_TEST_CASE( more_than_30_producer_voting, eosio_system_tester ) try {
   issue( "bob111111111", core_sym::from_string("2000.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), stake( "bob111111111", core_sym::from_string("13.0000"), core_sym::from_string("0.5791") ) );
   REQUIRE_MATCHING_OBJECT( voter( "bob111111111", core_sym::from_string("13.5791") ), get_voter_info( "bob111111111" ) );

   //bob111111111 should not be able to vote for alice1111111 who is not a producer
   BOOST_REQUIRE_EQUAL( wasm_assert_msg( "attempt to vote for too many producers" ),
                        vote( N(bob111111111), vector<account_name>(31, N(alice1111111)) ) );

} FC_LOG_AND_RETHROW()


BOOST_FIXTURE_TEST_CASE( vote_same_producer_30_times, eosio_system_tester ) try {
   issue( "bob111111111", core_sym::from_string("2000.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), stake( "bob111111111", core_sym::from_string("50.0000"), core_sym::from_string("50.0000") ) );
   REQUIRE_MATCHING_OBJECT( voter( "bob111111111", core_sym::from_string("100.0000") ), get_voter_info( "bob111111111" ) );

   //alice1111111 becomes a producer
   issue( "alice1111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   fc::variant params = producer_parameters_example(1);
   BOOST_REQUIRE_EQUAL( success(), push_action( N(alice1111111), N(regproducer), mvo()
                                               ("producer",  "alice1111111")
                                               ("producer_key", get_public_key(N(alice1111111), "active") )
                                               ("url", "")
                                               ("location", 0)
                        )
   );

   //bob111111111 should not be able to vote for alice1111111 who is not a producer
   BOOST_REQUIRE_EQUAL( wasm_assert_msg( "producer votes must be unique and sorted" ),
                        vote( N(bob111111111), vector<account_name>(30, N(alice1111111)) ) );

   auto prod = get_producer_info( "alice1111111" );
   BOOST_TEST_REQUIRE( 0 == prod["total_votes"].as_double() );

} FC_LOG_AND_RETHROW()


BOOST_FIXTURE_TEST_CASE( producer_keep_votes, eosio_system_tester, * boost::unit_test::tolerance(1e-4) ) try {
   issue( "alice1111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   fc::variant params = producer_parameters_example(1);
   vector<char> key = fc::raw::pack( get_public_key( N(alice1111111), "active" ) );
   BOOST_REQUIRE_EQUAL( success(), push_action( N(alice1111111), N(regproducer), mvo()
                                               ("producer",  "alice1111111")
                                               ("producer_key", get_public_key( N(alice1111111), "active") )
                                               ("url", "")
                                               ("location", 0)
                        )
   );

   //bob111111111 makes stake
   issue( "bob111111111", core_sym::from_string("2000.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), stake( "bob111111111", core_sym::from_string("13.0000"), core_sym::from_string("0.5791") ) );
   REQUIRE_MATCHING_OBJECT( voter( "bob111111111", core_sym::from_string("13.5791") ), get_voter_info( "bob111111111" ) );

   //bob111111111 votes for alice1111111
   BOOST_REQUIRE_EQUAL( success(), vote(N(bob111111111), { N(alice1111111) } ) );

   auto prod = get_producer_info( "alice1111111" );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("13.5791"), 1, 1) == prod["total_votes"].as_double() );

   //unregister producer
   BOOST_REQUIRE_EQUAL( success(), push_action(N(alice1111111), N(unregprod), mvo()
                                               ("producer",  "alice1111111")
                        )
   );
   prod = get_producer_info( "alice1111111" );
   //key should be empty
   BOOST_REQUIRE_EQUAL( fc::crypto::public_key(), fc::crypto::public_key(prod["producer_key"].as_string()) );
   //check parameters just in case
   //REQUIRE_MATCHING_OBJECT( params, prod["prefs"]);
   //votes should stay the same
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("13.5791"), 1, 1), prod["total_votes"].as_double() );

   //regtister the same producer again
   params = producer_parameters_example(2);
   BOOST_REQUIRE_EQUAL( success(), push_action( N(alice1111111), N(regproducer), mvo()
                                               ("producer",  "alice1111111")
                                               ("producer_key", get_public_key( N(alice1111111), "active") )
                                               ("url", "")
                                               ("location", 0)
                        )
   );
   prod = get_producer_info( "alice1111111" );
   //votes should stay the same
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("13.5791"), 1, 1), prod["total_votes"].as_double() );

   //change parameters
   params = producer_parameters_example(3);
   BOOST_REQUIRE_EQUAL( success(), push_action( N(alice1111111), N(regproducer), mvo()
                                               ("producer",  "alice1111111")
                                               ("producer_key", get_public_key( N(alice1111111), "active") )
                                               ("url","")
                                               ("location", 0)
                        )
   );
   prod = get_producer_info( "alice1111111" );
   //votes should stay the same
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("13.5791"), 1, 1), prod["total_votes"].as_double() );
   //check parameters just in case
   //REQUIRE_MATCHING_OBJECT( params, prod["prefs"]);

} FC_LOG_AND_RETHROW()


BOOST_FIXTURE_TEST_CASE( vote_for_two_producers, eosio_system_tester, * boost::unit_test::tolerance(1e-4) ) try {
   //alice1111111 becomes a producer
   fc::variant params = producer_parameters_example(1);
   auto key = get_public_key( N(alice1111111), "active" );
   BOOST_REQUIRE_EQUAL( success(), push_action( N(alice1111111), N(regproducer), mvo()
                                               ("producer",  "alice1111111")
                                               ("producer_key", get_public_key( N(alice1111111), "active") )
                                               ("url","")
                                               ("location", 0)
                        )
   );
   //bob111111111 becomes a producer
   params = producer_parameters_example(2);
   key = get_public_key( N(bob111111111), "active" );
   BOOST_REQUIRE_EQUAL( success(), push_action( N(bob111111111), N(regproducer), mvo()
                                               ("producer",  "bob111111111")
                                               ("producer_key", get_public_key( N(alice1111111), "active") )
                                               ("url","")
                                               ("location", 0)
                        )
   );

   //carol1111111 votes for alice1111111 and bob111111111
   issue( "carol1111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), stake( "carol1111111", core_sym::from_string("15.0005"), core_sym::from_string("5.0000") ) );
   BOOST_REQUIRE_EQUAL( success(), vote( N(carol1111111), { N(alice1111111), N(bob111111111) } ) );

   auto alice_info = get_producer_info( "alice1111111" );
   BOOST_TEST( stake2votes(core_sym::from_string("20.0005"), 2, 2) == alice_info["total_votes"].as_double() );
   auto bob_info = get_producer_info( "bob111111111" );
   BOOST_TEST( stake2votes(core_sym::from_string("20.0005"), 2, 2) == bob_info["total_votes"].as_double() );

   //carol1111111 votes for alice1111111 (but revokes vote for bob111111111)
   BOOST_REQUIRE_EQUAL( success(), vote( N(carol1111111), { N(alice1111111) } ) );

   alice_info = get_producer_info( "alice1111111" );
   BOOST_TEST( stake2votes(core_sym::from_string("20.0005"), 1, 2) == alice_info["total_votes"].as_double() );
   bob_info = get_producer_info( "bob111111111" );
   BOOST_TEST( 0 == bob_info["total_votes"].as_double() );

   //alice1111111 votes for herself and bob111111111
   issue( "alice1111111", core_sym::from_string("2.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", core_sym::from_string("1.0000"), core_sym::from_string("1.0000") ) );
   BOOST_REQUIRE_EQUAL( success(), vote(N(alice1111111), { N(alice1111111), N(bob111111111) } ) );

   alice_info = get_producer_info( "alice1111111" );
   BOOST_TEST( stake2votes(core_sym::from_string("20.0005"), 1, 2) + stake2votes(core_sym::from_string("2.0000"), 2, 2) == alice_info["total_votes"].as_double() );

   bob_info = get_producer_info( "bob111111111" );
   BOOST_TEST( stake2votes(core_sym::from_string("2.0000"), 2, 2) == bob_info["total_votes"].as_double() );

} FC_LOG_AND_RETHROW()


BOOST_FIXTURE_TEST_CASE( proxy_register_unregister_keeps_stake, eosio_system_tester ) try {
   //register proxy by first action for this user ever
   BOOST_REQUIRE_EQUAL( success(), push_action(N(alice1111111), N(regproxy), mvo()
                                               ("proxy",  "alice1111111")
                                               ("isproxy", true )
                        )
   );
   REQUIRE_MATCHING_OBJECT( proxy( "alice1111111" ), get_voter_info( "alice1111111" ) );

   //unregister proxy
   BOOST_REQUIRE_EQUAL( success(), push_action(N(alice1111111), N(regproxy), mvo()
                                               ("proxy",  "alice1111111")
                                               ("isproxy", false)
                        )
   );
   REQUIRE_MATCHING_OBJECT( voter( "alice1111111" ), get_voter_info( "alice1111111" ) );

   //stake and then register as a proxy
   issue( "bob111111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), stake( "bob111111111", core_sym::from_string("200.0002"), core_sym::from_string("100.0001") ) );
   BOOST_REQUIRE_EQUAL( success(), push_action( N(bob111111111), N(regproxy), mvo()
                                               ("proxy",  "bob111111111")
                                               ("isproxy", true)
                        )
   );
   REQUIRE_MATCHING_OBJECT( proxy( "bob111111111" )( "staked", 3000003 ), get_voter_info( "bob111111111" ) );
   //unrgister and check that stake is still in place
   BOOST_REQUIRE_EQUAL( success(), push_action( N(bob111111111), N(regproxy), mvo()
                                               ("proxy",  "bob111111111")
                                               ("isproxy", false)
                        )
   );
   REQUIRE_MATCHING_OBJECT( voter( "bob111111111", core_sym::from_string("300.0003") ), get_voter_info( "bob111111111" ) );

   //register as a proxy and then stake
   BOOST_REQUIRE_EQUAL( success(), push_action( N(carol1111111), N(regproxy), mvo()
                                               ("proxy",  "carol1111111")
                                               ("isproxy", true)
                        )
   );
   issue( "carol1111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), stake( "carol1111111", core_sym::from_string("246.0002"), core_sym::from_string("531.0001") ) );
   //check that both proxy flag and stake a correct
   REQUIRE_MATCHING_OBJECT( proxy( "carol1111111" )( "staked", 7770003 ), get_voter_info( "carol1111111" ) );

   //unregister
   BOOST_REQUIRE_EQUAL( success(), push_action( N(carol1111111), N(regproxy), mvo()
                                                ("proxy",  "carol1111111")
                                                ("isproxy", false)
                        )
   );
   REQUIRE_MATCHING_OBJECT( voter( "carol1111111", core_sym::from_string("777.0003") ), get_voter_info( "carol1111111" ) );

} FC_LOG_AND_RETHROW()


BOOST_FIXTURE_TEST_CASE( proxy_stake_unstake_keeps_proxy_flag, eosio_system_tester ) try {
   activate_network();

   BOOST_REQUIRE_EQUAL( success(), push_action( N(alice1111111), N(regproxy), mvo()
                                               ("proxy",  "alice1111111")
                                               ("isproxy", true)
                        )
   );
   issue( "alice1111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   REQUIRE_MATCHING_OBJECT( proxy( "alice1111111" ), get_voter_info( "alice1111111" ) );

   //stake
   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", core_sym::from_string("100.0000"), core_sym::from_string("50.0000") ) );
   //check that account is still a proxy
   REQUIRE_MATCHING_OBJECT( proxy( "alice1111111" )( "staked", 1500000 ), get_voter_info( "alice1111111" ) );

   //stake more
   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", core_sym::from_string("30.0000"), core_sym::from_string("20.0000") ) );
   //check that account is still a proxy
   REQUIRE_MATCHING_OBJECT( proxy( "alice1111111" )("staked", 2000000 ), get_voter_info( "alice1111111" ) );

   //unstake more
   BOOST_REQUIRE_EQUAL( success(), unstake( "alice1111111", core_sym::from_string("65.0000"), core_sym::from_string("35.0000") ) );
   REQUIRE_MATCHING_OBJECT( proxy( "alice1111111" )("staked", 1000000 ), get_voter_info( "alice1111111" ) );

   //unstake the rest
   BOOST_REQUIRE_EQUAL( success(), unstake( "alice1111111", core_sym::from_string("65.0000"), core_sym::from_string("35.0000") ) );
   REQUIRE_MATCHING_OBJECT( proxy( "alice1111111" )( "staked", 0 ), get_voter_info( "alice1111111" ) );

} FC_LOG_AND_RETHROW()


BOOST_FIXTURE_TEST_CASE( proxy_actions_affect_producers, eosio_system_tester, * boost::unit_test::tolerance(10) ) try {
   activate_network();

   create_accounts_with_resources( {  N(defproducer1), N(defproducer2), N(defproducer3) } );
   BOOST_REQUIRE_EQUAL( success(), regproducer( "defproducer1", 1) );
   BOOST_REQUIRE_EQUAL( success(), regproducer( "defproducer2", 2) );
   BOOST_REQUIRE_EQUAL( success(), regproducer( "defproducer3", 3) );

   //register as a proxy
   BOOST_REQUIRE_EQUAL( success(), push_action( N(alice1111111), N(regproxy), mvo()
                                                ("proxy",  "alice1111111")
                                                ("isproxy", true)
                        )
   );

   //accumulate proxied votes
   issue( "bob111111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), stake( "bob111111111", core_sym::from_string("100.0002"), core_sym::from_string("50.0001") ) );
   BOOST_REQUIRE_EQUAL( success(), vote(N(bob111111111), vector<account_name>(), N(alice1111111) ) );
   REQUIRE_MATCHING_OBJECT( proxy( "alice1111111" )( "proxied_vote_weight", 1500003 ), get_voter_info( "alice1111111" ) );

   //vote for producers
   BOOST_REQUIRE_EQUAL( success(), vote(N(alice1111111), { N(defproducer1), N(defproducer2) } ) );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("150.0003"), 2, 3) == get_producer_info( "defproducer1" )["total_votes"].as_double() );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("150.0003"), 2, 3) == get_producer_info( "defproducer2" )["total_votes"].as_double() );
   BOOST_TEST_REQUIRE( 0 == get_producer_info( "defproducer3" )["total_votes"].as_double() );

   //vote for another producers
   BOOST_REQUIRE_EQUAL( success(), vote( N(alice1111111), { N(defproducer1), N(defproducer3) } ) );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("150.0003"), 2, 3) == get_producer_info( "defproducer1" )["total_votes"].as_double() );
   BOOST_REQUIRE_EQUAL( 0, get_producer_info( "defproducer2" )["total_votes"].as_double() );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("150.0003"), 2, 3) == get_producer_info( "defproducer3" )["total_votes"].as_double() );

   //unregister proxy
   BOOST_REQUIRE_EQUAL( success(), push_action( N(alice1111111), N(regproxy), mvo()
                                                ("proxy",  "alice1111111")
                                                ("isproxy", false)
                        )
   );
   //REQUIRE_MATCHING_OBJECT( voter( "alice1111111" )( "proxied_vote_weight", stake2votes(core_sym::from_string("150.0003")) ), get_voter_info( "alice1111111" ) );
   BOOST_REQUIRE_EQUAL( 0, get_producer_info( "defproducer1" )["total_votes"].as_double() );
   BOOST_REQUIRE_EQUAL( 0, get_producer_info( "defproducer2" )["total_votes"].as_double() );
   BOOST_REQUIRE_EQUAL( 0, get_producer_info( "defproducer3" )["total_votes"].as_double() );

   //register proxy again
   BOOST_REQUIRE_EQUAL( success(), push_action( N(alice1111111), N(regproxy), mvo()
                                                ("proxy",  "alice1111111")
                                                ("isproxy", true)
                        )
   );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("150.0003"), 2, 3) == get_producer_info( "defproducer1" )["total_votes"].as_double() );
   BOOST_REQUIRE_EQUAL( 0, get_producer_info( "defproducer2" )["total_votes"].as_double() );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("150.0003"), 2, 3) == get_producer_info( "defproducer3" )["total_votes"].as_double() );

   //stake increase by proxy itself affects producers
   issue( "alice1111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", core_sym::from_string("30.0001"), core_sym::from_string("20.0001") ) );
   BOOST_REQUIRE_EQUAL( stake2votes(core_sym::from_string("200.0005"), 2, 3), get_producer_info( "defproducer1" )["total_votes"].as_double() );
   BOOST_REQUIRE_EQUAL( 0, get_producer_info( "defproducer2" )["total_votes"].as_double() );
   BOOST_REQUIRE_EQUAL( stake2votes(core_sym::from_string("200.0005"), 2, 3), get_producer_info( "defproducer3" )["total_votes"].as_double() );

   //stake decrease by proxy itself affects producers
   BOOST_REQUIRE_EQUAL( success(), unstake( "alice1111111", core_sym::from_string("10.0001"), core_sym::from_string("10.0001") ) );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("180.0003"), 2, 3) == get_producer_info( "defproducer1" )["total_votes"].as_double() );
   BOOST_REQUIRE_EQUAL( 0, get_producer_info( "defproducer2" )["total_votes"].as_double() );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("180.0003"), 2, 3) == get_producer_info( "defproducer3" )["total_votes"].as_double() );

} FC_LOG_AND_RETHROW()

// TODO : REWRITE producer_pay !!!!

// BOOST_FIXTURE_TEST_CASE(producer_pay, eosio_system_tester, * boost::unit_test::tolerance(1e-10)) try {
//    const double continuous_rate = 0.025; 
//    const double usecs_per_year  = 52 * 7 * 24 * 3600 * 1000000ll;
//    const double secs_per_year   = 52 * 7 * 24 * 3600;

//    const asset large_asset = core_sym::from_string("80.0000");
//    create_account_with_resources( N(defproducera), config::system_account_name, core_sym::from_string("1.0000"), false, large_asset, large_asset );
//    create_account_with_resources( N(defproducerb), config::system_account_name, core_sym::from_string("1.0000"), false, large_asset, large_asset );
//    create_account_with_resources( N(defproducerc), config::system_account_name, core_sym::from_string("1.0000"), false, large_asset, large_asset );

//    create_account_with_resources( N(producvotera), config::system_account_name, core_sym::from_string("1.0000"), false, large_asset, large_asset );
//    create_account_with_resources( N(producvoterb), config::system_account_name, core_sym::from_string("1.0000"), false, large_asset, large_asset );

//    BOOST_REQUIRE_EQUAL(success(), regproducer(N(defproducera)));
//    auto prod = get_producer_info( N(defproducera) );
//    BOOST_REQUIRE_EQUAL("defproducera", prod["owner"].as_string());
//    BOOST_REQUIRE_EQUAL(0, prod["total_votes"].as_double());

//    transfer( config::system_account_name, "producvotera", core_sym::from_string("400000000.0000"), config::system_account_name);
//    BOOST_REQUIRE_EQUAL(success(), stake("producvotera", core_sym::from_string("100000000.0000"), core_sym::from_string("100000000.0000")));
//    BOOST_REQUIRE_EQUAL(success(), vote( N(producvotera), { N(defproducera) }));

//    activate_network();

//    // defproducera is the only active producer
//    // produce enough blocks so new schedule kicks in and defproducera produces some blocks
//    {
//       const int32_t minBlocksForFullPayout = 342; // minimum necessary for full producer payout
//       const int32_t blocksProduced = minBlocksForFullPayout * 1.1; // minimum necessary for full producer payout + 10% insurance for missed blocks ?? 

//       produce_blocks(blocksProduced); 

//       const auto     initial_global_state      = get_global_state();
//       const uint64_t initial_claim_time        = microseconds_since_epoch_of_iso_string( initial_global_state["last_pervote_bucket_fill"] );
//       const int64_t  initial_pervote_bucket    = initial_global_state["pervote_bucket"].as<int64_t>();
//       const int64_t  initial_perblock_bucket   = initial_global_state["perblock_bucket"].as<int64_t>();
//       const int64_t  initial_savings           = get_balance(N(eosio.saving)).get_amount();
//       const uint32_t initial_tot_unpaid_blocks = initial_global_state["total_unpaid_blocks"].as<uint32_t>();

//       prod = get_producer_info("defproducera");
//       const uint32_t unpaid_blocks = prod["unpaid_blocks"].as<uint32_t>();
//       const bool is_active = prod["is_active"].as<bool>();
//       std::cout << "Producer defproducera unpaid_blocks: " << unpaid_blocks << " Is it greater than 1: " << (1 < unpaid_blocks) << std::endl;
//       std::cout << "Producer defproducera is_active: " << is_active << std::endl;
//       BOOST_REQUIRE(1 < unpaid_blocks);
//       BOOST_REQUIRE_EQUAL(0, microseconds_since_epoch_of_iso_string(prod["last_claim_time"]));

//       BOOST_REQUIRE_EQUAL(initial_tot_unpaid_blocks, unpaid_blocks);

//       const asset initial_supply  = get_token_supply();
//       const asset initial_balance = get_balance(N(defproducera));

//       BOOST_REQUIRE_EQUAL(success(), push_action(N(defproducera), N(claimrewards), mvo()("owner", "defproducera")));

//       const auto     global_state      = get_global_state();
//       const uint64_t claim_time        = microseconds_since_epoch_of_iso_string( global_state["last_pervote_bucket_fill"] );
//       const int64_t  pervote_bucket    = global_state["pervote_bucket"].as<int64_t>();
//       const int64_t  perblock_bucket   = global_state["perblock_bucket"].as<int64_t>();
//       const int64_t  savings           = get_balance(N(eosio.saving)).get_amount();
//       const uint32_t tot_unpaid_blocks = global_state["total_unpaid_blocks"].as<uint32_t>();

//       prod = get_producer_info("defproducera");
//       BOOST_REQUIRE_EQUAL(1, prod["unpaid_blocks"].as<uint32_t>());
//       BOOST_REQUIRE_EQUAL(1, tot_unpaid_blocks);
//       const asset supply  = get_token_supply();
//       const asset balance = get_balance(N(defproducera));

//       BOOST_REQUIRE_EQUAL(claim_time, microseconds_since_epoch_of_iso_string( prod["last_claim_time"] ));

//       auto usecs_between_fills = claim_time - initial_claim_time;
//       int32_t secs_between_fills = usecs_between_fills/1000000;

//       BOOST_REQUIRE_EQUAL(0, initial_savings);
//       BOOST_REQUIRE_EQUAL(0, initial_perblock_bucket);
//       BOOST_REQUIRE_EQUAL(0, initial_pervote_bucket);
      
//       auto new_tokens = static_cast<int64_t>((continuous_rate * double(initial_supply.get_amount()) * double(usecs_between_fills)) / double(usecs_per_year));
//       auto to_producers = (new_tokens / 5) * 2;
//       auto to_workers = new_tokens - to_producers;

//       BOOST_REQUIRE_EQUAL(new_tokens, supply.get_amount() - initial_supply.get_amount());
//       BOOST_REQUIRE_EQUAL(to_workers, savings - initial_savings);
//       BOOST_REQUIRE_EQUAL(to_producers, (balance.get_amount() - initial_balance.get_amount()));
//    }

//    {
//       BOOST_REQUIRE_EQUAL(wasm_assert_msg("already claimed rewards within past day"),
//                           push_action(N(defproducera), N(claimrewards), mvo()("owner", "defproducera")));
//    }

//    // defproducera waits for 23 hours and 55 minutes, can't claim rewards yet
//    {
//       produce_block(fc::seconds(23 * 3600 + 55 * 60));
//       BOOST_REQUIRE_EQUAL(wasm_assert_msg("already claimed rewards within past day"),
//                           push_action(N(defproducera), N(claimrewards), mvo()("owner", "defproducera")));
//    }

//    // wait 5 more minutes, defproducera can now claim rewards again
//    {
//       produce_block(fc::seconds(5 * 60));

//       const auto     initial_global_state      = get_global_state();
//       const uint64_t initial_claim_time        = microseconds_since_epoch_of_iso_string( initial_global_state["last_pervote_bucket_fill"] );
//       const int64_t  initial_pervote_bucket    = initial_global_state["pervote_bucket"].as<int64_t>();
//       const int64_t  initial_perblock_bucket   = initial_global_state["perblock_bucket"].as<int64_t>();
//       const int64_t  initial_savings           = get_balance(N(eosio.saving)).get_amount();
//       const uint32_t initial_tot_unpaid_blocks = initial_global_state["total_unpaid_blocks"].as<uint32_t>();
//       const double   initial_tot_vote_weight   = initial_global_state["total_producer_vote_weight"].as<double>();

//       prod = get_producer_info("defproducera");
//       const uint32_t unpaid_blocks = prod["unpaid_blocks"].as<uint32_t>();
//       BOOST_REQUIRE(1 < unpaid_blocks);
//       BOOST_REQUIRE_EQUAL(initial_tot_unpaid_blocks, unpaid_blocks);
//       BOOST_REQUIRE(0 < prod["total_votes"].as<double>());
//       BOOST_TEST(initial_tot_vote_weight, prod["total_votes"].as<double>());
//       BOOST_REQUIRE(0 < microseconds_since_epoch_of_iso_string( initial_global_state["last_pervote_bucket_fill"] ));

//       BOOST_REQUIRE_EQUAL(initial_tot_unpaid_blocks, unpaid_blocks);

//       const asset initial_supply  = get_token_supply();
//       const asset initial_balance = get_balance(N(defproducera));

//       BOOST_REQUIRE_EQUAL(success(), push_action(N(defproducera), N(claimrewards), mvo()("owner", "defproducera")));

//       const auto global_state          = get_global_state();
//       const uint64_t claim_time        = microseconds_since_epoch_of_iso_string( global_state["last_pervote_bucket_fill"] );
//       const int64_t  pervote_bucket    = global_state["pervote_bucket"].as<int64_t>();
//       const int64_t  perblock_bucket   = global_state["perblock_bucket"].as<int64_t>();
//       const int64_t  savings           = get_balance(N(eosio.saving)).get_amount();
//       const uint32_t tot_unpaid_blocks = global_state["total_unpaid_blocks"].as<uint32_t>();

//       prod = get_producer_info("defproducera");
//       BOOST_REQUIRE_EQUAL(1, prod["unpaid_blocks"].as<uint32_t>());
//       BOOST_REQUIRE_EQUAL(1, tot_unpaid_blocks);
//       const asset supply  = get_token_supply();
//       const asset balance = get_balance(N(defproducera));

//       BOOST_REQUIRE_EQUAL(claim_time, microseconds_since_epoch_of_iso_string( prod["last_claim_time"] ));
//       auto usecs_between_fills = claim_time - initial_claim_time;

//       auto new_tokens = static_cast<int64_t>((continuous_rate * double(initial_supply.get_amount()) * double(usecs_between_fills)) / double(usecs_per_year));
//       auto to_producers = (new_tokens / 5) * 2;
//       auto to_workers = new_tokens - to_producers;

//       BOOST_REQUIRE_EQUAL(new_tokens, supply.get_amount() - initial_supply.get_amount());
//       BOOST_REQUIRE_EQUAL(to_workers, savings - initial_savings);
//       // 24h production skip DOES NOT produce blocks, it just skips time. The #no of produced blocks is ~3 
//       BOOST_REQUIRE_EQUAL(to_producers/2, balance.get_amount() - initial_balance.get_amount());
//    }

//    // defproducerb tries to claim rewards but he's not on the list
//    {
//       BOOST_REQUIRE_EQUAL(wasm_assert_msg("unable to find key"),
//                           push_action(N(defproducerb), N(claimrewards), mvo()("owner", "defproducerb")));
//    }

//    // test stability over a year
//    {
//       regproducer(N(defproducerb));
//       regproducer(N(defproducerc));
//       produce_block(fc::hours(24));
//       const asset first_initial_supply = get_token_supply();
//       asset initial_supply  = first_initial_supply;
//       const int64_t initial_savings = get_balance(N(eosio.saving)).get_amount();
//       const asset initial_balance = get_balance(N(defproducera));
//       const auto initial_global_state = get_global_state();
//       auto global_state = get_global_state();
//       uint64_t initial_claim_time   = microseconds_since_epoch_of_iso_string(initial_global_state["last_pervote_bucket_fill"]);
//       uint64_t claim_time           = microseconds_since_epoch_of_iso_string(global_state["last_pervote_bucket_fill"]);
//       auto usecs_between_fills = claim_time - initial_claim_time;
//       uint64_t new_tokens = 0;

//       for (uint32_t i = 0; i < 7 * 52; ++i) {
//          produce_block(fc::seconds(23 * 3600));
//          BOOST_REQUIRE_EQUAL(success(), push_action(N(defproducerc), N(claimrewards), mvo()("owner", "defproducerc")));

//          global_state = get_global_state();
//          claim_time = microseconds_since_epoch_of_iso_string(global_state["last_pervote_bucket_fill"]);
//          usecs_between_fills = claim_time - initial_claim_time;
//          new_tokens += static_cast<int64_t>((continuous_rate * double(initial_supply.get_amount()) * double(usecs_between_fills)) / double(usecs_per_year));
//          initial_supply  = get_token_supply();
//          initial_claim_time = claim_time;

//          // produce_block(fc::seconds(8 * 3600));
//          produce_block(fc::seconds(1800));
//          BOOST_REQUIRE_EQUAL(success(), push_action(N(defproducerb), N(claimrewards), mvo()("owner", "defproducerb")));

//          global_state = get_global_state();
//          claim_time = microseconds_since_epoch_of_iso_string(global_state["last_pervote_bucket_fill"]);
//          usecs_between_fills = claim_time - initial_claim_time;
//          new_tokens += static_cast<int64_t>((continuous_rate * double(initial_supply.get_amount()) * double(usecs_between_fills)) / double(usecs_per_year));
//          initial_supply  = get_token_supply();
//          initial_claim_time = claim_time;

//          // produce_block(fc::seconds(8 * 3600));
//          produce_block(fc::seconds(1800));
//          BOOST_REQUIRE_EQUAL(success(), push_action(N(defproducera), N(claimrewards), mvo()("owner", "defproducera")));

//          global_state = get_global_state();
//          claim_time = microseconds_since_epoch_of_iso_string(global_state["last_pervote_bucket_fill"]);
//          usecs_between_fills = claim_time - initial_claim_time;
//          new_tokens += static_cast<int64_t>((continuous_rate * double(initial_supply.get_amount()) * double(usecs_between_fills)) / double(usecs_per_year));
//          initial_supply  = get_token_supply();
//          initial_claim_time = claim_time;

//       }

//       const asset balance = get_balance(N(defproducera));
//       const asset balancea = get_balance(N(defproducera));
//       const asset balanceb = get_balance(N(defproducerb));
//       const asset balancec = get_balance(N(defproducerc));
//       const asset supply  = get_token_supply();
//       const int64_t savings = get_balance(N(eosio.saving)).get_amount();

//       auto to_producers = (new_tokens / 5) * 2;
//       auto to_workers = new_tokens - to_producers;

//       initial_supply = first_initial_supply;
//       // std::cout << "new tokens: " << initial_supply.get_amount() <<  " * " <<  double(usecs_between_fills) <<  " * " <<  continuous_rate <<  " / " <<  usecs_per_year <<  " = " << new_tokens <<  '\n';
//       // std::cout << "supply - initial_supply = [new tokens] : " << supply.get_amount() <<  " - " <<  initial_supply.get_amount() <<  " = " <<  (supply.get_amount() - initial_supply.get_amount()) <<  '\n';
//       // std::cout << "savings - initial savings = to workers : " << savings <<  " - " <<  initial_savings <<  " = " <<  (savings - initial_savings) <<  "[ " << to_workers << " ]" <<  '\n';
//       // std::cout << "balance - initial balance = to producers : " << balance.get_amount() <<  " - " <<  initial_balance.get_amount() <<  " = " <<  (balance.get_amount() - initial_balance.get_amount()) <<  "[ " << to_producers << " ]" <<  '\n';

//       // std::cout << "perblock bucket: " << global_state["perblock_bucket"].as<int64_t>() << std::endl;

//       BOOST_REQUIRE(0 <= (supply.get_amount() - initial_supply.get_amount()) - int64_t(double(initial_supply.get_amount()) * double(0.025)));
      
//       // TODO :: should this be how it works ? 
//       // BOOST_REQUIRE(balancea.get_amount() == balanceb.get_amount());
//       // BOOST_REQUIRE(balancec.get_amount() == balanceb.get_amount());

//       // TODO :: what tollerance should the compounding have ? ... we have anything like this ?
//       // BOOST_REQUIRE(250 * 10000 > (supply.get_amount() - initial_supply.get_amount()) - int64_t(double(initial_supply.get_amount()) * double(0.025)));


//       // Amount issued per year is very close to the 5% inflation target. Small difference (500 tokens out of 50'000'000 issued)
//       // is due to compounding every 8 hours in this test as opposed to theoretical continuous compounding
//       // BOOST_REQUIRE(500 * 10000 > int64_t(double(initial_supply.get_amount()) * double(0.05)) - (supply.get_amount() - initial_supply.get_amount()));
//       // BOOST_REQUIRE(500 * 10000 > int64_t(double(initial_supply.get_amount()) * double(0.04)) - (savings - initial_savings));
//    }
// } FC_LOG_AND_RETHROW()

// TODO : rewrite multiple_producer_pay !!!

// BOOST_FIXTURE_TEST_CASE(multiple_producer_pay, eosio_system_tester, * boost::unit_test::tolerance(1e-10)) try {

//    auto within_one = [](int64_t a, int64_t b) -> bool { return std::abs( a - b ) <= 1; };

//    const int64_t secs_per_year  = 52 * 7 * 24 * 3600;
//    const double  usecs_per_year = secs_per_year * 1000000;
//    const double  cont_rate      = 0.025;

//    const asset net = core_sym::from_string("80.0000");
//    const asset cpu = core_sym::from_string("80.0000");
//    const std::vector<account_name> voters = { N(producvotera), N(producvoterb), N(producvoterc), N(producvoterd) };
//    for (const auto& v: voters) {
//       create_account_with_resources( v, config::system_account_name, core_sym::from_string("1.0000"), false, net, cpu );
//       transfer( config::system_account_name, v, core_sym::from_string("100000000.0000"), config::system_account_name );
//       BOOST_REQUIRE_EQUAL(success(), stake(v, core_sym::from_string("30000000.0000"), core_sym::from_string("30000000.0000")) );
//    }

//    // create accounts {defproducera, defproducerb, ..., defproducerz, abcproducera, ..., defproducern} and register as producers
//    std::vector<account_name> producer_names;
//    {
//       producer_names.reserve('z' - 'a' + 1);
//       {
//          const std::string root("defproducer");
//          for ( char c = 'a'; c <= 'z'; ++c ) {
//             producer_names.emplace_back(root + std::string(1, c));
//          }
//       }
//       {
//          const std::string root("abcproducer");
//          for ( char c = 'a'; c <= 'n'; ++c ) {
//             producer_names.emplace_back(root + std::string(1, c));
//          }
//       }
//       setup_producer_accounts(producer_names);
//       for (const auto& p: producer_names) {
//          BOOST_REQUIRE_EQUAL( success(), regproducer(p) );
//          produce_blocks(1);
//          ilog( "------ get pro----------" );
//          wdump((p));
//          BOOST_TEST(0 == get_producer_info(p)["total_votes"].as<double>());
//       }
//    }

//    produce_block( fc::hours(24) );
   
//    // producvotera votes for defproducera ... defproducerj
//    // producvoterb votes for defproducera ... defproduceru
//    // producvoterc votes for defproducera ... defproducerz
//    // producvoterd votes for abcproducera ... abcproducern
//    {
//       BOOST_REQUIRE_EQUAL(success(), vote(N(producvotera), vector<account_name>(producer_names.begin(), producer_names.begin()+10)));
//       BOOST_REQUIRE_EQUAL(success(), vote(N(producvoterb), vector<account_name>(producer_names.begin(), producer_names.begin()+21)));
//       BOOST_REQUIRE_EQUAL(success(), vote(N(producvoterc), vector<account_name>(producer_names.begin(), producer_names.begin()+26)));
//       BOOST_REQUIRE_EQUAL(success(), vote(N(producvoterd), vector<account_name>(producer_names.begin()+26, producer_names.end())));
//    }

//    {
//       auto proda = get_producer_info( N(defproducera) );
//       auto prodj = get_producer_info( N(defproducerj) );
//       auto prodk = get_producer_info( N(defproducerk) );
//       auto produ = get_producer_info( N(defproduceru) );
//       auto prodv = get_producer_info( N(defproducerv) );
//       auto prodz = get_producer_info( N(defproducerz) );

//       BOOST_REQUIRE (0 == proda["unpaid_blocks"].as<uint32_t>() && 0 == prodz["unpaid_blocks"].as<uint32_t>());
//       BOOST_REQUIRE (0 == microseconds_since_epoch_of_iso_string(proda["last_claim_time"]) && 0 == microseconds_since_epoch_of_iso_string(prodz["last_claim_time"]));

//       // check vote ratios
//       BOOST_REQUIRE ( 0 < proda["total_votes"].as<double>() && 0 < prodz["total_votes"].as<double>() );
//       BOOST_TEST( proda["total_votes"].as<double>() == prodj["total_votes"].as<double>() );
//       BOOST_TEST( prodk["total_votes"].as<double>() == produ["total_votes"].as<double>() );
//       BOOST_TEST( prodv["total_votes"].as<double>() == prodz["total_votes"].as<double>() );
//       // these ratios don't apply anymore, can't really calculate ratios with new formula
//       // BOOST_TEST( 2 * proda["total_votes"].as<double>() == 3 * produ["total_votes"].as<double>() );
//       // BOOST_TEST( proda["total_votes"].as<double>() ==  3 * prodz["total_votes"].as<double>() );
//    }

//    // give a chance for everyone to produce blocks
//    {
//       // why is there a need for such a high number of blocks for everyone to produce ???
//       // produce_blocks(51 * 24 + 20);
//       produce_blocks(23 * 12 + 20); 

//       // for (uint32_t i = 0; i < producer_names.size(); ++i) {
//       //    std::cout<<"["<<producer_names[i]<<"]: "<<get_producer_info(producer_names[i])["unpaid_blocks"].as<uint32_t>()<<std::endl;
//       // }

//       bool all_21_produced = true;
//       for (uint32_t i = 0; i < 21; ++i) {
//             // std::cout<<"P : "<<get_producer_info(producer_names[i])["unpaid_blocks"].as<uint32_t>()<<std::endl;
//          if (0 == get_producer_info(producer_names[i])["unpaid_blocks"].as<uint32_t>()) {
//             all_21_produced = false;
//          }
//       }
//       bool rest_didnt_produce = true;
//       for (uint32_t i = 21; i < producer_names.size(); ++i) {
//             // std::cout<<"N : "<<get_producer_info(producer_names[i])["unpaid_blocks"].as<uint32_t>()<<std::endl;
//          if (0 < get_producer_info(producer_names[i])["unpaid_blocks"].as<uint32_t>()) {
//             rest_didnt_produce = false;
//          }
//       }
//       BOOST_REQUIRE(all_21_produced && rest_didnt_produce);
//    }

//    std::vector<double> vote_shares(producer_names.size());
//    {
//       double total_votes = 0;
//       for (uint32_t i = 0; i < producer_names.size(); ++i) {
//          vote_shares[i] = get_producer_info(producer_names[i])["total_votes"].as<double>();
//          total_votes += vote_shares[i];
//       }
//       BOOST_TEST(total_votes == get_global_state()["total_producer_vote_weight"].as<double>());
//       std::for_each(vote_shares.begin(), vote_shares.end(), [total_votes](double& x) { x /= total_votes; });

//       BOOST_TEST(double(1) == std::accumulate(vote_shares.begin(), vote_shares.end(), double(0)));
//       // these ratios don't apply anymore, can't really calculate ratios with new formula
//       // BOOST_TEST(double(3./71.) == vote_shares.front());
//       // BOOST_TEST(double(1./71.) == vote_shares.back());
//    }

//    {
//       const uint32_t prod_index = 2;
//       const auto prod_name = producer_names[prod_index];

//       const auto     initial_global_state      = get_global_state();
//       const uint64_t initial_claim_time        = microseconds_since_epoch_of_iso_string( initial_global_state["last_pervote_bucket_fill"] );
//       const int64_t  initial_pervote_bucket    = initial_global_state["pervote_bucket"].as<int64_t>();
//       const int64_t  initial_perblock_bucket   = initial_global_state["perblock_bucket"].as<int64_t>();
//       const int64_t  initial_savings           = get_balance(N(eosio.saving)).get_amount();
//       const uint32_t initial_tot_unpaid_blocks = initial_global_state["total_unpaid_blocks"].as<uint32_t>();
//       const asset    initial_supply            = get_token_supply();
//       const asset    initial_bpay_balance      = get_balance(N(eosio.bpay));
//       const asset    initial_vpay_balance      = get_balance(N(eosio.vpay));
//       const asset    initial_balance           = get_balance(prod_name);
//       const uint32_t initial_unpaid_blocks     = get_producer_info(prod_name)["unpaid_blocks"].as<uint32_t>();

//       BOOST_REQUIRE_EQUAL(success(), push_action(prod_name, N(claimrewards), mvo()("owner", prod_name)));

//       const auto     global_state      = get_global_state();
//       const uint64_t claim_time        = microseconds_since_epoch_of_iso_string( global_state["last_pervote_bucket_fill"] );
//       const int64_t  pervote_bucket    = global_state["pervote_bucket"].as<int64_t>();
//       const int64_t  perblock_bucket   = global_state["perblock_bucket"].as<int64_t>();
//       const int64_t  savings           = get_balance(N(eosio.saving)).get_amount();
//       const uint32_t tot_unpaid_blocks = global_state["total_unpaid_blocks"].as<uint32_t>();
//       const asset    supply            = get_token_supply();
//       const asset    bpay_balance      = get_balance(N(eosio.bpay));
//       const asset    vpay_balance      = get_balance(N(eosio.vpay));
//       const asset    balance           = get_balance(prod_name);
//       const uint32_t unpaid_blocks     = get_producer_info(prod_name)["unpaid_blocks"].as<uint32_t>();

//       const uint64_t usecs_between_fills = claim_time - initial_claim_time;
//       const int32_t secs_between_fills = static_cast<int32_t>(usecs_between_fills / 1000000);

//       auto expected_supply_growth = static_cast<int64_t>((cont_rate * double(initial_supply.get_amount()) * double(usecs_between_fills)) / double(usecs_per_year));
//       auto to_producers = (expected_supply_growth / 5) * 2;
//       auto to_workers = expected_supply_growth - to_producers;

//       BOOST_REQUIRE_EQUAL( int64_t(expected_supply_growth), supply.get_amount() - initial_supply.get_amount() );
//       BOOST_REQUIRE_EQUAL( to_workers, savings - initial_savings );

//       produce_blocks(5);

//       BOOST_REQUIRE_EQUAL(wasm_assert_msg("already claimed rewards within past day"),
//                           push_action(prod_name, N(claimrewards), mvo()("owner", prod_name)));
//    }

//    {
//       const uint32_t prod_index = 23;
//       const auto prod_name = producer_names[prod_index];
//       BOOST_REQUIRE_EQUAL(success(),
//                           push_action(prod_name, N(claimrewards), mvo()("owner", prod_name)));
      
//       // sbp's should get half of the full producer amount - currently will fail
//       // const uint32_t prod_index_full = 20;
//       // const auto prod_name_full = producer_names[prod_index];
//       // BOOST_REQUIRE_EQUAL(get_balance(prod_name_full).get_amount()/2, get_balance(prod_name).get_amount());

//       // old check
//       // BOOST_REQUIRE_EQUAL(0, get_balance(prod_name).get_amount());
//       BOOST_REQUIRE_EQUAL(wasm_assert_msg("already claimed rewards within past day"),
//                           push_action(prod_name, N(claimrewards), mvo()("owner", prod_name)));
//    }


// // these checks are done above, plus the extra shares with pervote_bucket doesn't apply anymore

//    // Wait for 23 hours. By now, pervote_bucket has grown enough
//    // that a producer's share is more than 100 tokens.
// //    produce_block(fc::seconds(23 * 3600));

// //    {
// //       const uint32_t prod_index = 15;
// //       const auto prod_name = producer_names[prod_index];

// //       const auto     initial_global_state      = get_global_state();
// //       const uint64_t initial_claim_time        = initial_global_state["last_pervote_bucket_fill"].as_uint64();
// //       const int64_t  initial_pervote_bucket    = initial_global_state["pervote_bucket"].as<int64_t>();
// //       const int64_t  initial_perblock_bucket   = initial_global_state["perblock_bucket"].as<int64_t>();
// //       const int64_t  initial_savings           = get_balance(N(eosio.saving)).get_amount();
// //       const uint32_t initial_tot_unpaid_blocks = initial_global_state["total_unpaid_blocks"].as<uint32_t>();
// //       const asset    initial_supply            = get_token_supply();
// //       const asset    initial_bpay_balance      = get_balance(N(eosio.bpay));
// //       const asset    initial_vpay_balance      = get_balance(N(eosio.vpay));
// //       const asset    initial_balance           = get_balance(prod_name);
// //       const uint32_t initial_unpaid_blocks     = get_producer_info(prod_name)["unpaid_blocks"].as<uint32_t>();

// //       BOOST_REQUIRE_EQUAL(success(), push_action(prod_name, N(claimrewards), mvo()("owner", prod_name)));

// //       const auto     global_state      = get_global_state();
// //       const uint64_t claim_time        = global_state["last_pervote_bucket_fill"].as_uint64();
// //       const int64_t  pervote_bucket    = global_state["pervote_bucket"].as<int64_t>();
// //       const int64_t  perblock_bucket   = global_state["perblock_bucket"].as<int64_t>();
// //       const int64_t  savings           = get_balance(N(eosio.saving)).get_amount();
// //       const uint32_t tot_unpaid_blocks = global_state["total_unpaid_blocks"].as<uint32_t>();
// //       const asset    supply            = get_token_supply();
// //       const asset    bpay_balance      = get_balance(N(eosio.bpay));
// //       const asset    vpay_balance      = get_balance(N(eosio.vpay));
// //       const asset    balance           = get_balance(prod_name);
// //       const uint32_t unpaid_blocks     = get_producer_info(prod_name)["unpaid_blocks"].as<uint32_t>();

// //       const uint64_t usecs_between_fills = claim_time - initial_claim_time;

// //       const double expected_supply_growth = initial_supply.get_amount() * double(usecs_between_fills) * cont_rate / usecs_per_year;
// //       BOOST_REQUIRE_EQUAL( int64_t(expected_supply_growth), supply.get_amount() - initial_supply.get_amount() );
// //       BOOST_REQUIRE_EQUAL( int64_t(expected_supply_growth) - int64_t(expected_supply_growth)/5, savings - initial_savings );

// //       const int64_t expected_perblock_bucket = int64_t( double(initial_supply.get_amount()) * double(usecs_between_fills) * (0.25 * cont_rate/ 5.) / usecs_per_year )
// //                                                + initial_perblock_bucket;
// //       const int64_t expected_pervote_bucket  = int64_t( double(initial_supply.get_amount()) * double(usecs_between_fills) * (0.75 * cont_rate/ 5.) / usecs_per_year )
// //                                                + initial_pervote_bucket;
// //       const int64_t from_perblock_bucket = initial_unpaid_blocks * expected_perblock_bucket / initial_tot_unpaid_blocks ;
// //       const int64_t from_pervote_bucket  = int64_t( vote_shares[prod_index] * expected_pervote_bucket);

// //       BOOST_REQUIRE( 1 >= abs(int32_t(initial_tot_unpaid_blocks - tot_unpaid_blocks) - int32_t(initial_unpaid_blocks - unpaid_blocks)) );
// //       if (from_pervote_bucket >= 100 * 10000) {
// //          BOOST_REQUIRE( within_one( from_perblock_bucket + from_pervote_bucket, balance.get_amount() - initial_balance.get_amount() ) );
// //          BOOST_REQUIRE( within_one( expected_pervote_bucket - from_pervote_bucket, pervote_bucket ) );
// //          BOOST_REQUIRE( within_one( expected_pervote_bucket - from_pervote_bucket, vpay_balance.get_amount() ) );
// //          BOOST_REQUIRE( within_one( expected_perblock_bucket - from_perblock_bucket, perblock_bucket ) );
// //          BOOST_REQUIRE( within_one( expected_perblock_bucket - from_perblock_bucket, bpay_balance.get_amount() ) );
// //       } else {
// //          BOOST_REQUIRE( within_one( from_perblock_bucket, balance.get_amount() - initial_balance.get_amount() ) );
// //          BOOST_REQUIRE( within_one( expected_pervote_bucket, pervote_bucket ) );
// //       }

// //       produce_blocks(5);

// //       BOOST_REQUIRE_EQUAL(wasm_assert_msg("already claimed rewards within past day"),
// //                           push_action(prod_name, N(claimrewards), mvo()("owner", prod_name)));
// //    }

// //    {
// //       const uint32_t prod_index = 24;
// //       const auto prod_name = producer_names[prod_index];
// //       BOOST_REQUIRE_EQUAL(success(),
// //                           push_action(prod_name, N(claimrewards), mvo()("owner", prod_name)));
// //       BOOST_REQUIRE(100 * 10000 <= get_balance(prod_name).get_amount());
// //       BOOST_REQUIRE_EQUAL(wasm_assert_msg("already claimed rewards within past day"),
// //                           push_action(prod_name, N(claimrewards), mvo()("owner", prod_name)));
// //    }

//    {
//       const uint32_t rmv_index = 5;
//       account_name prod_name = producer_names[rmv_index];

//       auto info = get_producer_info(prod_name);
//       BOOST_REQUIRE( info["is_active"].as<bool>() );
//       BOOST_REQUIRE( fc::crypto::public_key() != fc::crypto::public_key(info["producer_key"].as_string()) );

//       BOOST_REQUIRE_EQUAL( error("missing authority of eosio"),
//                            push_action(prod_name, N(rmvproducer), mvo()("producer", prod_name)));
//       BOOST_REQUIRE_EQUAL( error("missing authority of eosio"),
//                            push_action(producer_names[rmv_index + 2], N(rmvproducer), mvo()("producer", prod_name) ) );
//       BOOST_REQUIRE_EQUAL( success(),
//                            push_action(config::system_account_name, N(rmvproducer), mvo()("producer", prod_name) ) );
//       {
//          bool rest_didnt_produce = true;
//          for (uint32_t i = 21; i < producer_names.size(); ++i) {
//             if (0 < get_producer_info(producer_names[i])["unpaid_blocks"].as<uint32_t>()) {
//                rest_didnt_produce = false;
//             }
//          }
//          BOOST_REQUIRE(rest_didnt_produce);
//       }

//       produce_blocks(3 * 21 * 12);
//       info = get_producer_info(prod_name);
//       const uint32_t init_unpaid_blocks = info["unpaid_blocks"].as<uint32_t>();
//       BOOST_REQUIRE( !info["is_active"].as<bool>() );
//       BOOST_REQUIRE( fc::crypto::public_key() == fc::crypto::public_key(info["producer_key"].as_string()) );
//       BOOST_REQUIRE_EQUAL( wasm_assert_msg("producer does not have an active key"),
//                            push_action(prod_name, N(claimrewards), mvo()("owner", prod_name) ) );
//       produce_blocks(3 * 21 * 12);
//       BOOST_REQUIRE_EQUAL( init_unpaid_blocks, get_producer_info(prod_name)["unpaid_blocks"].as<uint32_t>() );
//       {
//          bool prod_was_replaced = false;
//          for (uint32_t i = 21; i < producer_names.size(); ++i) {
//             if (0 < get_producer_info(producer_names[i])["unpaid_blocks"].as<uint32_t>()) {
//                prod_was_replaced = true;
//             }
//          }
//          BOOST_REQUIRE(prod_was_replaced);
//       }
//    }

//    {
//       BOOST_REQUIRE_EQUAL( wasm_assert_msg("producer not found"),
//                            push_action( config::system_account_name, N(rmvproducer), mvo()("producer", "nonexistingp") ) );
//    }

// } FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE(producers_upgrade_system_contract, eosio_system_tester) try {
   //install multisig contract
   abi_serializer msig_abi_ser = initialize_multisig();
   auto producer_names = active_and_vote_producers();

   //helper function
   auto push_action_msig = [&]( const account_name& signer, const action_name &name, const variant_object &data, bool auth = true ) -> action_result {
         string action_type_name = msig_abi_ser.get_action_type(name);

         action act;
         act.account = N(eosio.msig);
         act.name = name;
         act.data = msig_abi_ser.variant_to_binary( action_type_name, data, abi_serializer_max_time );

         return base_tester::push_action( std::move(act), auth ? uint64_t(signer) : signer == N(bob111111111) ? N(alice1111111) : N(bob111111111) );
   };
   // test begins
   vector<permission_level> prod_perms;
   for ( auto& x : producer_names ) {
      prod_perms.push_back( { name(x), config::active_name } );
   }

   transaction trx;
   {   
      //prepare system contract with different hash (contract differs in one byte)
      auto code = contracts::system_wasm();
      string msg = "producer votes must be unique and sorted";
      auto it = std::search( code.begin(), code.end(), msg.begin(), msg.end() );
      BOOST_REQUIRE( it != code.end() );
      msg[0] = 'P';
      std::copy( msg.begin(), msg.end(), it );

      variant pretty_trx = fc::mutable_variant_object()
         ("expiration", "2020-01-01T00:30")
         ("ref_block_num", 2)
         ("ref_block_prefix", 3)
         ("net_usage_words", 0)
         ("max_cpu_usage_ms", 0)
         ("delay_sec", 0)
         ("actions", fc::variants({
               fc::mutable_variant_object()
                  ("account", name(config::system_account_name))
                  ("name", "setcode")
                  ("authorization", vector<permission_level>{ { config::system_account_name, config::active_name } })
                  ("data", fc::mutable_variant_object() ("account", name(config::system_account_name))
                   ("vmtype", 0)
                   ("vmversion", "0")
                   ("code", bytes( code.begin(), code.end() ))
                  )
                  })
         );
      abi_serializer::from_variant(pretty_trx, trx, get_resolver(), abi_serializer_max_time);
   }

   BOOST_REQUIRE_EQUAL(success(), push_action_msig( N(alice1111111), N(propose), mvo()
                                                    ("proposer",      "alice1111111")
                                                    ("proposal_name", "upgrade1")
                                                    ("trx",           trx)
                                                    ("requested", prod_perms)
                       )
   );

   // get 15 approvals
   for ( size_t i = 0; i < 14; ++i ) {
      BOOST_REQUIRE_EQUAL(success(), push_action_msig( name(producer_names[i]), N(approve), mvo()
                                                       ("proposer",      "alice1111111")
                                                       ("proposal_name", "upgrade1")
                                                       ("level",         permission_level{ name(producer_names[i]), config::active_name })
                          )
      );
   }

   //should fail
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("transaction authorization failed"),
                       push_action_msig( N(alice1111111), N(exec), mvo()
                                         ("proposer",      "alice1111111")
                                         ("proposal_name", "upgrade1")
                                         ("executer",      "alice1111111")
                       )
   );

   // one more approval
   BOOST_REQUIRE_EQUAL(success(), push_action_msig( name(producer_names[14]), N(approve), mvo()
                                                    ("proposer",      "alice1111111")
                                                    ("proposal_name", "upgrade1")
                                                    ("level",         permission_level{ name(producer_names[14]), config::active_name })
                          )
   );

   transaction_trace_ptr trace;
   control->applied_transaction.connect([&]( const transaction_trace_ptr& t) { if (t->scheduled) { trace = t; } } );
   BOOST_REQUIRE_EQUAL(success(), push_action_msig( N(alice1111111), N(exec), mvo()
                                                    ("proposer",      "alice1111111")
                                                    ("proposal_name", "upgrade1")
                                                    ("executer",      "alice1111111")
                       )
   );

   BOOST_REQUIRE( bool(trace) );
   BOOST_REQUIRE_EQUAL( 1, trace->action_traces.size() );
   BOOST_REQUIRE_EQUAL( transaction_receipt::executed, trace->receipt->status );

   produce_blocks( 250 );

} FC_LOG_AND_RETHROW()


BOOST_FIXTURE_TEST_CASE(producer_onblock_check, eosio_system_tester) try {

   // min_activated_stake_part = 28'570'987'0000;
   const asset half_min_activated_stake = core_sym::from_string("14285493.5000");
   const asset quarter_min_activated_stake = core_sym::from_string("7142746.7500"); 
   const asset eight_min_activated_stake = core_sym::from_string("3571373.3750"); 

   const asset large_asset = core_sym::from_string("80.0000");
   create_account_with_resources( N(producvotera), config::system_account_name, core_sym::from_string("1.0000"), false, large_asset, large_asset );
   create_account_with_resources( N(producvoterb), config::system_account_name, core_sym::from_string("1.0000"), false, large_asset, large_asset );
   create_account_with_resources( N(producvoterc), config::system_account_name, core_sym::from_string("1.0000"), false, large_asset, large_asset );

   // create accounts {defproducera, defproducerb, ..., defproducerz} and register as producers
   std::vector<account_name> producer_names;
   producer_names.reserve('z' - 'a' + 1);
   const std::string root("defproducer");
   for ( char c = 'a'; c <= 'z'; ++c ) {
      producer_names.emplace_back(root + std::string(1, c));
   }
   setup_producer_accounts(producer_names);

   for (auto a:producer_names)
      regproducer(a);

   BOOST_REQUIRE_EQUAL(0, get_producer_info( producer_names.front() )["total_votes"].as<double>());
   BOOST_REQUIRE_EQUAL(0, get_producer_info( producer_names.back() )["total_votes"].as<double>());

   transfer(config::system_account_name, "producvotera", half_min_activated_stake, config::system_account_name);
   BOOST_REQUIRE_EQUAL(success(), stake("producvotera", quarter_min_activated_stake, quarter_min_activated_stake ));
   BOOST_REQUIRE_EQUAL(success(), vote( N(producvotera), vector<account_name>(producer_names.begin(), producer_names.begin()+10)));

   BOOST_CHECK_EQUAL( wasm_assert_msg( "cannot undelegate bandwidth until the chain is activated (1,000,000 blocks produced)" ),
                      unstake( "producvotera", core_sym::from_string("50.0000"), core_sym::from_string("50.0000") ) );

   // give a chance for everyone to produce blocks
   {
      produce_blocks(21 * 12);
      
      bool all_21_produced = true;
      for (uint32_t i = 0; i < 21; ++i) {
         if (0 == get_producer_info(producer_names[i])["unpaid_blocks"].as<uint32_t>()) {
            all_21_produced= false;
         }
      }
      bool rest_didnt_produce = true;
      for (uint32_t i = 21; i < producer_names.size(); ++i) {
         if (0 < get_producer_info(producer_names[i])["unpaid_blocks"].as<uint32_t>()) {
            rest_didnt_produce = false;
         }
      }
      BOOST_REQUIRE_EQUAL(false, all_21_produced);
      BOOST_REQUIRE_EQUAL(true, rest_didnt_produce);
   }

   {
      const char* claimrewards_activation_error_message = "cannot claim rewards until the chain is activated (1,000,000 blocks produced)";
      BOOST_CHECK_EQUAL(0, get_global_state()["total_unpaid_blocks"].as<uint32_t>());
      BOOST_REQUIRE_EQUAL(wasm_assert_msg( claimrewards_activation_error_message ),
                          push_action(producer_names.front(), N(claimrewards), mvo()("owner", producer_names.front())));
      BOOST_REQUIRE_EQUAL(0, get_balance(producer_names.front()).get_amount());
      BOOST_REQUIRE_EQUAL(wasm_assert_msg( claimrewards_activation_error_message ),
                          push_action(producer_names.back(), N(claimrewards), mvo()("owner", producer_names.back())));
      BOOST_REQUIRE_EQUAL(0, get_balance(producer_names.back()).get_amount());
   }

   
   // stake across 15% boundary
   transfer(config::system_account_name, "producvoterb", half_min_activated_stake, config::system_account_name);
   BOOST_REQUIRE_EQUAL(success(), stake("producvoterb", quarter_min_activated_stake, quarter_min_activated_stake));
   transfer(config::system_account_name, "producvoterc", quarter_min_activated_stake, config::system_account_name);
   BOOST_REQUIRE_EQUAL(success(), stake("producvoterc", eight_min_activated_stake, eight_min_activated_stake));
   
   // 21 => no rotation , 22 => yep, rotation
   BOOST_REQUIRE_EQUAL(success(), vote( N(producvoterb), vector<account_name>(producer_names.begin(), producer_names.begin()+22)));
   BOOST_REQUIRE_EQUAL(success(), vote( N(producvoterc), vector<account_name>(producer_names.begin(), producer_names.end())));
   
   activate_network();

   // give a chance for everyone to produce blocks
   {
      produce_blocks(21 * 12);
      for (uint32_t i = 0; i < producer_names.size(); ++i) {
         std::cout<<"["<<producer_names[i]<<"]: "<<get_producer_info(producer_names[i])["unpaid_blocks"].as<uint32_t>()<<std::endl;
      }

      bool all_21_produced = 0 < get_producer_info(producer_names[21])["unpaid_blocks"].as<uint32_t>();
      for (uint32_t i = 1; i < 21; ++i) {
         if (0 == get_producer_info(producer_names[i])["unpaid_blocks"].as<uint32_t>()) {
            all_21_produced= false;
         }
      }
      bool rest_didnt_produce = 0 == get_producer_info(producer_names[0])["unpaid_blocks"].as<uint32_t>();
      for (uint32_t i = 22; i < producer_names.size(); ++i) {
         if (0 < get_producer_info(producer_names[i])["unpaid_blocks"].as<uint32_t>()) {
            rest_didnt_produce = false;
         }
      }
      BOOST_REQUIRE_EQUAL(true, all_21_produced);
      BOOST_REQUIRE_EQUAL(true, rest_didnt_produce);
      
      
      const char* claimrewards_payment_missing = "No payment exists for account";
      BOOST_REQUIRE_EQUAL(wasm_assert_msg( claimrewards_payment_missing ),
                          push_action(producer_names.front(), N(claimrewards), mvo()("owner", producer_names.front())));

      //give time for snapshot
      produce_block(fc::minutes(30));
      produce_blocks(1);

      BOOST_REQUIRE_EQUAL(success(),
                          push_action(producer_names[1], N(claimrewards), mvo()("owner", producer_names[1])));
      BOOST_REQUIRE(0 < get_balance(producer_names[1]).get_amount());
   }

   BOOST_CHECK_EQUAL( success(), unstake( "producvotera", core_sym::from_string("50.0000"), core_sym::from_string("50.0000") ) );

} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( voter_and_proxy_actions_affect_producers_and_totals, eosio_system_tester, * boost::unit_test::tolerance(1e-4) ) try {
   create_accounts_with_resources( { N(donald111111), N(defproducer1), N(defproducer2), N(defproducer3) } );
   BOOST_REQUIRE_EQUAL( success(), regproducer( "defproducer1", 1) );
   BOOST_REQUIRE_EQUAL( success(), regproducer( "defproducer2", 2) );
   BOOST_REQUIRE_EQUAL( success(), regproducer( "defproducer3", 3) );
   
   //alice1111111 becomes a producer
   BOOST_REQUIRE_EQUAL( success(), push_action( N(alice1111111), N(regproxy), mvo()
                                                ("proxy",  "alice1111111")
                                                ("isproxy", true)
                        )
   );

   //bob111111111 becomes a producer
   BOOST_REQUIRE_EQUAL( success(), push_action( N(bob111111111), N(regproxy), mvo()
                                                ("proxy",  "bob111111111")
                                                ("isproxy", true)
                        )
   );

   REQUIRE_MATCHING_OBJECT( proxy( "alice1111111" ), get_voter_info( "alice1111111" ) );
   REQUIRE_MATCHING_OBJECT( proxy( "bob111111111" ), get_voter_info( "bob111111111" ) );

   //alice1111111 makes stake and votes
   issue( "alice1111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", core_sym::from_string("30.0001"), core_sym::from_string("20.0001") ) );
   BOOST_REQUIRE_EQUAL( success(), vote( N(alice1111111), { N(defproducer1), N(defproducer2) } ) );
   auto expected_value = stake2votes(core_sym::from_string("50.0002"),2,3);
   BOOST_TEST_REQUIRE( expected_value == get_producer_info( "defproducer1" )["total_votes"].as_double() );
   BOOST_TEST_REQUIRE( expected_value == get_producer_info( "defproducer2" )["total_votes"].as_double() );
   BOOST_REQUIRE_EQUAL( 0, get_producer_info( "defproducer3" )["total_votes"].as_double() );

   //donald111111 makes bob his proxy
   issue( "donald111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), stake( "donald111111", core_sym::from_string("5.0000"), core_sym::from_string("5.0000") ) );
   BOOST_REQUIRE_EQUAL( success(), vote( N(donald111111), vector<account_name>(), "bob111111111" ) );

   //bob111111111 bob stakes and votes
   issue( "bob111111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), stake( "bob111111111", core_sym::from_string("20.0001"), core_sym::from_string("20.0001") ) );
   BOOST_REQUIRE_EQUAL( success(), vote( N(bob111111111), { N(defproducer1), N(defproducer2) } ) );
   expected_value = stake2votes(core_sym::from_string("50.0002"),2,3) * 2;
   BOOST_TEST_REQUIRE( expected_value == get_producer_info( "defproducer1" )["total_votes"].as_double() );
   BOOST_TEST_REQUIRE( expected_value == get_producer_info( "defproducer2" )["total_votes"].as_double() );
   BOOST_REQUIRE_EQUAL( 0, get_producer_info( "defproducer3" )["total_votes"].as_double() );

   auto initial_activated_stake = get_global_state()["total_activated_stake"].as_int64();

   //donald111111 switches to alice as his proxy 
   BOOST_REQUIRE_EQUAL( success(), vote( N(donald111111), vector<account_name>(), "alice1111111" ) );
   BOOST_TEST_REQUIRE( expected_value == get_producer_info( "defproducer1" )["total_votes"].as_double() );
   BOOST_TEST_REQUIRE( expected_value == get_producer_info( "defproducer2" )["total_votes"].as_double() );
   BOOST_REQUIRE_EQUAL( 0, get_producer_info( "defproducer3" )["total_votes"].as_double() );

   expected_value = expected_value * 2; // 2 producers with same weight
   BOOST_TEST_REQUIRE(get_global_state()["total_producer_vote_weight"].as_double() == expected_value);
   // switching between proxies should not increase the total activated stake forever
   BOOST_TEST_REQUIRE(get_global_state()["total_activated_stake"].as_int64() == initial_activated_stake);

} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( voters_actions_affect_proxy_and_producers, eosio_system_tester, * boost::unit_test::tolerance(1e-4) ) try {
   activate_network();

   create_accounts_with_resources( { N(donald111111), N(defproducer1), N(defproducer2), N(defproducer3) } );
   BOOST_REQUIRE_EQUAL( success(), regproducer( "defproducer1", 1) );
   BOOST_REQUIRE_EQUAL( success(), regproducer( "defproducer2", 2) );
   BOOST_REQUIRE_EQUAL( success(), regproducer( "defproducer3", 3) );

   //alice1111111 becomes a producer
   BOOST_REQUIRE_EQUAL( success(), push_action( N(alice1111111), N(regproxy), mvo()
                                                ("proxy",  "alice1111111")
                                                ("isproxy", true)
                        )
   );
   REQUIRE_MATCHING_OBJECT( proxy( "alice1111111" ), get_voter_info( "alice1111111" ) );

   //alice1111111 makes stake and votes
   issue( "alice1111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", core_sym::from_string("30.0001"), core_sym::from_string("20.0001") ) );
   BOOST_REQUIRE_EQUAL( success(), vote( N(alice1111111), { N(defproducer1), N(defproducer2) } ) );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("50.0002"),2,3) == get_producer_info( "defproducer1" )["total_votes"].as_double() );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("50.0002"),2,3) == get_producer_info( "defproducer2" )["total_votes"].as_double() );
   BOOST_REQUIRE_EQUAL( 0, get_producer_info( "defproducer3" )["total_votes"].as_double() );

   BOOST_REQUIRE_EQUAL( success(), push_action( N(donald111111), N(regproxy), mvo()
                                                ("proxy",  "donald111111")
                                                ("isproxy", true)
                        )
   );
   REQUIRE_MATCHING_OBJECT( proxy( "donald111111" ), get_voter_info( "donald111111" ) );

   //bob111111111 chooses alice1111111 as a proxy
   issue( "bob111111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), stake( "bob111111111", core_sym::from_string("100.0002"), core_sym::from_string("50.0001") ) );
   BOOST_REQUIRE_EQUAL( success(), vote( N(bob111111111), vector<account_name>(), "alice1111111" ) );
   BOOST_TEST_REQUIRE( 1500003 == get_voter_info( "alice1111111" )["proxied_vote_weight"].as_double() );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("200.0005"),2,3) == get_producer_info( "defproducer1" )["total_votes"].as_double() );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("200.0005"),2,3) == get_producer_info( "defproducer2" )["total_votes"].as_double() );
   BOOST_REQUIRE_EQUAL( 0, get_producer_info( "defproducer3" )["total_votes"].as_double() );

   //carol1111111 chooses alice1111111 as a proxy
   issue( "carol1111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), stake( "carol1111111", core_sym::from_string("30.0001"), core_sym::from_string("20.0001") ) );
   BOOST_REQUIRE_EQUAL( success(), vote( N(carol1111111), vector<account_name>(), "alice1111111" ) );
   BOOST_TEST_REQUIRE( 2000005 == get_voter_info( "alice1111111" )["proxied_vote_weight"].as_double() );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("250.0007"),2,3) == get_producer_info( "defproducer1" )["total_votes"].as_double() );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("250.0007"),2,3) == get_producer_info( "defproducer2" )["total_votes"].as_double() );
   BOOST_REQUIRE_EQUAL( 0, get_producer_info( "defproducer3" )["total_votes"].as_double() );

   //proxied voter carol1111111 increases stake
   BOOST_REQUIRE_EQUAL( success(), stake( "carol1111111", core_sym::from_string("50.0000"), core_sym::from_string("70.0000") ) );
   BOOST_TEST_REQUIRE( 3200005 == get_voter_info( "alice1111111" )["proxied_vote_weight"].as_double() );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("370.0007"),2,3) == get_producer_info( "defproducer1" )["total_votes"].as_double() );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("370.0007"),2,3) == get_producer_info( "defproducer2" )["total_votes"].as_double() );
   BOOST_REQUIRE_EQUAL( 0, get_producer_info( "defproducer3" )["total_votes"].as_double() );

   //proxied voter bob111111111 decreases stake
   BOOST_REQUIRE_EQUAL( success(), unstake( "bob111111111", core_sym::from_string("50.0001"), core_sym::from_string("50.0001") ) );
   BOOST_TEST_REQUIRE( 2200003 == get_voter_info( "alice1111111" )["proxied_vote_weight"].as_double() );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("270.0005"),2,3) == get_producer_info( "defproducer1" )["total_votes"].as_double() );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("270.0005"),2,3) == get_producer_info( "defproducer2" )["total_votes"].as_double() );
   BOOST_REQUIRE_EQUAL( 0, get_producer_info( "defproducer3" )["total_votes"].as_double() );

   //proxied voter carol1111111 chooses another proxy
   BOOST_REQUIRE_EQUAL( success(), vote( N(carol1111111), vector<account_name>(), "donald111111" ) );
   BOOST_TEST_REQUIRE( 500001, get_voter_info( "alice1111111" )["proxied_vote_weight"].as_double() );
   BOOST_TEST_REQUIRE( 1700002, get_voter_info( "donald111111" )["proxied_vote_weight"].as_double() );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("100.0003"),2,3), get_producer_info( "defproducer1" )["total_votes"].as_double() );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("100.0003"),2,3), get_producer_info( "defproducer2" )["total_votes"].as_double() );
   BOOST_REQUIRE_EQUAL( 0, get_producer_info( "defproducer3" )["total_votes"].as_double() );

   //bob111111111 switches to direct voting and votes for one of the same producers, but not for another one
   BOOST_REQUIRE_EQUAL( success(), vote( N(bob111111111), { N(defproducer2) } ) );
   BOOST_TEST_REQUIRE( 0.0 == get_voter_info( "alice1111111" )["proxied_vote_weight"].as_double() );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("50.0002"),2,3), get_producer_info( "defproducer1" )["total_votes"].as_double() );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("100.0003"),1,3), get_producer_info( "defproducer2" )["total_votes"].as_double() );
   BOOST_TEST_REQUIRE( 0.0 == get_producer_info( "defproducer3" )["total_votes"].as_double() );

} FC_LOG_AND_RETHROW()


BOOST_FIXTURE_TEST_CASE( vote_both_proxy_and_producers, eosio_system_tester ) try {
   //alice1111111 becomes a proxy
   BOOST_REQUIRE_EQUAL( success(), push_action( N(alice1111111), N(regproxy), mvo()
                                                ("proxy",  "alice1111111")
                                                ("isproxy", true)
                        )
   );
   REQUIRE_MATCHING_OBJECT( proxy( "alice1111111" ), get_voter_info( "alice1111111" ) );

   //carol1111111 becomes a producer
   BOOST_REQUIRE_EQUAL( success(), regproducer( "carol1111111", 1) );

   //bob111111111 chooses alice1111111 as a proxy

   issue( "bob111111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), stake( "bob111111111", core_sym::from_string("100.0002"), core_sym::from_string("50.0001") ) );
   BOOST_REQUIRE_EQUAL( wasm_assert_msg("cannot vote for producers and proxy at same time"),
                        vote( N(bob111111111), { N(carol1111111) }, "alice1111111" ) );

} FC_LOG_AND_RETHROW()


BOOST_FIXTURE_TEST_CASE( select_invalid_proxy, eosio_system_tester ) try {
   //accumulate proxied votes
   issue( "bob111111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), stake( "bob111111111", core_sym::from_string("100.0002"), core_sym::from_string("50.0001") ) );

   //selecting account not registered as a proxy
   BOOST_REQUIRE_EQUAL( wasm_assert_msg( "invalid proxy specified" ),
                        vote( N(bob111111111), vector<account_name>(), "alice1111111" ) );

   //selecting not existing account as a proxy
   BOOST_REQUIRE_EQUAL( wasm_assert_msg( "invalid proxy specified" ),
                        vote( N(bob111111111), vector<account_name>(), "notexist" ) );

} FC_LOG_AND_RETHROW()


BOOST_FIXTURE_TEST_CASE( double_register_unregister_proxy_keeps_votes, eosio_system_tester ) try {
   //alice1111111 becomes a proxy
   BOOST_REQUIRE_EQUAL( success(), push_action( N(alice1111111), N(regproxy), mvo()
                                                ("proxy",  "alice1111111")
                                                ("isproxy",  1)
                        )
   );
   issue( "alice1111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", core_sym::from_string("5.0000"), core_sym::from_string("5.0000") ) );
   edump((get_voter_info("alice1111111")));
   REQUIRE_MATCHING_OBJECT( proxy( "alice1111111" )( "staked", 100000 ), get_voter_info( "alice1111111" ) );

   //bob111111111 stakes and selects alice1111111 as a proxy
   issue( "bob111111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), stake( "bob111111111", core_sym::from_string("100.0002"), core_sym::from_string("50.0001") ) );
   BOOST_REQUIRE_EQUAL( success(), vote( N(bob111111111), vector<account_name>(), "alice1111111" ) );
   REQUIRE_MATCHING_OBJECT( proxy( "alice1111111" )( "proxied_vote_weight", 1500003 )( "staked", 100000 ), get_voter_info( "alice1111111" ) );

   //double regestering should fail without affecting total votes and stake
   BOOST_REQUIRE_EQUAL( wasm_assert_msg( "action has no effect" ),
                        push_action( N(alice1111111), N(regproxy), mvo()
                                     ("proxy",  "alice1111111")
                                     ("isproxy",  1)
                        )
   );
   REQUIRE_MATCHING_OBJECT( proxy( "alice1111111" )( "proxied_vote_weight", 1500003 )( "staked", 100000 ), get_voter_info( "alice1111111" ) );

   //uregister
   BOOST_REQUIRE_EQUAL( success(), push_action( N(alice1111111), N(regproxy), mvo()
                                                ("proxy",  "alice1111111")
                                                ("isproxy",  0)
                        )
   );
   REQUIRE_MATCHING_OBJECT( voter( "alice1111111" )( "proxied_vote_weight", 1500003 )( "staked", 100000 ), get_voter_info( "alice1111111" ) );

   //double unregistering should not affect proxied_votes and stake
   BOOST_REQUIRE_EQUAL( wasm_assert_msg( "action has no effect" ),
                        push_action( N(alice1111111), N(regproxy), mvo()
                                     ("proxy",  "alice1111111")
                                     ("isproxy",  0)
                        )
   );
   REQUIRE_MATCHING_OBJECT( voter( "alice1111111" )( "proxied_vote_weight", 1500003 )( "staked", 100000 ), get_voter_info( "alice1111111" ) );

} FC_LOG_AND_RETHROW()


BOOST_FIXTURE_TEST_CASE( proxy_cannot_use_another_proxy, eosio_system_tester ) try {
   //alice1111111 becomes a proxy
   BOOST_REQUIRE_EQUAL( success(), push_action( N(alice1111111), N(regproxy), mvo()
                                                ("proxy",  "alice1111111")
                                                ("isproxy",  1)
                        )
   );

   //bob111111111 becomes a proxy
   BOOST_REQUIRE_EQUAL( success(), push_action( N(bob111111111), N(regproxy), mvo()
                                                ("proxy",  "bob111111111")
                                                ("isproxy",  1)
                        )
   );

   //proxy should not be able to use a proxy
   issue( "bob111111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), stake( "bob111111111", core_sym::from_string("100.0002"), core_sym::from_string("50.0001") ) );
   BOOST_REQUIRE_EQUAL( wasm_assert_msg( "account registered as a proxy is not allowed to use a proxy" ),
                        vote( N(bob111111111), vector<account_name>(), "alice1111111" ) );

   //voter that uses a proxy should not be allowed to become a proxy
   issue( "carol1111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), stake( "carol1111111", core_sym::from_string("100.0002"), core_sym::from_string("50.0001") ) );
   BOOST_REQUIRE_EQUAL( success(), vote( N(carol1111111), vector<account_name>(), "alice1111111" ) );
   BOOST_REQUIRE_EQUAL( wasm_assert_msg( "account that uses a proxy is not allowed to become a proxy" ),
                        push_action( N(carol1111111), N(regproxy), mvo()
                                     ("proxy",  "carol1111111")
                                     ("isproxy",  1)
                        )
   );

   //proxy should not be able to use itself as a proxy
   BOOST_REQUIRE_EQUAL( wasm_assert_msg( "cannot proxy to self" ),
                        vote( N(bob111111111), vector<account_name>(), "bob111111111" ) );

} FC_LOG_AND_RETHROW()

fc::mutable_variant_object config_to_variant( const eosio::chain::chain_config& config ) {
   return mutable_variant_object()
      ( "max_block_net_usage", config.max_block_net_usage )
      ( "target_block_net_usage_pct", config.target_block_net_usage_pct )
      ( "max_transaction_net_usage", config.max_transaction_net_usage )
      ( "base_per_transaction_net_usage", config.base_per_transaction_net_usage )
      ( "context_free_discount_net_usage_num", config.context_free_discount_net_usage_num )
      ( "context_free_discount_net_usage_den", config.context_free_discount_net_usage_den )
      ( "max_block_cpu_usage", config.max_block_cpu_usage )
      ( "target_block_cpu_usage_pct", config.target_block_cpu_usage_pct )
      ( "max_transaction_cpu_usage", config.max_transaction_cpu_usage )
      ( "min_transaction_cpu_usage", config.min_transaction_cpu_usage )
      ( "max_transaction_lifetime", config.max_transaction_lifetime )
      ( "deferred_trx_expiration_window", config.deferred_trx_expiration_window )
      ( "max_transaction_delay", config.max_transaction_delay )
      ( "max_inline_action_size", config.max_inline_action_size )
      ( "max_inline_action_depth", config.max_inline_action_depth )
      ( "max_authority_depth", config.max_authority_depth );
}

BOOST_FIXTURE_TEST_CASE( elect_producers /*_and_parameters*/, eosio_system_tester ) try {
   create_accounts_with_resources( {  N(defproducer1), N(defproducer2), N(defproducer3) } );
   BOOST_REQUIRE_EQUAL( success(), regproducer( "defproducer1", 1) );
   BOOST_REQUIRE_EQUAL( success(), regproducer( "defproducer2", 2) );
   BOOST_REQUIRE_EQUAL( success(), regproducer( "defproducer3", 3) );

   //stake more than 15% of total EOS supply to activate chain
   transfer( "eosio", "alice1111111", core_sym::from_string("600000000.0000"), "eosio" );
   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", "alice1111111", core_sym::from_string("300000000.0000"), core_sym::from_string("300000000.0000") ) );
   //vote for producers
   BOOST_REQUIRE_EQUAL( success(), vote( N(alice1111111), { N(defproducer1) } ) );
   
   activate_network();

   produce_blocks(250);
   auto producer_keys = control->head_block_state()->active_schedule.producers;
   BOOST_REQUIRE_EQUAL( 1, producer_keys.size() );
   BOOST_REQUIRE_EQUAL( name("defproducer1"), producer_keys[0].producer_name );

   //auto config = config_to_variant( control->get_global_properties().configuration );
   //auto prod1_config = testing::filter_fields( config, producer_parameters_example( 1 ) );
   //REQUIRE_EQUAL_OBJECTS(prod1_config, config);

   // elect 2 producers
   issue( "bob111111111", core_sym::from_string("80000.0000"),  config::system_account_name );
   ilog("stake");
   BOOST_REQUIRE_EQUAL( success(), stake( "bob111111111", core_sym::from_string("40000.0000"), core_sym::from_string("40000.0000") ) );
   ilog("start vote");
   BOOST_REQUIRE_EQUAL( success(), vote( N(bob111111111), { N(defproducer2) } ) );
   ilog(".");
   produce_blocks(250);
   producer_keys = control->head_block_state()->active_schedule.producers;
   BOOST_REQUIRE_EQUAL( 2, producer_keys.size() );
   BOOST_REQUIRE_EQUAL( name("defproducer1"), producer_keys[0].producer_name );
   BOOST_REQUIRE_EQUAL( name("defproducer2"), producer_keys[1].producer_name );
   //config = config_to_variant( control->get_global_properties().configuration );
   //auto prod2_config = testing::filter_fields( config, producer_parameters_example( 2 ) );
   //REQUIRE_EQUAL_OBJECTS(prod2_config, config);

   // elect 3 producers
   BOOST_REQUIRE_EQUAL( success(), vote( N(bob111111111), { N(defproducer2), N(defproducer3) } ) );
   produce_blocks(250);
   producer_keys = control->head_block_state()->active_schedule.producers;
   BOOST_REQUIRE_EQUAL( 3, producer_keys.size() );
   BOOST_REQUIRE_EQUAL( name("defproducer1"), producer_keys[0].producer_name );
   BOOST_REQUIRE_EQUAL( name("defproducer2"), producer_keys[1].producer_name );
   BOOST_REQUIRE_EQUAL( name("defproducer3"), producer_keys[2].producer_name );
   //config = config_to_variant( control->get_global_properties().configuration );
   //REQUIRE_EQUAL_OBJECTS(prod2_config, config);

   // try to go back to 2 producers and fail
   BOOST_REQUIRE_EQUAL( success(), vote( N(bob111111111), { N(defproducer3) } ) );
   produce_blocks(250);
   producer_keys = control->head_block_state()->active_schedule.producers;
   /*
   wdump((producer_keys));
   BOOST_REQUIRE_EQUAL( 3, producer_keys.size() );
   */

   // The test below is invalid now, producer schedule is not updated if there are
   // fewer producers in the new schedule
   BOOST_REQUIRE_EQUAL( 2, producer_keys.size() );
   BOOST_REQUIRE_EQUAL( name("defproducer1"), producer_keys[0].producer_name );
   BOOST_REQUIRE_EQUAL( name("defproducer3"), producer_keys[1].producer_name );
   /*
   //config = config_to_variant( control->get_global_properties().configuration );
   //auto prod3_config = testing::filter_fields( config, producer_parameters_example( 3 ) );
   //REQUIRE_EQUAL_OBJECTS(prod3_config, config);
   */

} FC_LOG_AND_RETHROW()


BOOST_FIXTURE_TEST_CASE( buyname, eosio_system_tester ) try {
   create_accounts_with_resources( { N(dan), N(sam) } );
   transfer( config::system_account_name, "dan", core_sym::from_string( "10000.0000" ) );
   transfer( config::system_account_name, "sam", core_sym::from_string( "10000.0000" ) );
   stake_with_transfer( config::system_account_name, "sam", core_sym::from_string( "80000000.0000" ), core_sym::from_string( "80000000.0000" ) );
   stake_with_transfer( config::system_account_name, "dan", core_sym::from_string( "80000000.0000" ), core_sym::from_string( "80000000.0000" ) );

   regproducer( config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), vote( N(sam), { config::system_account_name } ) );

   activate_network();
   // wait 14 days after min required amount has been staked
   produce_block( fc::days(7) );
   BOOST_REQUIRE_EQUAL( success(), vote( N(dan), { config::system_account_name } ) );
   produce_block( fc::days(7) );
   produce_block();

   BOOST_REQUIRE_EXCEPTION( create_accounts_with_resources( { N(fail) }, N(dan) ), // dan shouldn't be able to create fail
                            eosio_assert_message_exception, eosio_assert_message_is( "no active bid for name" ) );
   bidname( "dan", "nofail", core_sym::from_string( "1.0000" ) );
   BOOST_REQUIRE_EQUAL( "assertion failure with message: must increase bid by 10%", bidname( "sam", "nofail", core_sym::from_string( "1.0000" ) )); // didn't increase bid by 10%
   BOOST_REQUIRE_EQUAL( success(), bidname( "sam", "nofail", core_sym::from_string( "2.0000" ) )); // didn't increase bid by 10%
   produce_block( fc::days(1) );
   produce_block();

   BOOST_REQUIRE_EXCEPTION( create_accounts_with_resources( { N(nofail) }, N(dan) ), // dan shoudn't be able to do this, sam won
                            eosio_assert_message_exception, eosio_assert_message_is( "only highest bidder can claim" ) );
   //wlog( "verify sam can create nofail" );
   create_accounts_with_resources( { N(nofail) }, N(sam) ); // sam should be able to do this, he won the bid
   //wlog( "verify nofail can create test.nofail" );
   transfer( "eosio", "nofail", core_sym::from_string( "1000.0000" ) );
   create_accounts_with_resources( { N(test.nofail) }, N(nofail) ); // only nofail can create test.nofail
   //wlog( "verify dan cannot create test.fail" );
   BOOST_REQUIRE_EXCEPTION( create_accounts_with_resources( { N(test.fail) }, N(dan) ), // dan shouldn't be able to do this
                            eosio_assert_message_exception, eosio_assert_message_is( "only suffix may create this account" ) );

   create_accounts_with_resources( { N(goodgoodgood) }, N(dan) ); /// 12 char names should succeed
} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( bid_invalid_names, eosio_system_tester ) try {
   create_accounts_with_resources( { N(dan) } );

   BOOST_REQUIRE_EQUAL( wasm_assert_msg( "you can only bid on top-level suffix" ),
                        bidname( "dan", "abcdefg.12345", core_sym::from_string( "1.0000" ) ) );

   BOOST_REQUIRE_EQUAL( wasm_assert_msg( "the empty name is not a valid account name to bid on" ),
                        bidname( "dan", "", core_sym::from_string( "1.0000" ) ) );

   BOOST_REQUIRE_EQUAL( wasm_assert_msg( "13 character names are not valid account names to bid on" ),
                        bidname( "dan", "abcdefgh12345", core_sym::from_string( "1.0000" ) ) );

   BOOST_REQUIRE_EQUAL( wasm_assert_msg( "accounts with 12 character names and no dots can be created without bidding required" ),
                        bidname( "dan", "abcdefg12345", core_sym::from_string( "1.0000" ) ) );

} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( multiple_namebids, eosio_system_tester ) try {

   const std::string not_closed_message("auction for name is not closed yet");

   std::vector<account_name> accounts = { N(alice), N(bob), N(carl), N(david), N(eve) };
   create_accounts_with_resources( accounts );
   for ( const auto& a: accounts ) {
      transfer( config::system_account_name, a, core_sym::from_string( "10000.0000" ) );
      BOOST_REQUIRE_EQUAL( core_sym::from_string( "10000.0000" ), get_balance(a) );
   }
   create_accounts_with_resources( { N(producer) } );
   BOOST_REQUIRE_EQUAL( success(), regproducer( N(producer) ) );

   produce_block();
   // stake but but not enough to go live
   stake_with_transfer( config::system_account_name, "bob",  core_sym::from_string( "3500000.0000" ), core_sym::from_string( "3500000.0000" ) );
   stake_with_transfer( config::system_account_name, "carl", core_sym::from_string( "3500000.0000" ), core_sym::from_string( "3500000.0000" ) );
   BOOST_REQUIRE_EQUAL( success(), vote( N(bob), { N(producer) } ) );
   BOOST_REQUIRE_EQUAL( success(), vote( N(carl), { N(producer) } ) );

   // start bids
   bidname( "bob",  "prefa", core_sym::from_string("1.0003") );
   BOOST_REQUIRE_EQUAL( core_sym::from_string( "9998.9997" ), get_balance("bob") );
   bidname( "bob",  "prefb", core_sym::from_string("1.0000") );
   bidname( "bob",  "prefc", core_sym::from_string("1.0000") );
   BOOST_REQUIRE_EQUAL( core_sym::from_string( "9996.9997" ), get_balance("bob") );

   bidname( "carl", "prefd", core_sym::from_string("1.0000") );
   bidname( "carl", "prefe", core_sym::from_string("1.0000") );
   BOOST_REQUIRE_EQUAL( core_sym::from_string( "9998.0000" ), get_balance("carl") );

   BOOST_REQUIRE_EQUAL( error("assertion failure with message: account is already highest bidder"),
                        bidname( "bob", "prefb", core_sym::from_string("1.1001") ) );
   BOOST_REQUIRE_EQUAL( error("assertion failure with message: must increase bid by 10%"),
                        bidname( "alice", "prefb", core_sym::from_string("1.0999") ) );
   BOOST_REQUIRE_EQUAL( core_sym::from_string( "9996.9997" ), get_balance("bob") );
   BOOST_REQUIRE_EQUAL( core_sym::from_string( "10000.0000" ), get_balance("alice") );

   // alice outbids bob on prefb
   {
      const asset initial_names_balance = get_balance(N(eosio.names));
      BOOST_REQUIRE_EQUAL( success(),
                           bidname( "alice", "prefb", core_sym::from_string("1.1001") ) );
      BOOST_REQUIRE_EQUAL( core_sym::from_string( "9997.9997" ), get_balance("bob") );
      BOOST_REQUIRE_EQUAL( core_sym::from_string( "9998.8999" ), get_balance("alice") );
      BOOST_REQUIRE_EQUAL( initial_names_balance + core_sym::from_string("0.1001"), get_balance(N(eosio.names)) );
   }

   // david outbids carl on prefd
   {
      BOOST_REQUIRE_EQUAL( core_sym::from_string( "9998.0000" ), get_balance("carl") );
      BOOST_REQUIRE_EQUAL( core_sym::from_string( "10000.0000" ), get_balance("david") );
      BOOST_REQUIRE_EQUAL( success(),
                           bidname( "david", "prefd", core_sym::from_string("1.9900") ) );
      BOOST_REQUIRE_EQUAL( core_sym::from_string( "9999.0000" ), get_balance("carl") );
      BOOST_REQUIRE_EQUAL( core_sym::from_string( "9998.0100" ), get_balance("david") );
   }

   // eve outbids carl on prefe
   {
      BOOST_REQUIRE_EQUAL( success(),
                           bidname( "eve", "prefe", core_sym::from_string("1.7200") ) );
   }

   produce_block( fc::days(14) );
   produce_block();

   // highest bid is from david for prefd but no bids can be closed yet
   BOOST_REQUIRE_EXCEPTION( create_account_with_resources( N(prefd), N(david) ),
                            fc::exception, fc_assert_exception_message_is( not_closed_message ) );

   // stake enough to go above the 15% threshold ~ total of ~~30M = 16 + 14 above (minstake to activate ~29M)
   stake_with_transfer( config::system_account_name, "alice", core_sym::from_string( "8000000.0000" ), core_sym::from_string( "8000000.0000" ) );
   BOOST_REQUIRE_EQUAL(0, get_producer_info("producer")["unpaid_blocks"].as<uint32_t>());
   BOOST_REQUIRE_EQUAL( success(), vote( N(alice), { N(producer) } ) );

   activate_network();

   // need to wait for 14 days after going live
   produce_blocks(10);
   produce_block( fc::days(2) );
   produce_blocks( 10 );
   BOOST_REQUIRE_EXCEPTION( create_account_with_resources( N(prefd), N(david) ),
                            fc::exception, fc_assert_exception_message_is( not_closed_message ) );
   // it's been 14 days, auction for prefd has been closed
   produce_block( fc::days(12) );
   create_account_with_resources( N(prefd), N(david) );
   produce_blocks(2);
   produce_block( fc::hours(23) );
   // auctions for prefa, prefb, prefc, prefe haven't been closed
   BOOST_REQUIRE_EXCEPTION( create_account_with_resources( N(prefa), N(bob) ),
                            fc::exception, fc_assert_exception_message_is( not_closed_message ) );
   BOOST_REQUIRE_EXCEPTION( create_account_with_resources( N(prefb), N(alice) ),
                            fc::exception, fc_assert_exception_message_is( not_closed_message ) );
   BOOST_REQUIRE_EXCEPTION( create_account_with_resources( N(prefc), N(bob) ),
                            fc::exception, fc_assert_exception_message_is( not_closed_message ) );
   BOOST_REQUIRE_EXCEPTION( create_account_with_resources( N(prefe), N(eve) ),
                            fc::exception, fc_assert_exception_message_is( not_closed_message ) );
   // attemp to create account with no bid
   BOOST_REQUIRE_EXCEPTION( create_account_with_resources( N(prefg), N(alice) ),
                            fc::exception, fc_assert_exception_message_is( "no active bid for name" ) );
   // changing highest bid pushes auction closing time by 24 hours
   BOOST_REQUIRE_EQUAL( success(),
                        bidname( "eve",  "prefb", core_sym::from_string("2.1880") ) );

   produce_block( fc::hours(22) );
   produce_blocks(2);

   BOOST_REQUIRE_EXCEPTION( create_account_with_resources( N(prefb), N(eve) ),
                            fc::exception, fc_assert_exception_message_is( not_closed_message ) );
   // but changing a bid that is not the highest does not push closing time
   BOOST_REQUIRE_EQUAL( success(),
                        bidname( "carl", "prefe", core_sym::from_string("2.0980") ) );
   produce_block( fc::hours(2) );
   produce_blocks(2);
   // bid for prefb has closed, only highest bidder can claim
   BOOST_REQUIRE_EXCEPTION( create_account_with_resources( N(prefb), N(alice) ),
                            eosio_assert_message_exception, eosio_assert_message_is( "only highest bidder can claim" ) );
   BOOST_REQUIRE_EXCEPTION( create_account_with_resources( N(prefb), N(carl) ),
                            eosio_assert_message_exception, eosio_assert_message_is( "only highest bidder can claim" ) );
   create_account_with_resources( N(prefb), N(eve) );

   BOOST_REQUIRE_EXCEPTION( create_account_with_resources( N(prefe), N(carl) ),
                            fc::exception, fc_assert_exception_message_is( not_closed_message ) );
   produce_block();
   produce_block( fc::hours(24) );
   // by now bid for prefe has closed
   create_account_with_resources( N(prefe), N(carl) );
   // prefe can now create *.prefe
   BOOST_REQUIRE_EXCEPTION( create_account_with_resources( N(xyz.prefe), N(carl) ),
                            fc::exception, fc_assert_exception_message_is("only suffix may create this account") );
   transfer( config::system_account_name, N(prefe), core_sym::from_string("10000.0000") );
   create_account_with_resources( N(xyz.prefe), N(prefe) );

   // other auctions haven't closed
   BOOST_REQUIRE_EXCEPTION( create_account_with_resources( N(prefa), N(bob) ),
                            fc::exception, fc_assert_exception_message_is( not_closed_message ) );

} FC_LOG_AND_RETHROW()

// BOOST_FIXTURE_TEST_CASE( namebid_pending_winner, eosio_system_tester ) try {
//    activate_network();
//    produce_block( fc::hours(14*24) );    //wait 14 day for name auction activation
//    transfer( config::system_account_name, N(alice1111111), core_sym::from_string("10000.0000") );
//    transfer( config::system_account_name, N(bob111111111), core_sym::from_string("10000.0000") );

//    BOOST_REQUIRE_EQUAL( success(), bidname( "alice1111111", "prefa", core_sym::from_string( "50.0000" ) ));
//    BOOST_REQUIRE_EQUAL( success(), bidname( "bob111111111", "prefb", core_sym::from_string( "30.0000" ) ));
//    produce_block( fc::hours(100) ); //should close "perfa"
//    produce_block( fc::hours(100) ); //should close "perfb"

//    //despite "perfa" account hasn't been created, we should be able to create "perfb" account
//    create_account_with_resources( N(prefb), N(bob111111111) );
// } FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( vote_producers_in_and_out, eosio_system_tester ) try {
      activate_network();
   const asset net = core_sym::from_string("80.0000");
   const asset cpu = core_sym::from_string("80.0000");
   std::vector<account_name> voters = { N(producvotera), N(producvoterb), N(producvoterc), N(producvoterd) };
   for (const auto& v: voters) {
      create_account_with_resources(v, config::system_account_name, core_sym::from_string("1.0000"), false, net, cpu);
   }

   // create accounts {defproducera, defproducerb, ..., defproducerz} and register as producers
   std::vector<account_name> producer_names;
   {
      producer_names.reserve('z' - 'a' + 1);
      const std::string root("defproducer");
      for ( char c = 'a'; c <= 'z'; ++c ) {
         producer_names.emplace_back(root + std::string(1, c));
      }
      setup_producer_accounts(producer_names);
      for (const auto& p: producer_names) {
         BOOST_REQUIRE_EQUAL( success(), regproducer(p) );
         produce_blocks(1);
         ilog( "------ get pro----------" );
         wdump((p));
         BOOST_TEST(0 == get_producer_info(p)["total_votes"].as<double>());
      }
   }

   for (const auto& v: voters) {
      transfer( config::system_account_name, v, core_sym::from_string("200000000.0000"), config::system_account_name );
      BOOST_REQUIRE_EQUAL(success(), stake(v, core_sym::from_string("30000000.0000"), core_sym::from_string("30000000.0000")) );
   }

   {
      BOOST_REQUIRE_EQUAL(success(), vote(N(producvotera), vector<account_name>(producer_names.begin(), producer_names.begin()+20)));
      BOOST_REQUIRE_EQUAL(success(), vote(N(producvoterb), vector<account_name>(producer_names.begin(), producer_names.begin()+21)));
      BOOST_REQUIRE_EQUAL(success(), vote(N(producvoterc), vector<account_name>(producer_names.begin(), producer_names.end())));
   }

   // give a chance for everyone to produce blocks
   {
      // produce_blocks(23 * 12 + 20);
      // ?? why is there a need for such a high number of blocks for everyone to produce ?? 
      produce_blocks(51 * 24 + 20);
      // for (uint32_t i = 0; i < producer_names.size(); ++i) {
      //    std::cout<<"["<<producer_names[i]<<"]: "<<get_producer_info(producer_names[i])["unpaid_blocks"].as<uint32_t>()<<std::endl;
      // }

      bool all_21_produced = true;
      for (uint32_t i = 0; i < 21; ++i) {
         if (0 == get_producer_info(producer_names[i])["unpaid_blocks"].as<uint32_t>()) {
            all_21_produced = false;
         }
      }
      bool rest_didnt_produce = true;
      for (uint32_t i = 21; i < producer_names.size(); ++i) {
         if (0 < get_producer_info(producer_names[i])["unpaid_blocks"].as<uint32_t>()) {
            rest_didnt_produce = false;
         }
      }
      BOOST_REQUIRE(all_21_produced && rest_didnt_produce);
   }

   {
      
      // for (uint32_t i = 0; i < producer_names.size(); ++i) {
      //    std::cout<<"["<<producer_names[i]<<"]: "<<get_producer_info(producer_names[i])["unpaid_blocks"].as<uint32_t>()<<std::endl;
      // }
      // std::cout<<"============"<<std::endl;
      // for (uint32_t i = 0; i < producer_names.size(); ++i) {
      //    std::cout<<"["<<producer_names[i]<<"]: "<<get_producer_info(producer_names[i])["unpaid_blocks"].as<uint32_t>()<<std::endl;
      // }

      // produce_block(fc::hours(7)); // this would trigger a rotation and the next checks would fail
      produce_block(fc::hours(3));
      const uint32_t voted_out_index = 20;
      const uint32_t new_prod_index  = 23;
      // the new weight calculation gives bigger weight for more voted producers
      vector<account_name> v = vector<account_name>(producer_names.begin(), producer_names.begin()+(voted_out_index-1)); 
      v.emplace_back(producer_names[new_prod_index]);

      BOOST_REQUIRE_EQUAL(success(), stake("producvoterd", core_sym::from_string("40000000.0000"), core_sym::from_string("40000000.0000")));
      BOOST_REQUIRE_EQUAL(success(), vote(N(producvoterd), v)); 
      BOOST_REQUIRE_EQUAL(0, get_producer_info(producer_names[new_prod_index])["unpaid_blocks"].as<uint32_t>());
      produce_blocks(4 * 24 * 21); 
      BOOST_REQUIRE(0 < get_producer_info(producer_names[new_prod_index])["unpaid_blocks"].as<uint32_t>());
      const uint32_t initial_unpaid_blocks = get_producer_info(producer_names[voted_out_index])["unpaid_blocks"].as<uint32_t>();
      produce_blocks(2 * 24 * 21);
      BOOST_REQUIRE_EQUAL(initial_unpaid_blocks, get_producer_info(producer_names[voted_out_index])["unpaid_blocks"].as<uint32_t>());
      produce_block(fc::hours(24));
      BOOST_REQUIRE_EQUAL(success(), vote(N(producvoterd), { producer_names[voted_out_index] }));
      produce_blocks(2 * 24 * 21);
      BOOST_REQUIRE(fc::crypto::public_key() != fc::crypto::public_key(get_producer_info(producer_names[voted_out_index])["producer_key"].as_string()));
      BOOST_REQUIRE_EQUAL(success(), push_action(producer_names[voted_out_index], N(claimrewards), mvo()("owner", producer_names[voted_out_index])));
   }

} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( setparams, eosio_system_tester ) try {
   //install multisig contract
   abi_serializer msig_abi_ser = initialize_multisig();
   auto producer_names = active_and_vote_producers();

   //helper function
   auto push_action_msig = [&]( const account_name& signer, const action_name &name, const variant_object &data, bool auth = true ) -> action_result {
         string action_type_name = msig_abi_ser.get_action_type(name);

         action act;
         act.account = N(eosio.msig);
         act.name = name;
         act.data = msig_abi_ser.variant_to_binary( action_type_name, data, abi_serializer_max_time );

         return base_tester::push_action( std::move(act), auth ? uint64_t(signer) : signer == N(bob111111111) ? N(alice1111111) : N(bob111111111) );
   };

   // test begins
   vector<permission_level> prod_perms;
   for ( auto& x : producer_names ) {
      prod_perms.push_back( { name(x), config::active_name } );
   }

   eosio::chain::chain_config params;
   params = control->get_global_properties().configuration;
   //change some values
   params.max_block_net_usage += 10;
   params.max_transaction_lifetime += 1;

   transaction trx;
   {
      variant pretty_trx = fc::mutable_variant_object()
         ("expiration", "2020-01-01T00:30")
         ("ref_block_num", 2)
         ("ref_block_prefix", 3)
         ("net_usage_words", 0)
         ("max_cpu_usage_ms", 0)
         ("delay_sec", 0)
         ("actions", fc::variants({
               fc::mutable_variant_object()
                  ("account", name(config::system_account_name))
                  ("name", "setparams")
                  ("authorization", vector<permission_level>{ { config::system_account_name, config::active_name } })
                  ("data", fc::mutable_variant_object()
                   ("params", params)
                  )
                  })
         );
      abi_serializer::from_variant(pretty_trx, trx, get_resolver(), abi_serializer_max_time);
   }

   BOOST_REQUIRE_EQUAL(success(), push_action_msig( N(alice1111111), N(propose), mvo()
                                                    ("proposer",      "alice1111111")
                                                    ("proposal_name", "setparams1")
                                                    ("trx",           trx)
                                                    ("requested", prod_perms)
                       )
   );

   // get 16 approvals
   for ( size_t i = 0; i < 15; ++i ) {
      BOOST_REQUIRE_EQUAL(success(), push_action_msig( name(producer_names[i]), N(approve), mvo()
                                                       ("proposer",      "alice1111111")
                                                       ("proposal_name", "setparams1")
                                                       ("level",         permission_level{ name(producer_names[i]), config::active_name })
                          )
      );
   }

   transaction_trace_ptr trace;
   control->applied_transaction.connect([&]( const transaction_trace_ptr& t) { if (t->scheduled) { trace = t; } } );
   BOOST_REQUIRE_EQUAL(success(), push_action_msig( N(alice1111111), N(exec), mvo()
                                                    ("proposer",      "alice1111111")
                                                    ("proposal_name", "setparams1")
                                                    ("executer",      "alice1111111")
                       )
   );

   BOOST_REQUIRE( bool(trace) );
   BOOST_REQUIRE_EQUAL( 1, trace->action_traces.size() );
   BOOST_REQUIRE_EQUAL( transaction_receipt::executed, trace->receipt->status );

   produce_blocks( 250 );

   // make sure that changed parameters were applied
   auto active_params = control->get_global_properties().configuration;
   BOOST_REQUIRE_EQUAL( params.max_block_net_usage, active_params.max_block_net_usage );
   BOOST_REQUIRE_EQUAL( params.max_transaction_lifetime, active_params.max_transaction_lifetime );

} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( setram_effect, eosio_system_tester ) try {

   const asset net = core_sym::from_string("8.0000");
   const asset cpu = core_sym::from_string("8.0000");
   std::vector<account_name> accounts = { N(aliceaccount), N(bobbyaccount) };
   for (const auto& a: accounts) {
      create_account_with_resources(a, config::system_account_name, core_sym::from_string("1.0000"), false, net, cpu);
   }

   {
      const auto name_a = accounts[0];
      transfer( config::system_account_name, name_a, core_sym::from_string("1000.0000") );
      BOOST_REQUIRE_EQUAL( core_sym::from_string("1000.0000"), get_balance(name_a) );
      const uint64_t init_bytes_a = get_total_stake(name_a)["ram_bytes"].as_uint64();
      BOOST_REQUIRE_EQUAL( success(), buyram( name_a, name_a, core_sym::from_string("300.0000") ) );
      BOOST_REQUIRE_EQUAL( core_sym::from_string("700.0000"), get_balance(name_a) );
      const uint64_t bought_bytes_a = get_total_stake(name_a)["ram_bytes"].as_uint64() - init_bytes_a;

      // after buying and selling balance should be 700 + 300 * 0.995 * 0.995 = 997.0075 (actually 997.0074 due to rounding fees up)
      BOOST_REQUIRE_EQUAL( success(), sellram(name_a, bought_bytes_a ) );
      BOOST_REQUIRE_EQUAL( core_sym::from_string("997.0074"), get_balance(name_a) );
   }

   {
      const auto name_b = accounts[1];
      transfer( config::system_account_name, name_b, core_sym::from_string("1000.0000") );
      BOOST_REQUIRE_EQUAL( core_sym::from_string("1000.0000"), get_balance(name_b) );
      const uint64_t init_bytes_b = get_total_stake(name_b)["ram_bytes"].as_uint64();
      // name_b buys ram at current price
      BOOST_REQUIRE_EQUAL( success(), buyram( name_b, name_b, core_sym::from_string("300.0000") ) );
      BOOST_REQUIRE_EQUAL( core_sym::from_string("700.0000"), get_balance(name_b) );
      const uint64_t bought_bytes_b = get_total_stake(name_b)["ram_bytes"].as_uint64() - init_bytes_b;

      // increase max_ram_size, ram bought by name_b loses part of its value
      BOOST_REQUIRE_EQUAL( wasm_assert_msg("ram may only be increased"),
                           push_action(config::system_account_name, N(setram), mvo()("max_ram_size", 12ll*1024 * 1024 * 1024)) );
      BOOST_REQUIRE_EQUAL( error("missing authority of eosio"),
                           push_action(name_b, N(setram), mvo()("max_ram_size", 16ll*1024 * 1024 * 1024)) );
      BOOST_REQUIRE_EQUAL( success(),
                           push_action(config::system_account_name, N(setram), mvo()("max_ram_size", 16ll*1024 * 1024 * 1024)) );

      BOOST_REQUIRE_EQUAL( success(), sellram(name_b, bought_bytes_b ) );
      BOOST_REQUIRE( core_sym::from_string("900.0000") < get_balance(name_b) );
      BOOST_REQUIRE( core_sym::from_string("950.0000") > get_balance(name_b) );
   }

} FC_LOG_AND_RETHROW()

// BOOST_FIXTURE_TEST_CASE( ram_inflation, eosio_system_tester ) try {

//    const uint64_t init_max_ram_size = 64ll*1024 * 1024 * 1024;

//    BOOST_REQUIRE_EQUAL( init_max_ram_size, get_global_state()["max_ram_size"].as_uint64() );
//    produce_blocks(20);
//    BOOST_REQUIRE_EQUAL( init_max_ram_size, get_global_state()["max_ram_size"].as_uint64() );
//    transfer( config::system_account_name, "alice1111111", core_sym::from_string("1000.0000"), config::system_account_name );
//    BOOST_REQUIRE_EQUAL( success(), buyram( "alice1111111", "alice1111111", core_sym::from_string("100.0000") ) );
//    produce_blocks(3);
//    BOOST_REQUIRE_EQUAL( init_max_ram_size, get_global_state()["max_ram_size"].as_uint64() );
//    uint16_t rate = 1000;
//    BOOST_REQUIRE_EQUAL( success(), push_action( config::system_account_name, N(setramrate), mvo()("bytes_per_block", rate) ) );
//    BOOST_REQUIRE_EQUAL( rate, get_global_state2()["new_ram_per_block"].as<uint16_t>() );
//    // last time update_ram_supply called is in buyram, num of blocks since then to
//    // the block that includes the setramrate action is 1 + 3 = 4.
//    // However, those 4 blocks were accumulating at a rate of 0, so the max_ram_size should not have changed.
//    BOOST_REQUIRE_EQUAL( init_max_ram_size, get_global_state()["max_ram_size"].as_uint64() );
//    // But with additional blocks, it should start accumulating at the new rate.
//    uint64_t cur_ram_size = get_global_state()["max_ram_size"].as_uint64();
//    produce_blocks(10);
//    BOOST_REQUIRE_EQUAL( success(), buyram( "alice1111111", "alice1111111", core_sym::from_string("100.0000") ) );
//    BOOST_REQUIRE_EQUAL( cur_ram_size + 11 * rate, get_global_state()["max_ram_size"].as_uint64() );
//    cur_ram_size = get_global_state()["max_ram_size"].as_uint64();
//    produce_blocks(5);
//    BOOST_REQUIRE_EQUAL( cur_ram_size, get_global_state()["max_ram_size"].as_uint64() );
//    BOOST_REQUIRE_EQUAL( success(), sellram( "alice1111111", 100 ) );
//    BOOST_REQUIRE_EQUAL( cur_ram_size + 6 * rate, get_global_state()["max_ram_size"].as_uint64() );
//    cur_ram_size = get_global_state()["max_ram_size"].as_uint64();
//    produce_blocks();
//    BOOST_REQUIRE_EQUAL( success(), buyrambytes( "alice1111111", "alice1111111", 100 ) );
//    BOOST_REQUIRE_EQUAL( cur_ram_size + 2 * rate, get_global_state()["max_ram_size"].as_uint64() );

//    BOOST_REQUIRE_EQUAL( error("missing authority of eosio"),
//                         push_action( "alice1111111", N(setramrate), mvo()("bytes_per_block", rate) ) );

//    cur_ram_size = get_global_state()["max_ram_size"].as_uint64();
//    produce_blocks(10);
//    uint16_t old_rate = rate;
//    rate = 5000;
//    BOOST_REQUIRE_EQUAL( success(), push_action( config::system_account_name, N(setramrate), mvo()("bytes_per_block", rate) ) );
//    BOOST_REQUIRE_EQUAL( cur_ram_size + 11 * old_rate, get_global_state()["max_ram_size"].as_uint64() );
//    produce_blocks(5);
//    BOOST_REQUIRE_EQUAL( success(), buyrambytes( "alice1111111", "alice1111111", 100 ) );
//    BOOST_REQUIRE_EQUAL( cur_ram_size + 11 * old_rate + 6 * rate, get_global_state()["max_ram_size"].as_uint64() );

// } FC_LOG_AND_RETHROW()

// BOOST_FIXTURE_TEST_CASE( eosioram_ramusage, eosio_system_tester ) try {
//    BOOST_REQUIRE_EQUAL( core_sym::from_string("0.0000"), get_balance( "alice1111111" ) );
//    transfer( "eosio", "alice1111111", core_sym::from_string("1000.0000"), "eosio" );
//    BOOST_REQUIRE_EQUAL( success(), stake( "eosio", "alice1111111", core_sym::from_string("200.0000"), core_sym::from_string("100.0000") ) );

//    const asset initial_ram_balance = get_balance(N(eosio.ram));
//    const asset initial_ramfee_balance = get_balance(N(eosio.ramfee));
//    BOOST_REQUIRE_EQUAL( success(), buyram( "alice1111111", "alice1111111", core_sym::from_string("1000.0000") ) );

//    BOOST_REQUIRE_EQUAL( false, get_row_by_account( N(eosio.token), N(alice1111111), N(accounts), symbol{CORE_SYM}.to_symbol_code() ).empty() );

//    //remove row
//    base_tester::push_action( N(eosio.token), N(close), N(alice1111111), mvo()
//                              ( "owner", "alice1111111" )
//                              ( "symbol", symbol{CORE_SYM} )
//    );
//    BOOST_REQUIRE_EQUAL( true, get_row_by_account( N(eosio.token), N(alice1111111), N(accounts), symbol{CORE_SYM}.to_symbol_code() ).empty() );

//    auto rlm = control->get_resource_limits_manager();
//    auto eosioram_ram_usage = rlm.get_account_ram_usage(N(eosio.ram));
//    auto alice_ram_usage = rlm.get_account_ram_usage(N(alice1111111));

//    BOOST_REQUIRE_EQUAL( success(), sellram( "alice1111111", 2048 ) );

//    //make sure that ram was billed to alice, not to eosio.ram
//    BOOST_REQUIRE_EQUAL( true, alice_ram_usage < rlm.get_account_ram_usage(N(alice1111111)) );
//    BOOST_REQUIRE_EQUAL( eosioram_ram_usage, rlm.get_account_ram_usage(N(eosio.ram)) );

// } FC_LOG_AND_RETHROW()

// BOOST_FIXTURE_TEST_CASE( ram_gift, eosio_system_tester ) try {
//    active_and_vote_producers();

//    auto rlm = control->get_resource_limits_manager();
//    int64_t ram_bytes_orig, net_weight, cpu_weight;
//    rlm.get_account_limits( N(alice1111111), ram_bytes_orig, net_weight, cpu_weight );

//    /*
//     * It seems impossible to write this test, because buyrambytes action doesn't give you exact amount of bytes requested
//     *
//    //check that it's possible to create account bying required_bytes(2724) + userres table(112) + userres row(160) - ram_gift_bytes(1400)
//    create_account_with_resources( N(abcdefghklmn), N(alice1111111), 2724 + 112 + 160 - 1400 );

//    //check that one byte less is not enough
//    BOOST_REQUIRE_THROW( create_account_with_resources( N(abcdefghklmn), N(alice1111111), 2724 + 112 + 160 - 1400 - 1 ),
//                         ram_usage_exceeded );
//    */

//    //check that stake/unstake keeps the gift
//    transfer( "eosio", "alice1111111", core_sym::from_string("1000.0000"), "eosio" );
//    BOOST_REQUIRE_EQUAL( success(), stake( "eosio", "alice1111111", core_sym::from_string("200.0000"), core_sym::from_string("100.0000") ) );
//    int64_t ram_bytes_after_stake;
//    rlm.get_account_limits( N(alice1111111), ram_bytes_after_stake, net_weight, cpu_weight );
//    BOOST_REQUIRE_EQUAL( ram_bytes_orig, ram_bytes_after_stake );

//    BOOST_REQUIRE_EQUAL( success(), unstake( "eosio", "alice1111111", core_sym::from_string("20.0000"), core_sym::from_string("10.0000") ) );
//    int64_t ram_bytes_after_unstake;
//    rlm.get_account_limits( N(alice1111111), ram_bytes_after_unstake, net_weight, cpu_weight );
//    BOOST_REQUIRE_EQUAL( ram_bytes_orig, ram_bytes_after_unstake );

//    uint64_t ram_gift = 1400;

//    int64_t ram_bytes;
//    BOOST_REQUIRE_EQUAL( success(), buyram( "alice1111111", "alice1111111", core_sym::from_string("1000.0000") ) );
//    rlm.get_account_limits( N(alice1111111), ram_bytes, net_weight, cpu_weight );
//    auto userres = get_total_stake( N(alice1111111) );
//    BOOST_REQUIRE_EQUAL( userres["ram_bytes"].as_uint64() + ram_gift, ram_bytes );

//    BOOST_REQUIRE_EQUAL( success(), sellram( "alice1111111", 1024 ) );
//    rlm.get_account_limits( N(alice1111111), ram_bytes, net_weight, cpu_weight );
//    userres = get_total_stake( N(alice1111111) );
//    BOOST_REQUIRE_EQUAL( userres["ram_bytes"].as_uint64() + ram_gift, ram_bytes );

// } FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( setabi_bios, TESTER ) try {
   abi_serializer abi_ser(fc::json::from_string( (const char*)contracts::system_abi().data()).template as<abi_def>(), abi_serializer_max_time);
   set_code( config::system_account_name, contracts::bios_wasm() );
   set_abi( config::system_account_name, contracts::bios_abi().data() );
   create_account(N(eosio.token));
   set_abi( N(eosio.token), contracts::token_abi().data() );
   {
      auto res = get_row_by_account( config::system_account_name, config::system_account_name, N(abihash), N(eosio.token) );
      _abi_hash abi_hash;
      auto abi_hash_var = abi_ser.binary_to_variant( "abi_hash", res, abi_serializer_max_time );
      abi_serializer::from_variant( abi_hash_var, abi_hash, get_resolver(), abi_serializer_max_time);
      auto abi = fc::raw::pack(fc::json::from_string( (const char*)contracts::token_abi().data()).template as<abi_def>());
      auto result = fc::sha256::hash( (const char*)abi.data(), abi.size() );

      BOOST_REQUIRE( abi_hash.hash == result );
   }

   set_abi( N(eosio.token), contracts::system_abi().data() );
   {
      auto res = get_row_by_account( config::system_account_name, config::system_account_name, N(abihash), N(eosio.token) );
      _abi_hash abi_hash;
      auto abi_hash_var = abi_ser.binary_to_variant( "abi_hash", res, abi_serializer_max_time );
      abi_serializer::from_variant( abi_hash_var, abi_hash, get_resolver(), abi_serializer_max_time);
      auto abi = fc::raw::pack(fc::json::from_string( (const char*)contracts::system_abi().data()).template as<abi_def>());
      auto result = fc::sha256::hash( (const char*)abi.data(), abi.size() );

      BOOST_REQUIRE( abi_hash.hash == result );
   }
} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( setabi, eosio_system_tester ) try {
   set_abi( N(eosio.token), contracts::token_abi().data() );
   {
      auto res = get_row_by_account( config::system_account_name, config::system_account_name, N(abihash), N(eosio.token) );
      _abi_hash abi_hash;
      auto abi_hash_var = abi_ser.binary_to_variant( "abi_hash", res, abi_serializer_max_time );
      abi_serializer::from_variant( abi_hash_var, abi_hash, get_resolver(), abi_serializer_max_time);
      auto abi = fc::raw::pack(fc::json::from_string( (const char*)contracts::token_abi().data()).template as<abi_def>());
      auto result = fc::sha256::hash( (const char*)abi.data(), abi.size() );

      BOOST_REQUIRE( abi_hash.hash == result );
   }

   set_abi( N(eosio.token), contracts::system_abi().data() );
   {
      auto res = get_row_by_account( config::system_account_name, config::system_account_name, N(abihash), N(eosio.token) );
      _abi_hash abi_hash;
      auto abi_hash_var = abi_ser.binary_to_variant( "abi_hash", res, abi_serializer_max_time );
      abi_serializer::from_variant( abi_hash_var, abi_hash, get_resolver(), abi_serializer_max_time);
      auto abi = fc::raw::pack(fc::json::from_string( (const char*)contracts::system_abi().data()).template as<abi_def>());
      auto result = fc::sha256::hash( (const char*)abi.data(), abi.size() );

      BOOST_REQUIRE( abi_hash.hash == result );
   }
} FC_LOG_AND_RETHROW()

BOOST_AUTO_TEST_SUITE_END()
