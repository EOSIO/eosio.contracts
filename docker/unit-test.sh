#!/bin/bash
set -e # exit on failure of any "simple" command (excludes &&, ||, or | chains)
cd /eosio.contracts/build/tests
ctest -j8 --output-on-failure