#include <stdint.h>
#include <fstream>
# include <iostream>

using namespace std;

int main (){

  ofstream inFile;
  inFile.open("QuiverFile");//Opening Plotting File

  //Setting stuff
  inFile << "reset\n";
  inFile << "set terminal postscript color" << endl;

  //Setting Output (this can be changed)
  inFile << "set output \"QuivGrad.eps\" \n";

  //Plotting Datafile (be sure the datafile is present in the directory)
  inFile << "plot \"grad.dat\" using 1:2:3:4 with vectors nofilled head lw 1\n";

  //Closing file
  inFile.close();

  //plotting with gnuplot
  system("gnuplot -p <QuiverFile");

  return 0;
}
