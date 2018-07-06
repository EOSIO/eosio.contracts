add_executable(eosio.msig.wasm ${CMAKE_CURRENT_SOURCE_DIR}/src/eosio.msig.cpp)
target_include_directories(eosio.msig.wasm
   PUBLIC 
   ${CMAKE_CURRENT_SOURCE_DIR}/include)
#install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION ${WASM_ROOT}/eosio.wasmsdk/include)
install(TARGETS eosio.msig.wasm
   RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/abi/eosio.msig.abi DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)
