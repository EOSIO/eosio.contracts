add_contract(cyber.system cyber.system ${CMAKE_CURRENT_SOURCE_DIR}/src/cyber.system.cpp)
#add_executable(cyber.system.wasm ${CMAKE_CURRENT_SOURCE_DIR}/src/cyber.system.cpp)
target_include_directories(cyber.system.wasm
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include
   ${CMAKE_CURRENT_SOURCE_DIR}/../cyber.token/include)

set_target_properties(cyber.system.wasm
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

install (TARGETS cyber.system.wasm DESTINATION ${CMAKE_INSTALL_PREFIX}/cyber.system/)
install (FILES ${CMAKE_CURRENT_BINARY_DIR}/cyber.system.abi DESTINATION ${CMAKE_INSTALL_PREFIX}/cyber.system/)
