#include "include/includes.h"
using namespace std;

int main(void)
{
    d_vec Something = {1.0,2.0,0.0,2.0,5.0,0.0,1.0,3.0,2.0};
    int interindx = 64;
    d_vec interpSomething = Interpolate(Something,interindx);
    cout << interpSomething.size() << endl;
    //plotting
        {
            ofstream myFile;
            myFile.open("buffer.txt");
            // for (int i = 0; i < Something.size(); i++)
            // {
            //     myFile << i << "," << Something[i] << endl;
            // }

            for (int i = 0; i < interpSomething.size(); i++)
            {
                float floaty = ((float)i/(float)interindx);
                myFile << floaty << "," << interpSomething[i] << ",";
                if(ceil(floaty) == floor(floaty)){
                    myFile << Something[(int)floaty];
                }else{
                    myFile << "-1";
                }
                myFile << endl;
            }
            myFile.close();
            string mycmd = "python plotting.py buffer.txt"; //+ to_string((int)start/WINDOW);
            system(mycmd.c_str());
        }
}
    

