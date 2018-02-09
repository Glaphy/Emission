#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define STBI_ONLY_PNG
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define CHANNEL_NUM 3

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
		printf("Failed to open %s. Please check the file and try\
 again\n.", filename);
		exit(2);
	}

	unsigned char *rgb_image=stbi_load(filename, &width, &height, &bpp, CHANNEL_NUM);
    
	for(int i=0; i<height; i++){
		for(int j=0; j<width*CHANNEL_NUM; j++){
			printf("%3d ", *(rgb_image+i*width+j));
		}

		printf("\n");
	}

	stbi_image_free(rgb_image);

	return 0;
}
