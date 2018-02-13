#include "fpstar.h"

int main(int argc, char** argv){

	if(argc!=2){
		printf("Program Syntax:\n\n./<program_name> <length_of_square_image>\n\n");
		exit(INPUT_FAILURE);
	}

	int N=atoi(argv[1]), Nsquare=N*N;
	int (*A)[Nsquare]=malloc(sizeof(int[Nsquare][Nsquare]));
	float *b=calloc(Nsquare, sizeof(float));

	for(int i=0; i<N; i++){
		b[i]=25;
	}

	genSparseFile(*A, N);
	vseek(*A, b, N);

	for(int i=0; i<Nsquare; i++){
		for(int j=0; j<Nsquare; j++){
			printf("%d", A[i][j]);
		}

		printf("\n");
	}
	
	free(A);
	free(b);

	return 0;
}
