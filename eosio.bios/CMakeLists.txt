add_contract(eosio.bios eosio.bios ${CMAKE_CURRENT_SOURCE_DIR}/src/eosio.bios.cpp)
target_include_directories(eosio.bios.wasm
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(eosio.bios.wasm
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
