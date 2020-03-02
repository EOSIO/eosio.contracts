add_contract(sendinline sendinline ${CMAKE_CURRENT_SOURCE_DIR}/src/sendinline.cpp)
target_include_directories(sendinline PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_target_properties(sendinline PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
