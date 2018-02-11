#include <stdio.h>
#include <stdlib.h>

int* vseek(int* A, float* b){
	int L=sizeof(b)/sizeof(int), colsA=sizeof(A[0])/sizeof(A[0][0]);

	for(int i=0; i<L; i++){
		if(b[i]!=0){
			for(int j=0; j<colsA; j++){
				*(A+i*colsA+j)=0;
			}

			*(A+i*colsA+i)=1;
		}
	}

	return A;
}
