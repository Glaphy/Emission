#include <stdint.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main() {
	int width, height, bpp;

	unsigned char *rgb_image = stbi_load("smiley.png", &width, &height, &bpp, 1);
    
	for(int i=0; i<height; i++){
		for(int j=0; j<width; j++){
			printf("%3d ", *(rgb_image+i*width+j));
		}

		printf("\n");
	}

    stbi_image_free(rgb_image);

    return 0;
}
