if [ "$1" == "-t" ];
then
   echo "Using the testbench script"
   g++ -std=c++17 -I./DSP ./tests/testbench.cpp -o build/testbenchOut
else
   echo "Using the main script"
   g++ -std=c++17 -I./DSP ./main.cpp -o build/mainOut
fi