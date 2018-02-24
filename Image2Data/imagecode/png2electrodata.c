#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"

#define CHANNEL_NO 3


int main(int argc, char *argv[]) {
	int width, height, bpp;
	char filename[25]="";
	FILE *chargefile, *geometryfile;

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

	chargefile=fopen("chargefile.dat", "w");
	geometryfile=fopen("geometryfile.dat", "w");
	
	//print test 
	for(int i=0; i<height; i++){	
		for(int j=0; j<width; j++){
			fprintf(chargefile, "%4f ", canvas[i][j][0]);
			fprintf(geometryfile, "%1f ", canvas[i][j][1]);

		}

		fprintf(chargefile, "\n");
		fprintf(geometryfile, "\n");
	}

	fclose(chargefile);
	fclose(geometryfile);

	
	return 0;
}
