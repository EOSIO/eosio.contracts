add_contract(eosio.saving eosio.wps ${CMAKE_CURRENT_SOURCE_DIR}/src/worker.proposals.cpp) #NOTE: this path needs to change
target_include_directories(eosio.wps.wasm
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include
   ${CMAKE_CURRENT_SOURCE_DIR}/../eosio.trail/include)

# TODO: might need to include path to trail contract

set_target_properties(eosio.wps.wasm
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
