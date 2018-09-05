add_executable(eosio.system.sys.wasm ${CMAKE_SOURCE_DIR}/eosio.system/src/eosio.system.cpp)
target_include_directories(eosio.system.sys.wasm
   PUBLIC 
   ${CMAKE_SOURCE_DIR}/eosio.system/src
   ${CMAKE_CURRENT_SOURCE_DIR}/include
   ${CMAKE_SOURCE_DIR}/eosio.system/include
   ${CMAKE_SOURCE_DIR}/eosio.token/include)

set_target_properties(eosio.system.sys.wasm
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

add_executable(eosio.token.sys.wasm ${CMAKE_SOURCE_DIR}/eosio.token/src/eosio.token.cpp)
target_include_directories(eosio.token.sys.wasm
   PUBLIC 
   ${CMAKE_CURRENT_SOURCE_DIR}/include
   ${CMAKE_SOURCE_DIR}/eosio.token/include
   ${CMAKE_SOURCE_DIR}/eosio.token/include)

set_target_properties(eosio.token.sys.wasm
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

#install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION ${WASM_ROOT}/eosio.wasmsdk/include)
