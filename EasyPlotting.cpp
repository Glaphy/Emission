#include <stdint.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>

using namespace std;

int main(){

  ofstream inFile;
  inFile.open("PlottingFile");
  inFile << "set pm3d\n";
  inFile << "set palette rgb 22,13,-31\n";
  inFile << "set terminal postscript color\n";
  inFile << "set output \"GnuPlates.eps\" \n";
  inFile << "splot \"Plates.dat\" with lines\n";
  inFile.close();
  system("gnuplot -p <PlottingFile");

  return 0;
}
