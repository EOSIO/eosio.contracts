cmake_minimum_required(VERSION 3.5)
project(eosio_contracts VERSION 1.3.0)

set(EOSIO_DEPENDENCY "1.2")
set(EOSIO_CDT_DEPENDENCY "1.2")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
   set(TEST_BUILD_TYPE "Debug")
   set(CMAKE_BUILD_TYPE "Release")
else()
   set(TEST_BUILD_TYPE ${CMAKE_BUILD_TYPE})
endif()

if(EOSIO_ROOT STREQUAL "" OR NOT EOSIO_ROOT)
   set(EOSIO_ROOT "/usr/local/eosio")
endif()

if(EOSIO_CDT_ROOT STREQUAL "" OR NOT EOSIO__ROOT)
   set(EOSIO_CDT_ROOT "/usr/local/eosio.cdt")
endif()

list(APPEND CMAKE_MODULE_PATH ${EOSIO_CDT_ROOT}/lib/cmake)
include(EosioWasmToolchain)

### Check the version of wasmsdk
string(FIND "${EOSIO_CDT_VERSION}" "${EOSIO_CDT_DEPENDENCY}" output)

if (NOT "${output}" EQUAL 0)
   message(FATAL_ERROR "Incorrect EOSIO.CDT version, please use version ${EOSIO_CDT_DEPENDENCY}.x")
endif()

include_directories(AFTER ${BOOST_ROOT}/include)
add_subdirectory(eosio.bios)
add_subdirectory(eosio.msig)
add_subdirectory(eosio.sudo)
add_subdirectory(eosio.system)
add_subdirectory(eosio.token)

if (APPLE)
   set(OPENSSL_ROOT "/usr/local/opt/openssl")
elseif (UNIX)
   set(OPENSSL_ROOT "/usr/include/openssl")
endif()
set(SECP256K1_ROOT "/usr/local")

include(UnitTestsExternalProject.txt)
