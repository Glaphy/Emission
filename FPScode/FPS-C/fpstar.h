#ifndef FPSTAR_H
#define FPSTAR_H

#define STBI_ONLY_PNG
#define CHANNEL_NO 3
#define INPUT_FAILURE 1

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


void png2ElectroData(int height, int width, float maxV, unsigned char *rgb_image, float canvas[height][width][2]);
void genSparseFile(int* A, int N);
void vseek(int* A, float* b, int N);

#endif /*FPSTAR_H*/
