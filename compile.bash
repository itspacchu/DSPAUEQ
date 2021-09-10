# how to cmake?
if [ "$1" == "-t" ]; then
        echo "Using the testbench script"
        g++ -std=c++17 -I./DSP ./testbench.cpp -o build/testbenchOut
else
        g++ -std=c++17 -I./DSP ./main.cpp -o build/mainOut
fi
# im just a simpleton