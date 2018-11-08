add_contract(eosio.arbitration eosio.arbitration ${CMAKE_CURRENT_SOURCE_DIR}/src/eosio.arbitration.cpp)
target_include_directories(eosio.arbitration.wasm
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(eosio.arbitration.wasm
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")