add_contract_with_abi(cyber.domain cyber.domain.abi ${CMAKE_CURRENT_SOURCE_DIR}/cyber.domain.cpp)
target_include_directories(cyber.domain.wasm
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/../eosio.system/include
   ${CMAKE_CURRENT_SOURCE_DIR}/../eosio.token/include)

set_target_properties(cyber.domain.wasm
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

install (TARGETS eosio.system.wasm DESTINATION ${CMAKE_INSTALL_PREFIX}/cyber.domain/)
#install (FILES ${CMAKE_CURRENT_BINARY_DIR}/cyber.domain.abi DESTINATION ${CMAKE_INSTALL_PREFIX}/cyber.domain/)
