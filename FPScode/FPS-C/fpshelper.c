#include "fpstar.h"

void genSparseFile(FILE* sparseTripletFile, int height, int width, float canvas[height][width][2], int N){
	int Nsquare=N*N;
	int targets[Nsquare];
	int target_idx=0;

	//Linearises the canvas. This looks like it could be heavily optimised.
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			targets[target_idx]=canvas[i][j][1];
			target_idx++;
		}
	}

	for(int i=0; i<Nsquare; i++){

		//Code if the current canvas pixel is NOT a specified value.
		if(targets[i]==0){
			//Inserts the leftmost band of ones.
			if(i>=N){
				fprintf(sparseTripletFile, "%d %d 1\n", i, i-N);
			}

			//Inserts the band to the left of the leading diagonal.
			if(i%N!=0){
				fprintf(sparseTripletFile, "%d %d 1\n", i, i-1);
			}

			//The leading diagonal.
			fprintf(sparseTripletFile, "%d %d -4\n", i, i);

			//The band to the right of the leading diagonal.
			if((i+1)%N!=0){
				fprintf(sparseTripletFile, "%d %d 1\n", i, i+1);
			}

			//Inserts the rightmost band of ones.
			if(i<N*(N-1)){
				fprintf(sparseTripletFile, "%d %d 1\n", i, i+N);
			}
		}

		//Code if the current canvas pixel is NOT a specified value.
		else{
			fprintf(sparseTripletFile, "%d %d 1\n", i, i);
		}
	}

	//The period acts as a delimiter.
	fprintf(sparseTripletFile, ".");
}

void png2ElectroData(int height, int width, unsigned char *rgb_image, float canvas[height][width][2], float maxV){

	/*DESCRIPTION:
	use maxV to calculate volatge from colors:
	V = colorvalue * max / 255

	there are 4 cases:
	RED	-->	( +V , 1 )
	GREEN 	-->	( -V , 1 )
	BLACK	-->	(  0 , 1 )
	WHITE	-->	(  0 , 0 )
	*/

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
			}

			else{
				canvas[i/3][j/3][1] = 1;	//if not white => defined

				if (redvalue != 0) { //check if red
					canvas[i/3][j/3][0] = redvalue * maxV / 255;	//positive V
				}

				else if(greenvalue != 0){ //check if green 
					canvas[i/3][j/3][0] = - greenvalue * maxV / 255; //negative V
				}

				else{ //has to be black
					canvas[i/3][j/3][0] = 0;	//0 V
					//printf("BLACK\n");
				}
			}
		}
	}
}
