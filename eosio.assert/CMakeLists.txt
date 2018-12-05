add_contract(eosio.assert eosio.assert ${CMAKE_CURRENT_SOURCE_DIR}/src/eosio.assert.cpp)
target_include_directories(eosio.assert.wasm
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(eosio.assert.wasm
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
