#!/bin/sh

if [ $# -ne 3 ]; then
    echo "Usage: $0 <json model config file> <csv rentbw input file> <model output file>"
    echo "Example: $0 examples/model_config.json examples/rentbw_input.csv model_tests.csv"
    exit 1
fi

../build/tests/unit_test -t eosio_system_rentbw_modeling_tests -- $1 $2 $3

if [ $? -eq 0 ]; then
	command -v gnuplot &>/dev/null
	if [ $? -eq 0 ]; then
        echo "
          set datafile separator ';'
          set style line 1 lt 1 lc rgb '#A00000' lw 2 pt 7 ps 1
          set style line 2 lt 1 lc rgb '#00A000' lw 2 pt 11 ps 1
  
          set style line 81 lt 0 lc rgb '#808080' lw 0.5

          # Draw the grid lines for both the major and minor tics
          set grid xtics
          set grid ytics
          set grid mxtics
          set grid mytics

          # Put the grid behind anything drawn and use the linestyle 81
          set grid back ls 81

          set key autotitle columnhead
          plot \"$3\" using 1:24 w lp ls 1, '' using 1:25 w lp ls 2
	    " | gnuplot --persist
    else
        echo "INFO: You can install gnuplot to see the result graph"
    fi
fi
