cmake_minimum_required(VERSION 3.5)
project(eosio_token VERSION 1.0.0)

# if no wasm root is given use default path
if(WASM_ROOT STREQUAL "" OR NOT WASM_ROOT)
   set(WASM_ROOT ${CMAKE_INSTALL_PREFIX})
endif()

list(APPEND CMAKE_MODULE_PATH ${WASM_ROOT}/lib/cmake)
include(EosioWasmToolchain)

add_executable(eosio.system 
   ${CMAKE_SOURCE_DIR}/src/eosio.system.cpp
   ${CMAKE_SOURCE_DIR}/src/producer_pay.cpp
   ${CMAKE_SOURCE_DIR}/src/delegate_bandwidth.cpp
   ${CMAKE_SOURCE_DIR}/src/voting.cpp
   ${CMAKE_SOURCE_DIR}/src/exchange_state.cpp)

target_include_directories(eosio.system 
   PUBLIC 
   ${STANDARD_INCLUDES}
   ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(eosio.system PRIVATE ${STANDARD_LIBS})
#install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION ${WASM_ROOT}/eosiosdk/include)
