add_contract(eosio.amend eosio.amend ${CMAKE_CURRENT_SOURCE_DIR}/src/eosio.amend.cpp) #NOTE: this path needs to change

target_compile_options(eosio.amend.wasm PUBLIC -R${CMAKE_CURRENT_SOURCE_DIR}/resources)
target_compile_options(eosio.amend.wasm PUBLIC -Wunknown-pragmas)
target_include_directories(eosio.amend.wasm
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include
   ${CMAKE_CURRENT_SOURCE_DIR}/../eosio.trail/include)

# TODO: might need to include path to trail contract

set_target_properties(eosio.amend.wasm
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
