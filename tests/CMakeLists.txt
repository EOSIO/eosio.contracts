set(BUILD_CYBERWAY_CHAINDB_MONGO TRUE CACHE BOOL "Build chaindb based on mongodb")

cmake_minimum_required( VERSION 3.5 )

list(APPEND CMAKE_MODULE_PATH ${EOSIO_ROOT}/lib/cmake)
include(EosioTester)

### check the version of EOSIO
string(FIND "${EOSIO_VERSION}" "${EOSIO_DEPENDENCY}" output)
if (NOT "${output}" EQUAL 0)
   message(FATAL_ERROR "Incorrect EOSIO version, please use version ${EOSIO_DEPENDENCY}.x")
endif()


enable_testing()

configure_file(${CMAKE_SOURCE_DIR}/contracts.hpp.in ${CMAKE_BINARY_DIR}/contracts.hpp)

include_directories(${CMAKE_BINARY_DIR})

file(GLOB UNIT_TESTS "*.cpp" "*.hpp")

add_eosio_test( unit_test ${UNIT_TESTS} )
