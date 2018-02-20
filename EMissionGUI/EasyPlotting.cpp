#include <stdint.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>

using namespace std;

int EasyPlotting(){

  ofstream inFile;
  inFile.open("PlottingFile"); //Opening plotting file

  //Setting Stuff
  inFile << "set pm3d\n";
  inFile << "set palette rgb 22,13,-31\n";
  inFile << "set terminal postscript color\n";

  //Setting Output (this can be changed)
  inFile << "set output \"GnuPlates.eps\" \n";

  //Plotting datafile (be sure the datafile is present in the directory)
  inFile << "splot \"datpic.dat\" with lines\n";

  //Closing file
  inFile.close();

  //plotting with gnuplot
  system("gnuplot -p <PlottingFile");
	
  system("evince GnuPlates.eps");

  return 0;
}
