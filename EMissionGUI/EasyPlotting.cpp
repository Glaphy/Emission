#include <stdint.h>
#include <fstream>
#include <stdlib.h>
#include "main.h"

using namespace std;

int EasyPlotting(){

  ofstream inFile;
  inFile.open("PlottingFile"); //Opening plotting file

  //Setting Stuff
  inFile << "set pm3d\n";
  inFile << "set palette rgb 22,13,-31\n";
  inFile << "set terminal qt 0\n";

  //Setting Output (this can be changed)
  inFile << "set output \"GnuPlates.eps\" \n";

  //Plotting datafile (be sure the datafile is present in the directory)
  inFile << "splot \"Potential.dat\" with lines\n";
  inFile << "pause mouse key\n";
  inFile << "if (MOUSE_KEY != 27) reread\n";


  //Closing file
  inFile.close();

  //plotting with gnuplot
  system("gnuplot -p <PlottingFile");

  return 0;
}
