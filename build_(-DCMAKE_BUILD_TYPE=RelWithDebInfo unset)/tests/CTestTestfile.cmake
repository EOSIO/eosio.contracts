# CMake generated Testfile for 
# Source directory: /Users/jinjung.zhao/Work/new-contracts/eosio.contracts/tests
# Build directory: /Users/jinjung.zhao/Work/new-contracts/eosio.contracts/build/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(eosio_msig_unit_test "/Users/jinjung.zhao/Work/new-contracts/eosio.contracts/build/tests/unit_test" "--run_test=eosio_msig_tests" "--report_level=detailed" "--color_output")
set_tests_properties(eosio_msig_unit_test PROPERTIES  _BACKTRACE_TRIPLES "/Users/jinjung.zhao/Work/new-contracts/eosio.contracts/tests/CMakeLists.txt;41;add_test;/Users/jinjung.zhao/Work/new-contracts/eosio.contracts/tests/CMakeLists.txt;0;")
add_test(eosio_system_unit_test "/Users/jinjung.zhao/Work/new-contracts/eosio.contracts/build/tests/unit_test" "--run_test=eosio_system_tests" "--report_level=detailed" "--color_output")
set_tests_properties(eosio_system_unit_test PROPERTIES  _BACKTRACE_TRIPLES "/Users/jinjung.zhao/Work/new-contracts/eosio.contracts/tests/CMakeLists.txt;41;add_test;/Users/jinjung.zhao/Work/new-contracts/eosio.contracts/tests/CMakeLists.txt;0;")
add_test(eosio_token_unit_test "/Users/jinjung.zhao/Work/new-contracts/eosio.contracts/build/tests/unit_test" "--run_test=eosio_token_tests" "--report_level=detailed" "--color_output")
set_tests_properties(eosio_token_unit_test PROPERTIES  _BACKTRACE_TRIPLES "/Users/jinjung.zhao/Work/new-contracts/eosio.contracts/tests/CMakeLists.txt;41;add_test;/Users/jinjung.zhao/Work/new-contracts/eosio.contracts/tests/CMakeLists.txt;0;")
add_test(eosio_wrap_unit_test "/Users/jinjung.zhao/Work/new-contracts/eosio.contracts/build/tests/unit_test" "--run_test=eosio_wrap_tests" "--report_level=detailed" "--color_output")
set_tests_properties(eosio_wrap_unit_test PROPERTIES  _BACKTRACE_TRIPLES "/Users/jinjung.zhao/Work/new-contracts/eosio.contracts/tests/CMakeLists.txt;41;add_test;/Users/jinjung.zhao/Work/new-contracts/eosio.contracts/tests/CMakeLists.txt;0;")
