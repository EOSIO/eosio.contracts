add_executable(eosio.system.wasm ${CMAKE_CURRENT_SOURCE_DIR}/src/eosio.system.cpp)
target_include_directories(eosio.system.wasm
   PUBLIC 
   ${CMAKE_SOURCE_DIR}/include)
#install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION ${WASM_ROOT}/eosio.wasmsdk/include)
install(TARGETS eosio.system.wasm
   RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/abi/eosio.system.abi DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)
