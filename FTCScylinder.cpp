#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
using namespace std;


/*
The aim of the following code is to generate a square matrix which represents the potential field
inbetween two charged plates,  with a grounded wire stretched through the middle. The 
2D matrix will be generated using FTCS finite difference scheme. 
*/

int main(){
	
	double dx,dy,r,L,W,V;
	
	std::cout<<"Enter desired step size in x-axis:"<<std::endl;
	std::cin>>dx;
	std::cout<<" "<<std::endl;
	
	std::cout<<"Enter desired step size in y-axis:"<<std::endl;
	std::cin>>dy;
	std::cout<<" "<<std::endl;
	
	std::cout<<"Enter desired radius of wire inbetween:"<<std::endl;
	std::cin>>r;
	std::cout<<" "<<std::endl;
	
	std::cout<<"Enter desired length between charged plates:"<<std::endl;
	std::cin>>L;
	std::cout<<" "<<std::endl;
	
	std::cout<<"Enter desried potential difference between plates:"<<std::endl;
	std::cin>>V;
	std::cout<<" "<<std::endl;
	
	W=L;
	midpnt=round(W/2);
	
	double Potential[L*dx][L*dy];
	
	
	for  (int i=0 ;i<W )
	
	
	
	return 0;
}