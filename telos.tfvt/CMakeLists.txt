add_contract(telos.tfvt telos.tfvt ${CMAKE_CURRENT_SOURCE_DIR}/src/telos.tfvt.cpp) #NOTE: this path needs to change

target_compile_options(telos.tfvt.wasm PUBLIC -R${CMAKE_CURRENT_SOURCE_DIR}/resources)
target_include_directories(telos.tfvt.wasm
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/../eosio.trail/include
   ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(telos.tfvt.wasm
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
