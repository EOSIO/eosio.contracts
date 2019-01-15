add_contract_with_abi(cyber.wrap abi/cyber.wrap.abi ${CMAKE_CURRENT_SOURCE_DIR}/src/cyber.wrap.cpp)
target_include_directories(cyber.wrap.wasm
   PUBLIC 
   ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(cyber.wrap.wasm
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
