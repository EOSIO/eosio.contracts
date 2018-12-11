add_contract(telos.free telos.free ${CMAKE_CURRENT_SOURCE_DIR}/src/telos.free.cpp)

target_compile_options(telos.free.wasm PUBLIC -R${CMAKE_CURRENT_SOURCE_DIR}/resources)
target_include_directories(telos.free.wasm
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(telos.free.wasm
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
