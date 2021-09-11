#include <iostream>
#include <fstream>

using namespace std;
int main(void){
    ofstream myFile;
    myFile.open("test2.txt");
    for (int i = 0; i < 100; i++)
    {
        myFile << i << "," << i%2 << "\n";
    }
    myFile.close();
}