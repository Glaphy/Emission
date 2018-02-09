#include <stdint.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define CHANNEL_NUM 3

int main() {
    int width = 800; 
    int height = 800;

    uint8_t* rgb_image;
    rgb_image = (uint8_t*) malloc(width*height*CHANNEL_NUM);

    // Write your code to populate rgb_image here
	for(int i=0; i<height; i++){
		for(int j=0; j<width; j++){
			if(i==j){
				*(rgb_image+i*width+j)=255;
			} else{
				*(rgb_image+i*width+j)=147;
			}
		}
	}

    stbi_write_png("output.png", width, height, CHANNEL_NUM, rgb_image, width*CHANNEL_NUM);

    return 0;
}
