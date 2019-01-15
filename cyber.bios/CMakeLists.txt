add_contract_with_abi(cyber.bios abi/cyber.bios.abi ${CMAKE_CURRENT_SOURCE_DIR}/src/cyber.bios.cpp)
target_include_directories(cyber.bios.wasm
   PUBLIC 
   ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(cyber.bios.wasm
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
