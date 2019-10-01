cmake_minimum_required(VERSION 3.10)

project(integration-tests)

set(EOSIO_WASM_OLD_BEHAVIOR "off")
find_package(eosio.cdt)

function(add_test TARGET SRC)
   add_executable(${TARGET} ${SRC})
   target_link_libraries(${TARGET} -ftester -stack-size=65536)
   target_compile_options(${TARGET} PUBLIC -ftester -Os)
   target_include_directories(${TARGET}
      PUBLIC
      ${CMAKE_CURRENT_SOURCE_DIR}/../contracts/eosio.bios/include
      ${CMAKE_CURRENT_SOURCE_DIR}/../contracts/eosio.msig/include
      ${CMAKE_CURRENT_SOURCE_DIR}/../contracts/eosio.system/include
      ${CMAKE_CURRENT_SOURCE_DIR}/../contracts/eosio.token/include
      ${CMAKE_CURRENT_SOURCE_DIR}/../contracts/eosio.wrap/include
      )
   set_target_properties(${TARGET}
     PROPERTIES
     RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
endfunction()

add_test(eosio.msig-tests eosio.msig-tests.cpp)
add_test(eosio.token-tests eosio.token-tests.cpp)
