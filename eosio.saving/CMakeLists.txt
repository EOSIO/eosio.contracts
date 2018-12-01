add_contract(eosio.saving eosio.saving ${CMAKE_CURRENT_SOURCE_DIR}/src/worker.proposals.cpp) #NOTE: this path needs to change
target_include_directories(eosio.saving.wasm
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include
   ${CMAKE_CURRENT_SOURCE_DIR}/../eosio.trail/include)

# TODO: might need to include path to trail contract

set_target_properties(eosio.saving.wasm
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
