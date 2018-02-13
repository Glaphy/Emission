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


int main(int argc, char *argv[]) {
  int width, height, bpp;
  char filename[25]="";
  
  if(argc!=2){
    puts("Please use the following syntax:");
    puts("<program_name> <image_name>.png");
    exit(1);
  }
  
  strcpy(filename, argv[1]);
  
  if(fopen(filename, "r")==NULL){
    printf("Failed to open %s. Please check the file and try again\n.", filename);
    exit(2);
  }
  
  unsigned char *rgb_image=stbi_load(filename, &width, &height, &bpp, CHANNEL_NO);
  printf("%dx%d\n%d\n", height, width, bpp);
  
  /*
    for(int i=0; i<height*CHANNEL_NO; i++){	//should this * CHANNEL?
    for(int j=0; j<width*CHANNEL_NO; j++){
    printf("%3d ", *(rgb_image+i*width+j));
    }
    
    printf("\n");
    }*/
  
  //explicit definition of height and width
  float canvas[50][50][2] = {0};	//initialise canvas to hold (voltage, plate)
  float max = 1000;	//this value must come from Tom
  
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
  double tmax=400;
  double error=0;
  double tolerance=50;
  double dt=0.1;
  double v=1;
  int xmin=0;
  int xmax2=71;
  int xmax=70;
  int ymax=70;
  int ymax2=71;
  int dx=1;
  double dy=dx;
  int y;
  
  
  
  //********//INPUT FROM USER//*********//
  char gauss_out_file[50];
  char reply;
  cout << "Please enter" << endl;
  cout << "Name of output file:" << endl;
  cin.getline ( gauss_out_file, 50 );
  ofstream gauss_out ( gauss_out_file );
  
  cout << "Choose boudndary 1 or 2" << endl;
  cin >> y;
  
  //  cout << "Please enter the error tolerance" << endl;
  //  cin >> tolerance;
  
  
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
  int midx=(sizeof(xvalues)/sizeof(double))/2;
  int midy=(sizeof(yvalues)/sizeof(double))/2;
  
  
  //centering the presented matrix
  double test[51][51];
  int shiftx, shifty;
  shiftx=(70-50)/2;
  shifty=(70-50)/2;
  
  
  
  //u will hold the current time values, uplus will hold the n+1 time value
  //assume that first two arrays are the same
  double u[ymax2][xmax2];
  double uplus[ymax2][xmax2];
  for(int j=xmin;j<ymax2;j=j+dx){
    for(int i=xmin;i<xmax2;i=i+dx){
      u[j][i]=0;
      uplus[j][i]=0;
      
    }
  }
  
  
  
//********//METHOD//*********//
  
  //Looping through time
  while (tmax >= t){
    error=0;
    
    //staggered leapfrog ~ iterating through grid
    for(int j=(xmin);j<(ymax2);j=j+dx){
      for(int i=(xmin);i<(xmax2);i=i+dx){
	if(i > xmin && i < xmax && j > xmin && j < ymax) {
	  //Numerical method	
				uplus[j][i]=u[j][i]+((v*dt)/(dx*dx))*(u[(j+1)][i]-(2*u[j][i])+u[(j-1)][i]+u[j][(i+1)]-(2*u[j][i])+u[j][(i-1)]); 
				
	}
	
	
	if(i > shiftx && i < (xmax2-shiftx) && j > shifty && j < (ymax2-shifty) ){	
	  if(canvas[(j-shifty)][(i-shiftx)][1] == 1 ) {
	    uplus[j][i]=canvas[(j-shifty)][(i-shiftx)][0];
	  }
	}
	
	//Boundaries//
	if(y==1){
	  //Boundaries(1)
	  double M_1;
	  M_1=(uplus[(xmin+2)][i]-uplus[(xmin+1)][i]);
	  uplus[xmin][i]=uplus[(xmin+1)][i]-M_1;
	  M_1=(uplus[(ymax-2)][i]-uplus[(ymax-1)][i]);
	  uplus[ymax][i]=uplus[(ymax-1)][i]-M_1;
	  M_1=(uplus[j][(xmin+2)]-uplus[j][(xmin+1)]);
	  uplus[j][xmin]=uplus[j][(xmin+1)]-M_1;
	  M_1=(uplus[j][(xmax-2)]-uplus[j][(xmax-1)]);
	  uplus[j][xmax]=uplus[j][(xmax-1)]-M_1;
	  cout << uplus[j][xmin] << " " << uplus[j][xmax]<< " " <<M_1<<endl;
	}
	else if(y==2){
	  //Boundary (2)
	  double M_1xa,M_2xa,M_0xa,M_1xb,M_2xb,M_0xb,M_1ya,M_2ya,M_0ya,M_1yb,M_2yb,M_0yb;
	  M_2xa=uplus[(xmin+3)][i]-uplus[(xmin+2)][i];
	  if(round(M_2xa)!=0){
	    M_1xa=uplus[(xmin+2)][i]-uplus[(xmin+1)][i];
	    M_0xa=(M_1xa*M_1xa)/round(M_2xa);
	    uplus[xmin][i]=uplus[(xmin+1)][i]-M_0xa;
	  }
	  
	  
	  /*M_2xb=uplus[(ymax-3)][i]-uplus[(ymax-2)][i];
	  if(round(M_2xb)!=0){
	    M_1xb=uplus[(ymax-2)][i]-uplus[(ymax-1)][i];
	    M_0xb=(M_1xb*M_1xb)/round(M_2xb);
	    uplus[ymax][i]=uplus[(ymax-1)][i]-M_0xb;
	  }
	  	  
	  M_2ya=uplus[j][(xmin+3)]-uplus[j][(xmin+2)];
	  if(round(M_2ya)!=0){
	    M_1ya=uplus[j][(xmin+2)]-uplus[j][(xmin+1)];
	    M_0ya=(M_1ya*M_1ya)/round(M_2ya);
	    uplus[j][xmin]=uplus[j][(xmin+1)]-M_0ya;
	    }*/
	  
	  M_2yb=uplus[j][(xmax-3)]-uplus[j][(xmax-2)];
	  if(round(M_2yb)!=0){
	    M_1yb=uplus[j][(xmax-2)]-uplus[j][(xmax-1)];
	    M_0yb=(M_1yb*M_1yb)/round(M_2yb);
	    uplus[j][xmax]=uplus[j][(xmax-1)]-M_0yb;
	  }
	}

	//error
	error=error+abs(uplus[j][i]-u[j][i]);
	
      }
    }
    
    //ERROR CONTROL    
    if (error < tolerance ){
      cout << "Error tolerance reached: " << error << endl;
      break;
    }
    //Resetting matrix u
    for(int j=xmin;j<ymax2;j=j+dx){
      for (int i=xmin;i<xmax2;i=i+dx){	
	u[j][i]=uplus[j][i];
      }
    }
    
    tmax=tmax-dt;
    //cout << tmax << endl;
  }  
  
  
  
  //********//PLOTTING SECTION//*********//
  
  //POTENTIALS//
  for(int j=0;j<ymax2;j=j+dx){
    for(int i=0;i<xmax2;i=i+dx){
      gauss_out << i << " " << j << " " << u[j][i]<< endl;;
    }
    gauss_out << " " << endl;
  }
  
  cout << "Done"<<endl;
  gauss_out.close();
  
  
  
  //GRADIENTS//
  char grad_file[50];
  cout << "Name of output file:" << endl;
  cin>> grad_file;
  //cin.getline ( grad_file, 50 );
  ofstream grad ( grad_file );
  
  
  
  double ugradx[xmax2][xmax2]; 
  double ugrady[xmax2][xmax2];
  
  for(int o=xmin;o<ymax2;o=o+dx){
    for (int w=xmin;w<xmax2;w=w+dx){
      ugradx[o][w]=u[o][w]-u[o][(w+1)];
      ugrady[o][w]=u[o][w]-u[(o+1)][w];
    }
  }
  
  for(int j=0;j<ymax2;j=j+dx){
    for(int i=0;i<xmax2;i=i+dx){
      grad << xvalues[i] << " " << yvalues[j] << " " << ugradx[j][i]/50 << " " << ugrady[j][i]/50 << endl;;
    }
    grad << " " << endl;
  }
  cout << "Done2"<<endl;
  grad.close();
  cout << u[0][0] << endl;
  
  return 0;
}
