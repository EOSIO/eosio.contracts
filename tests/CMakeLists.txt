cmake_minimum_required( VERSION 3.5 )
project( EOSIO_CONTRACTS_TESTS )
set( VERSION_MAJOR 1 )
set( VERSION_MINOR 0 )
set( VERSION_PATCH 0 )

enable_testing()

find_package( Gperftools QUIET )
if( GPERFTOOLS_FOUND )
    message( STATUS "Found gperftools; compiling tests with TCMalloc")
    list( APPEND PLATFORM_SPECIFIC_LIBS tcmalloc )
endif()

find_package(LLVM 4.0 REQUIRED CONFIG)

link_directories(${LLVM_LIBRARY_DIR})

set( CMAKE_CXX_STANDARD 14 )
set( CMAKE_CXX_EXTENSIONS ON )
set( CXX_STANDARD_REQUIRED ON )

if ( APPLE )
   set( CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wall -Wno-deprecated-declarations" )
else ( APPLE )
   set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
   set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++ -static-libgcc")
endif ( APPLE )

set( Boost_USE_STATIC_LIBS ON CACHE STRING "ON or OFF" )
configure_file(${CMAKE_SOURCE_DIR}/contracts.hpp.in ${CMAKE_SOURCE_DIR}/contracts.hpp)
find_package(Boost 1.67 REQUIRED COMPONENTS 
	date_time 
	filesystem 
	system 
	chrono 
	iostreams 
	date_time 
	unit_test_framework)

file(GLOB UNIT_TESTS "*.cpp")

find_library(libtester eosio_testing ${EOSIO_INSTALL_PREFIX}/lib)
find_library(libchain eosio_chain ${EOSIO_INSTALL_PREFIX}/lib)
if ( "${CMAKE_BUILD_TYPE}" EQUAL "Debug" )
   find_library(libfc fc_debug ${EOSIO_INSTALL_PREFIX}/lib)
else()
   find_library(libfc fc ${EOSIO_INSTALL_PREFIX}/lib)
endif()
find_library(libbinaryen binaryen ${EOSIO_INSTALL_PREFIX}/lib)
find_library(libwasm WASM ${EOSIO_INSTALL_PREFIX}/lib)
find_library(libwast WAST ${EOSIO_INSTALL_PREFIX}/lib)
find_library(libir IR     ${EOSIO_INSTALL_PREFIX}/lib)
find_library(libplatform Platform ${EOSIO_INSTALL_PREFIX}/lib)
find_library(liblogging Logging ${EOSIO_INSTALL_PREFIX}/lib)
find_library(libruntime Runtime ${EOSIO_INSTALL_PREFIX}/lib)
find_library(libsoftfloat softfloat ${EOSIO_INSTALL_PREFIX}/lib)
find_library(liboscrypto crypto ${OPENSSL_INSTALL_PREFIX}/lib)
find_library(libosssl ssl ${OPENSSL_INSTALL_PREFIX}/lib)
find_library(libchainbase chainbase ${EOSIO_INSTALL_PREFIX}/lib)
find_library(libbuiltins builtins ${EOSIO_INSTALL_PREFIX}/lib)
find_library(libsecp256k1 secp256k1 ${SECP256K1_INSTALL_LIB})

add_executable( unit_test ${UNIT_TESTS} )
target_link_libraries( unit_test 
    ${LLVM} 
    ${libtester}    
    ${libchain} 
    ${libfc} 
    ${libbinaryen} 
    ${libwast} 
    ${libwasm} 
    ${libruntime} 
    ${libplatform} 
    ${libir} 
    ${libsoftfloat} 
    ${liboscrypto} 
    ${libosssl} 
    ${liblogging} 
    ${libchainbase} 
    ${libbuiltins} 
    ${libsecp256k1} 

    LLVMX86Disassembler
    LLVMX86AsmParser
    LLVMX86AsmPrinter
    LLVMX86CodeGen

    LLVMSelectionDAG

    LLVMDebugInfoDWARF
    LLVMAsmPrinter
    LLVMMCParser
    LLVMX86Info

    LLVMOrcJIT
    LLVMExecutionEngine

    LLVMCodeGen
    LLVMScalarOpts
    LLVMTransformUtils

    LLVMipo
    LLVMAnalysis
    LLVMTarget
    LLVMMC
    LLVMCore
    LLVMSupport
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_CHRONO_LIBRARY}
    ${Boost_IOSTREAMS_LIBRARY}
    ${Boost_DATE_TIME_LIBRARY}
    ${PLATFORM_SPECIFIC_LIBS}
   )

