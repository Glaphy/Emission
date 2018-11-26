#include <stdint.h>
#include <fstream>
# include <iostream>
#include "main.h"

using namespace std;

int EasyQuiver (){

  ofstream inFile;
  inFile.open("QuiverFile");//Opening Plotting File

  //Setting stuff
  inFile << "reset\n";
  inFile << "set terminal qt" << endl;

  //Setting Output (this can be changed)
  inFile << "set output \"QuivGrad.eps\" \n";
  inFile << "set xrange [0:350]\n";
  inFile << "set yrange [0:350]\n";

  inFile << "set title 'Electric Field'\n";

  //Plotting Datafile (be sure the datafile is present in the directory)
  inFile << "plot \"grad.dat\" using 1:2:3:4 with vectors nofilled head lw 1\n";

  //Closing file
  inFile.close();

  //plotting with gnuplot
  system("gnuplot -p <QuiverFile");

  return 0;
}
