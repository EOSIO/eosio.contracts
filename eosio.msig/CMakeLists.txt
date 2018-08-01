configure_file("${CMAKE_CURRENT_SOURCE_DIR}/abi/eosio.msig.abi" "${CMAKE_CURRENT_BINARY_DIR}" COPYONLY)

add_executable(eosio.msig.wasm ${CMAKE_CURRENT_SOURCE_DIR}/src/eosio.msig.cpp)
target_include_directories(eosio.msig.wasm
   PUBLIC 
   ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(eosio.msig.wasm
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

#install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION ${WASM_ROOT}/eosio.wasmsdk/include)
