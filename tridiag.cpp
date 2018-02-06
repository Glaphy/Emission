#include <iostream>

#define N 7

using namespace std;

//void print_array(int *A[]);

int main(void){
	int A[N*N][N*N]={0};

	for(int i=0; i<N*N; i++){
		A[i][i]=-4;
		
		if(i%N!=0){
			A[i][i-1]=1;
		}

		if((i+1)%N!=0){
			A[i][i+1]=1;
		}

		if(i<N*(N-1)){
			A[i+N][i]=1;
			A[i][i+N]=1;
		}
	}


	for(int i=0; i<N*N; i++){
		for(int j=0; j<N*N; j++){
			cout<<A[i][j];
		}
		cout<<endl;
	}


	return 0;
}

//void print_array(int *A[]){
//	int L=sizeof(A[0])/sizeof(int);
//	cout<<L<<endl;
//
//	for(int i=0; i<L; i++){
//		for(int j=0; j<L; j++){
////			printf("%2d ", A[i][j]);
//			cout<<A[i][j];
//		}
//		cout<<endl;
//	}
//}
