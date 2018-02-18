#include <stdint.h>
#include <fstream>
# include <iostream>

using namespace std;

int main (){

  ofstream inFile;
  inFile.open("QuiverFile");
  inFile << "reset\n";
  //inFile << "set palette rgb 22,13,-31\n";
  inFile << "set terminal postscript color" << endl;
  inFile << "set output \"QuivGrad.eps\" \n";
  inFile << "plot \"grad.dat\" using 1:2:3:4 with vectors nofilled head lw 1\n";
  inFile.close();
  system("gnuplot -p <QuiverFile");

  return 0;
}
