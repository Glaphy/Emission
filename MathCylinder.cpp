#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include <fstream>
using namespace std;


/*
The aim of the following code is to generate a square matrix which represents the potential field
inbetween two charged plates,  with a grounded wire stretched through the middle. The 
2D matrix will be generated using analytical solution to problem.
*/

// given a Cartesian coordinate, this function generates its potential using analytical solution.
double Potential(double x,double y,double  E0, double R){
	double theta=0, r=0, V=0;
	
	// CONVERT MATRIX COORDINATES INTO POLAR
	theta=atan2(x,y);
	r=sqrt(pow(x,2) + pow(y,2));
	
	//SET GROUND CONDITIONS, THE REST OF THE FIELD FOLLOWS ANALYTICAL SOLUTION
	if (r<R){
		V=0;
	}
	else{
		V=(double)-E0*(r-(pow(R,2)/r))*cos(theta);
	}
	
	return V;
}


int main(){
	
	double dx,dy,RC,L,W,V;
	
	std::cout<<"Enter desired step size in x-axis:"<<std::endl;
	std::cin>>dx;
	std::cout<<" "<<std::endl;
	
	std::cout<<"Enter desired step size in y-axis:"<<std::endl;
	std::cin>>dy;
	std::cout<<" "<<std::endl;
	
	std::cout<<"Enter desired radius of grounded wire inbetween:"<<std::endl;
	std::cin>>RC;
	std::cout<<" "<<std::endl;
	
	std::cout<<"Enter desired length between charged plates:"<<std::endl;
	std::cin>>L;
	std::cout<<" "<<std::endl;
	
	std::cout<<"Enter desried potential difference between plates:"<<std::endl;
	std::cin>>V;
	std::cout<<" "<<std::endl;
	
	W=L;
	double Enull=V/W;
	
	
	// GRID ORIGIN DEFINED HERE
	double midpnt=W/2;
	
	
	// GRID ARRAY DEFINED HERE
	int width=round(L/dx);
	int length=round(L/dy);
	
	double field[length][width];
	
	

	
	//POPULATING ARRAY
	for (int i=0; i<length; i++){
		for (int j=0; j<width;j++){
			double pos[2]={j*dx,i*dy};             // Index positon on the grid with respects used to find distance from midpoint which is seen as origin.
			double xval=midpnt-pos[0];
			double yval=midpnt-pos[1];
			
			
			
			
			field[i][j]=Potential(xval,yval,Enull,RC);
			
		}
		
	}
	
	// WRITING ARRAY INTO DATA FILE
	ofstream goobster ("field.dat");
	
	for (int i=0; i<length; i++){
		for (int j=0; j<width;j++){
			goobster << field[i][j] << " ";
		}
		goobster <<"\n";
	}
	
	
	goobster.close();
	
	
	
	
	
	return 0;
}