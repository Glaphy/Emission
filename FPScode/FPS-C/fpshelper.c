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

void vseek(int* A, int colsA, float* b, int sizeb){
	int L=sizeb;

	for(int i=0; i<L; i++){
		if(b[i]!=0){
			for(int j=0; j<colsA; j++){
				*(A+i*colsA+j)=0;
			}

			*(A+i*colsA+i)=1;
		}
	}
}
