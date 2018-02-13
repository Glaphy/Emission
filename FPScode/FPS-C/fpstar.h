#ifndef FPSTAR_H
#define FPSTAR_H

#include <stdio.h>
#include <stdlib.h>

#define INPUT_FAILURE 1

void genSparseFile(int* A, int N);
void vseek(int* A, int colsA, float* b, int sizeb);

#endif /*FPSTAR_H*/
