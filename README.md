# rentbw modeling tool

![](./utilization.png)

mkdir build

cd build

cmake -DBUILD_TESTS=true ..

make -j

from the project folder execute:

./run_and_plot.sh model_config.json rentbw_input.csv

