add_executable(eosio.sudo.wasm ${CMAKE_CURRENT_SOURCE_DIR}/src/eosio.sudo.cpp)
target_include_directories(eosio.sudo.wasm
   PUBLIC 
   ${CMAKE_CURRENT_SOURCE_DIR}/include)
#install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION ${WASM_ROOT}/eosio.wasmsdk/include)
install(TARGETS eosio.sudo.wasm
   RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/abi/eosio.sudo.abi DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)
