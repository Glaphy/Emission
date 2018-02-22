#ifndef FPSTAR_H
#define FPSTAR_H

#define STBI_ONLY_PNG
#define CHANNEL_NO 3
#define INPUT_FAILURE 1

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <slu_ddefs.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include "csparse.h"

void png2ElectroData(int height, int width, unsigned char *rgb_image, float canvas[height][width][2], float maxV);
void genSparseFile(FILE* sparseTripletFile, int height, int width, float canvas[height][width][2], int N);
void my2Print_Dense_Matrix(char *what, SuperMatrix *A);

#endif /*FPSTAR_H*/
