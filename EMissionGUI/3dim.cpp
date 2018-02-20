#include <stdint.h>
#include <string.h>
#include<fstream>
#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<cmath>
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"
using namespace std;

#define CHANNEL_NO 3
	
	
	
int trivialMatrix(char* filename, double tolerance, bool infinite, double max) {
	int width, height, bpp;
	//char filename[25]="";

	//strcpy(filename, argv[1]);
	
	if(fopen(filename, "r")==NULL){
		printf("Failed to open %s. Please check the file and try again\n.", filename);
		exit(2);
	}

	unsigned char *rgb_image=stbi_load(filename, &width, &height, &bpp, CHANNEL_NO);
    //printf("%dx%d\n%d\n", height, width, bpp);


	//Allocating the canvas array.
	float ***canvas= new float **[height];

	for(int i=0; i<height; i++){
		canvas[i]=new float*[width];
		
		for(int j=0; j<width; j++){
			canvas[i][j]=new float[2];
		}
	}

	//loat max = 1000;	//this value must come from Tom
	
	/*DESCRIPTION:
	use max to calculate volatge from colors:
	V = colorvalue * max / 255
	
	there are 4 cases:
	RED		-->	( +V , 1 )
	GREEN 	-->	( - V , 1  )
	BLACK	-->	(  0  , 1  )
	WHITE	-->	(  0  , 0  )
	*/
	
	//CODE the above relationships:
	for (int i = 0; i < height*CHANNEL_NO; i+=3) {	//*CHANNEL?
		for (int j = 0; j < (width*CHANNEL_NO); j = j + 3){ //move in 3 since RGB
			
			float redvalue, greenvalue, bluevalue = 0;
			
			//using the order or R G B, obtain colour values:
			redvalue = (*(rgb_image + i*width + j + 0));	// Red
			greenvalue = (*(rgb_image + i*width + j + 1)); // Green
			bluevalue = (*(rgb_image + i*width + j + 2));	// Blue (for white)
			
			if (bluevalue == 255) { //check if white 
				canvas[i/3][j/3][1] = 0;	//undefined, empty space
				//printf("WHITE\n");
				
			} else {
				canvas[i/3][j/3][1] = 1;	//if not white => defined
				
				if (redvalue != 0) { //check if red
				canvas[i/3][j/3][0] = redvalue * max / 255;	//positive V
				
				} else if (greenvalue != 0) { //check if green 
					canvas[i/3][j/3][0] = - greenvalue * max / 255; //negative V
				
				} else { //has to be black
					canvas[i/3][j/3][0] = 0;	//0 V
					//printf("BLACK\n");
				}
			}
		}
	}
	
//********//INITIATING VARIABLES//*********//

double t=0; //time zero
double tmax=100000;
double error=0;
double dt=1;
double v=1;
int xmin=0;
int xmax2=height*1.2;
int xmax=xmax2-1.2;
int ymax2=width*1.2;
int ymax=ymax2-1;
int dx=1;
double dy=dx;
double total;


//********//INPUT FROM USER//*********//***************
char gauss_out_file[50]="datpic.dat";
ofstream gauss_out ( gauss_out_file );



//********//INITIATING ARRAYS//*********//

//create array of x and y values
double xvalues[xmax];
double yvalues[ymax];
for (int i=xmin;i<xmax;i=i+dx){
	xvalues[i]=i;
}
for(int j=xmin;j<ymax;j=j+dy){
	yvalues[j]=j;
}

//centering the presented matrix
int shiftx, shifty;
shiftx=(xmax2-height)/2;
shifty=(ymax2-width)/2;
 


//u will hold the current time values, uplus will hold the n+1 time value
//assume that first two arrays are the same
double u[ymax2][xmax2];
double uplus[ymax2][xmax2][2];
for(int j=xmin;j<ymax2;j=j+dx){
	for(int i=xmin;i<xmax2;i=i+dx){
		u[j][i]=0;
		uplus[j][i][0]=0;
		uplus[j][i][1]=0;		
	}
}    


//FROM CANVAS TO UPLUS 
for(int j=shifty; j<(ymax-shifty); j=j+dx){
	for(int i=shiftx;i<(xmax-shiftx);i=i+dx){
		if(canvas[(j-shifty)][(i-shiftx)][1] == 1 ) {
			uplus[j][i][0]=canvas[(j-shifty)][(i-shiftx)][0];
			uplus[j][i][1]=1;	
		}		
	}
}


//Extending Sides to simulate infinite plates
if(infinite) {
	//sides N-S
	for(int j=shifty; j<(ymax-shifty); j=j+dx){
		if(canvas[(j-shifty)][0][1]== 1 ) {
			for(int p=0;p<=shifty;p++) { 
				uplus[j][shiftx-p][0]= canvas[(j-shifty)][0][0];
				uplus[j][shiftx-p][1]= canvas[(j-shifty)][0][1];
			}
		}
		if(canvas[(j-shifty)][(xmax-2*shiftx)][1] == 1 ){
			for(int p=0;p<=shifty;p++) { 
				uplus[j][xmax-shiftx+p][0]=canvas[(j-shifty)][(xmax-2*shiftx)][0];
				uplus[j][xmax-shiftx+p][1]=canvas[(j-shifty)][(xmax-2*shiftx)][1];
			}
		}
	}

	//sides E-W
	for(int i=shiftx; i<(xmax-shiftx); i=i+dx){
		if(canvas[0][(i-shifty)][1] == 1 ) {
			for(int p=0;p<=shiftx;p++) { 
				uplus[shiftx-p][i][0]= canvas[0][(i-shifty)][0];
				uplus[shiftx-p][i][1]= canvas[0][(i-shifty)][1];
			}
		}
		if(canvas[(ymax-2*shifty)][(i-shiftx)][1] == 1 ){
			for(int p=0;p<=shiftx;p++) { 
				uplus[xmax-shiftx+p][i][0]=canvas[(ymax-2*shifty)][(i-shiftx)][0];
				uplus[xmax-shiftx+p][i][1]=canvas[(ymax-2*shifty)][(i-shiftx)][1];
			}
		}
	}
}



//********//METHOD//*********//

//Looping through time 

while (tmax >= t){
	error=0;
        total=0;
	
	//staggered leapfrog ~ iterating through grid
	for(int j=xmin; j<ymax2; j++){
		for(int i=xmin;i<xmax2;i++){
			if(i > xmin && i < xmax && j > xmin && j < ymax && uplus[j][i][1] == 0) {
				//Numerical method
				uplus[j][i][0]=u[j][i]+((v*dt)/(dx*dx))*(u[(j+1)][i]-(2*u[j][i])+u[(j-1)][i]+u[j][(i+1)]-(2*u[j][i])+u[j][(i-1)]); 
				//error
				error=error+abs(uplus[j][i][0]-u[j][i]);
				total=total+abs(uplus[j][i][0]);
			}				
			
			//Boundaries//
            double M_1;
			M_1=(uplus[(xmin+2)][i][0]-uplus[(xmin+1)][i][0]);
			uplus[xmin][i][0]=uplus[(xmin+1)][i][0]-M_1;
			M_1=(uplus[(ymax-2)][i][0]-uplus[(ymax-1)][i][0]);
			uplus[ymax][i][0]=uplus[(ymax-1)][i][0]-M_1;
			M_1=(uplus[j][(xmin+2)][0]-uplus[j][(xmin+1)][0]);
			uplus[j][xmin][0]=uplus[j][(xmin+1)][0]-M_1;
			M_1=(uplus[j][(xmax-2)][0]-uplus[j][(xmax-1)][0]);
			uplus[j][xmax][0]=uplus[j][(xmax-1)][0]-M_1;
		}
		
	}
	
	
	//ERROR CONTROL    
	if ( error*100/total/dt  < tolerance && (1000-tmax)/dt != 0 ) {
        cout << "Error tolerance reached: " << error*100/total/dt  << "% " << (100000-tmax)/dt << endl;
		break;
	}
	
	//Resetting matrix u
	for(int j=xmin;j<ymax2;j=j+dx){
		for(int i=xmin;i<xmax2;i=i+dx){
			u[j][i]=uplus[j][i][0];	
		}
	}    
	tmax=tmax-dt;
	
}  
	
//Deallocating the canvas array.
for(int i=0; i<height; i++){
	for(int j=0; j<width; j++){
		delete[] canvas[i][j];
	}

	delete[] canvas[i];
}

delete[] canvas;
  
  


//********//PLOTTING SECTION//*********//

//POTENTIALS//	
for(int j=shifty+1;j<(ymax-shifty);j=j+4*dx){
    for(int i=shiftx+1;i<(xmax-shiftx);i=i+4*dx){
		gauss_out << i-shiftx << " " << j-shifty+1 << " " << u[j][i]<< endl;;
	}
	gauss_out << " " << endl;
}
gauss_out.close();


//***************TEST********************//
char plot_file[50]="datpic2.dat";
ofstream plot ( plot_file );

for(int j=0;j<(ymax2);j=j+dx){
	for(int i=0;i<(xmax2);i=i+dx){
		plot << i << " " << j << " " << u[j][i]<< endl;;
	}
	plot << " " << endl;
}
plot.close();

//GRADIENTS//
char grad_file[50]="grad.dat";
ofstream grad ( grad_file );

double ugradx[(ymax2-2*shifty)][(xmax2-2*shiftx)]; 
double ugrady[(ymax2-2*shifty)][(xmax2-2*shiftx)];
 
for(int o=xmin;o<(ymax2-2*shifty);o=o+dx){
	for (int w=xmin;w<(xmax2-2*shiftx);w=w+dx){
		ugradx[o][w]=u[(o+shifty)][(w+shiftx)]-u[(o+shifty)][(w+shiftx+1)];
		ugrady[o][w]=u[(o+shifty)][(w+shiftx)]-u[(o+shifty+1)][(w+shiftx)];
	}
}
 
for(int j=0;j<(ymax2-2*shifty);j=j+dx){
	for(int i=0;i<(xmax2-2*shiftx);i=i+dx){
		grad << xvalues[i] << " " << yvalues[j] << " " << ugradx[j][i]/50 << " " << ugrady[j][i]/50 << endl;;
	}
	grad << " " << endl;
}
grad.close();

return 0;
}



//int main() {
//char png_name[]="1.png";
//double tolerance=0.1;
//bool infinite=false;
//double max=1000;
//trivialMatrix(png_name,tolerance,infinite,max);


//return 0;
//}
