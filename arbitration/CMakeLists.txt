add_contract(arbitration arbitration ${CMAKE_CURRENT_SOURCE_DIR}/src/arbitration.cpp)
target_include_directories(arbitration.wasm
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(arbitration.wasm
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")