#include "main.h"

using namespace std;

//Variables which GUI outputs to generate the final plot.
int maxVolt;
int methodvar=22;
char png_name[]="datpic.png";
bool inf = false;
double errtol;



int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    lineWidget w;
    w.show();

    a.exec();

    if (methodvar==0){
        trivialMatrix(png_name,errtol,inf,maxVolt);
        EasyPlotting();
    }
    else{
        return 1;
    }

    return 0;
}
