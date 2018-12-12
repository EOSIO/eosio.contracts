add_contract(token.registry token.registry ${CMAKE_CURRENT_SOURCE_DIR}/src/token.registry.cpp)

target_compile_options(token.registry.wasm PUBLIC -R${CMAKE_CURRENT_SOURCE_DIR}/resources)

target_include_directories(token.registry.wasm
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/../token.registry/include
   ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(token.registry.wasm
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
