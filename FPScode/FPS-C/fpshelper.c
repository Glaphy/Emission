#include "fpstar.h"

void genSparseFile(int* A, int N){
	int Nsquare=N*N;

	for(int i=0; i<Nsquare; i++){
		*(A+i*Nsquare+i)=-4;
		
		if(i%N!=0){
			*(A+i*Nsquare+i-1)=1;
		}

		if((i+1)%N!=0){
			*(A+i*Nsquare+i+1)=1;
		}

		if(i<N*(N-1)){
			*(A+(i+N)*Nsquare+i)=1;
			*(A+i*Nsquare+i+N)=1;
		}
	}
}

void vSeek(int* A, float* b, int N){
	int Nsquare=N*N;

	for(int i=0; i<Nsquare; i++){
		if(b[i]!=0){
			for(int j=0; j<Nsquare; j++){
				*(A+i*Nsquare+j)=0;
			}

			*(A+i*Nsquare+i)=1;
		}
	}
}

/*DESCRIPTION:
use maxV to calculate volatge from colors:
V = colorvalue * max / 255

there are 4 cases:
RED	-->	( +V , 1 )
GREEN 	-->	( -V , 1 )
BLACK	-->	(  0 , 1 )
WHITE	-->	(  0 , 0 )
*/

void png2ElectroData(int height, int width, float maxV, unsigned char *rgb_image, float canvas[height][width][2]){
	for (int i = 0; i < height*CHANNEL_NO; i+=3){
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
				canvas[i/3][j/3][0] = redvalue * maxV / 255;	//positive V
				
				} else if (greenvalue != 0) { //check if green 
					canvas[i/3][j/3][0] = - greenvalue * maxV / 255; //negative V
				
				} else { //has to be black
					canvas[i/3][j/3][0] = 0;	//0 V
					//printf("BLACK\n");
				}
			}
		}
	}
}