target_include_directories( unit_test PUBLIC
                            ${Boost_INCLUDE_DIRS}
                            ${OPENSSL_INSTALL_PREFIX}/include
                            ${EOSIO_INSTALL_PREFIX}
                            ${EOSIO_INSTALL_PREFIX}/include
                            ${EOSIO_INSTALL_PREFIX}/include/eosio/wasm-jit/Include
                            ${EOSIO_INSTALL_PREFIX}/include/eosio/softfloat/include
                            ${CMAKE_CURRENT_BINARY_DIR}/include )

#Manually run unit_test for all supported runtimes
#To run unit_test with all log from blockchain displayed, put --verbose after --, i.e. unit_test -- --verbose
add_test(NAME unit_test_binaryen COMMAND unit_test
 --report_level=detailed --color_output -- --binaryen)
add_test(NAME unit_test_wavm COMMAND unit_test
 --report_level=detailed --color_output --catch_system_errors=no -- --wavm)

if(ENABLE_COVERAGE_TESTING)

  set(Coverage_NAME ${PROJECT_NAME}_ut_coverage)

  if(NOT LCOV_PATH)
    message(FATAL_ERROR "lcov not found! Aborting...")
  endif() # NOT LCOV_PATH

  if(NOT LLVMCOV_PATH)
    message(FATAL_ERROR "llvm-cov not found! Aborting...")
  endif() # NOT LCOV_PATH

  if(NOT GENHTML_PATH)
    message(FATAL_ERROR "genhtml not found! Aborting...")
  endif() # NOT GENHTML_PATH

  # no spaces allowed within tests list
  set(ctest_tests 'unit_test_binaryen|unit_test_wavm')
  set(ctest_exclude_tests '')

  # Setup target
  add_custom_target(${Coverage_NAME}

    # Cleanup lcov
    COMMAND ${LCOV_PATH} --directory . --zerocounters

    # Run tests
    COMMAND ./tools/ctestwrapper.sh -R ${ctest_tests} -E ${ctest_exclude_tests}

    COMMAND ${LCOV_PATH} --directory . --capture --gcov-tool ./tools/llvm-gcov.sh --output-file ${Coverage_NAME}.info

    COMMAND ${LCOV_PATH} -remove ${Coverage_NAME}.info '*/boost/*' '/usr/lib/*' '/usr/include/*' '*/externals/*' '*/fc/*' '*/wasm-jit/*' --output-file ${Coverage_NAME}_filtered.info

    COMMAND ${GENHTML_PATH} -o ${Coverage_NAME} ${PROJECT_BINARY_DIR}/${Coverage_NAME}_filtered.info

    COMMAND if [ "$CI" != "true" ]\; then ${CMAKE_COMMAND} -E remove ${Coverage_NAME}.base ${Coverage_NAME}.info ${Coverage_NAME}_filtered.info ${Coverage_NAME}.total ${PROJECT_BINARY_DIR}/${Coverage_NAME}.info.cleaned ${PROJECT_BINARY_DIR}/${Coverage_NAME}_filtered.info.cleaned\; fi

    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    COMMENT "Resetting code coverage counters to zero. Processing code coverage counters and generating report. Report published in ./${Coverage_NAME}"
    )

  # Show info where to find the report
  add_custom_command(TARGET ${Coverage_NAME} POST_BUILD
    COMMAND ;
    COMMENT "Open ./${Coverage_NAME}/index.html in your browser to view the coverage report."
    )
endif()
