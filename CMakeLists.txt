cmake_minimum_required(VERSION 3.5)
project(eosio_contracts VERSION 1.1.0)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
   set(TEST_BUILD_TYPE "Debug")
   set(CMAKE_BUILD_TYPE "Release")
else()
   set(TEST_BUILD_TYPE ${CMAKE_BUILD_TYPE})
endif()

if(EOSIO_ROOT STREQUAL "" OR NOT EOSIO_ROOT)
   set(EOSIO_ROOT "/usr/local/eosio")
endif()
if(EOSIO_WASMSDK_ROOT STREQUAL "" OR NOT EOSIO_WASMSDK_ROOT)
   set(EOSIO_WASMSDK_ROOT "/usr/local")
   set(WASM_ROOT "/usr/local")
endif()

list(APPEND CMAKE_MODULE_PATH ${EOSIO_WASMSDK_ROOT}/lib/cmake)
include(EosioWasmToolchain)

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
