add_contract_with_abi(cyber.token abi/cyber.token.abi ${CMAKE_CURRENT_SOURCE_DIR}/src/cyber.token.cpp)
target_include_directories(cyber.token.wasm
   PUBLIC 
   ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(cyber.token.wasm
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
