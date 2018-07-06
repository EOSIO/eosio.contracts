add_executable(eosio.token.wasm ${CMAKE_CURRENT_SOURCE_DIR}/src/eosio.token.cpp)
target_include_directories(eosio.token.wasm
   PUBLIC 
   ${CMAKE_CURRENT_SOURCE_DIR}/include)
#install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION ${WASM_ROOT}/eosio.wasmsdk/include)
install(TARGETS eosio.token.wasm
   RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/abi/eosio.token.abi DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)
