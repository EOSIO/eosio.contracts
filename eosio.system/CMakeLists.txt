add_executable(eosio.system.wasm ${CMAKE_CURRENT_SOURCE_DIR}/src/eosio.system.cpp)
target_include_directories(eosio.system.wasm
   PUBLIC 
   ${CMAKE_SOURCE_DIR}/include)

set_target_properties(eosio.system.wasm
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/eosio.system")

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/abi/eosio.system.abi" "${CMAKE_CURRENT_SOURCE_DIR}/bin/eosio.system" COPYONLY)

#install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION ${WASM_ROOT}/eosio.wasmsdk/include)
