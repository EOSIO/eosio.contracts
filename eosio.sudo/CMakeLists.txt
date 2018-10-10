add_contract(sudo eosio.sudo ${CMAKE_CURRENT_SOURCE_DIR}/src/eosio.sudo.cpp)
target_include_directories(eosio.sudo.wasm
   PUBLIC 
   ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(eosio.sudo.wasm
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
