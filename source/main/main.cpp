#include "main.h"

using namespace std;

//Variables which GUI outputs to generate the final plot.
int maxVolt;
int methodvar=0;
char png_name[]="datpic.png";
bool inf = false;
double errtol;
clock_t clock_start, clock_end;
double clock_total;



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    lineWidget w;
    w.show();
    a.exec();


    if (methodvar==0){
        clock_start=clock();
        trivialMatrix(png_name,errtol,inf,maxVolt);
        clock_end=clock();
        clock_total=(double)(clock_end-clock_start)/CLOCKS_PER_SEC;
        cout<<"Time taken: " << clock_total <<endl;
        EasyPlotting();
        EasyQuiver();
    }
    else{
        char fpscmd[100];
        sprintf(fpscmd, "../FPScode/FPS-C/fpstar.out datpic.png 4 4 %d", maxVolt);
        system(fpscmd);
    }

    return 0;
}
