#include "main.h"

using namespace std;

//Variables which GUI outputs to generate the final plot.
int maxVolt;
char png_name[]="datpic.png";
bool inf = false;
double errtol;



int main(int argc, char *argv[])
{



    QApplication a(argc, argv);
    lineWidget w;
    w.show();

    a.exec();

    trivialMatrix(png_name,errtol,inf,maxVolt);

    EasyPlotting();

    return 0;
}
