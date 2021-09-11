echo "COMPILING"
g++ -std=c++17 -I./DSP ./testbench.cpp -o build/testbenchOut
echo "TESTING"
./build/testbenchOut
echo "PLOTTING"
python plotting.py test2.txt
echo "DONE"