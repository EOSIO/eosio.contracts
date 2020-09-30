# rentbw modeling tool

![](https://user-images.githubusercontent.com/61709855/94286123-91e69480-ff22-11ea-94d4-59ae2daa2073.png)

mkdir build

cd build

cmake -DBUILD_TESTS=true ..

make -j

from the project folder execute:

./run_and_plot.sh model_config.json rentbw_input.csv

