#include "main.h"

using namespace std;

//Variables which GUI outputs to generate the final plot.
int maxVolt;
int methodvar=0;
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
        cout<<methodvar<<endl;
        EasyPlotting();
    }
    else{
        system("FPS-C/fpstar.out datpic.png 4 4");
    }

    return 0;
}
