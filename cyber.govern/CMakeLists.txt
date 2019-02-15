add_contract_with_abi(cyber.govern abi/cyber.govern.abi ${CMAKE_CURRENT_SOURCE_DIR}/src/cyber.govern.cpp)
target_include_directories(cyber.govern.wasm
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include
   ${CMAKE_CURRENT_SOURCE_DIR}/../cyber.token/include
   ${CMAKE_CURRENT_SOURCE_DIR}/../cyber.stake/include
   ${CMAKE_CURRENT_SOURCE_DIR}/..)

set_target_properties(cyber.govern.wasm
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

install (TARGETS cyber.govern.wasm DESTINATION ${CMAKE_INSTALL_PREFIX}/cyber.govern/)
install (FILES ${CMAKE_CURRENT_BINARY_DIR}/cyber.govern.abi DESTINATION ${CMAKE_INSTALL_PREFIX}/cyber.govern/)
