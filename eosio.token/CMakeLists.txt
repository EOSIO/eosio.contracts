add_executable(eosio.token.wasm ${CMAKE_CURRENT_SOURCE_DIR}/src/eosio.token.cpp)

generate_ricardian_abi( eosio.token ${CMAKE_CURRENT_SOURCE_DIR}/abi ${CMAKE_CURRENT_BINARY_DIR} )

target_include_directories(eosio.token.wasm
   PUBLIC 
   ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(eosio.token.wasm
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

#configure_file("${CMAKE_CURRENT_SOURCE_DIR}/abi/eosio.token.abi" "${CMAKE_CURRENT_BINARY_DIR}" COPYONLY)
#install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION ${WASM_ROOT}/eosio.wasmsdk/include)
