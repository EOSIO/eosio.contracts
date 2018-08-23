add_executable(eosio.msig.wasm ${CMAKE_CURRENT_SOURCE_DIR}/src/eosio.msig.cpp)

generate_ricardian_abi( eosio.msig ${CMAKE_CURRENT_SOURCE_DIR}/abi ${CMAKE_CURRENT_BINARY_DIR} )

target_include_directories(eosio.msig.wasm
   PUBLIC 
   ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(eosio.msig.wasm
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

#install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION ${WASM_ROOT}/eosio.wasmsdk/include)
