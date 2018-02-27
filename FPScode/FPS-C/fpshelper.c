#include "fpstar.h"

void genSparseFile(FILE* sparseTripletFile, int height, int width, float canvas[height][width][2], int N){
	int Nsquare=N*N;
	int targets[Nsquare];

	//Linearises the canvas.
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			targets[i*N+j]=canvas[i][j][1];
		}
	}

	for(int i=0; i<Nsquare; i++){

		//Code if the current canvas pixel is NOT a specified value.
		if(targets[i]==0){
			//Inserts the leftmost band of ones.
			if(i>=N){
				fprintf(sparseTripletFile, "%d %d 1\n", i, i-N);
			}

			//Inserts the band to the left of the leading diagonal.
			if(i%N!=0){
				fprintf(sparseTripletFile, "%d %d 1\n", i, i-1);
			}

			//The leading diagonal.
			fprintf(sparseTripletFile, "%d %d -4\n", i, i);

			//The band to the right of the leading diagonal.
			if((i+1)%N!=0){
				fprintf(sparseTripletFile, "%d %d 1\n", i, i+1);
			}

			//Inserts the rightmost band of ones.
			if(i<N*(N-1)){
				fprintf(sparseTripletFile, "%d %d 1\n", i, i+N);
			}
		}

		//Code if the current canvas pixel is NOT a specified value.
		else{
			fprintf(sparseTripletFile, "%d %d 1\n", i, i);
		}
	}

	//The period acts as a delimiter.
	fprintf(sparseTripletFile, ".");
}

void png2ElectroData(int height, int width, unsigned char *rgb_image, float canvas[height][width][2], int maxV){

	/*DESCRIPTION:
	use maxV to calculate volatge from colors:
	V = colorvalue * max / 255

	there are 4 cases:
	RED	-->	( +V , 1 )
	GREEN 	-->	( -V , 1 )
	BLACK	-->	(  0 , 1 )
	WHITE	-->	(  0 , 0 )
	*/

	for (int i = 0; i < height*CHANNEL_NO; i+=3){
		for (int j = 0; j < (width*CHANNEL_NO); j = j + 3){ //move in 3 since RGB

			float redvalue, greenvalue, bluevalue = 0;

			//using the order or R G B, obtain colour values:
			redvalue = (*(rgb_image + i*width + j + 0));	// Red
			greenvalue = (*(rgb_image + i*width + j + 1)); // Green
			bluevalue = (*(rgb_image + i*width + j + 2));	// Blue (for white)

			if (bluevalue == 255) { //check if white 
				canvas[i/3][j/3][1] = 0;	//undefined, empty space
				//printf("WHITE\n");
			}

			else{
				canvas[i/3][j/3][1] = 1;	//if not white => defined

				if (redvalue != 0) { //check if red
					canvas[i/3][j/3][0] = (redvalue * maxV) / 255;	//positive V
				}

				else if(greenvalue != 0){ //check if green 
					canvas[i/3][j/3][0] = - (greenvalue * maxV) / 255; //negative V
				}

				else{ //has to be black
					canvas[i/3][j/3][0] = 0;	//0 V
					//printf("BLACK\n");
				}
			}
		}
	}
}

//This fills the voltage and electric files in the format that gnuplot expects.
void printPlotData(char *what, SuperMatrix *A) {
	DNformat* Astore = (DNformat*) A->Store;
	int i;
	double *dp, gradx, grady, scalefactor, normx, normy;
	FILE* voltagefile = fopen("potentials.dat","w");
	FILE* electrofile = fopen("electricfield.dat","w");

	dp = (double *) Astore->nzval;
	int nroot = sqrt(A->nrow);
	int columncounter = 0;
	int counter = 1;
	
	gradx = dp[0] - dp[1];
	grady = dp[0] - dp[nroot];
	scalefactor = 4; //*sqrt(gradx*gradx+grady*grady);

	for (i = 0; i < A->nrow; i++) {
		gradx = dp[i] - dp[i+1];
		grady = dp[i] - dp[i+nroot];
		normx = gradx / scalefactor;
		normy = grady / scalefactor;
		
		//zero any outlying points in electric field.
		if(i>((A->nrow)-nroot) || (i%nroot == 0)){
			fprintf(electrofile,"%d %d 0 0\n", columncounter, (i%nroot));
		}
		
		else{
			fprintf(electrofile,"%d %d %f %f\n", columncounter, (i%nroot), normy, normx);
		}

		fprintf(voltagefile,"%d %d %f\n", columncounter, (i%nroot), dp[i]);

		//Make a newline between each full row in the files.
		if(counter % nroot == 0){
			fprintf(electrofile,"\n");
			fprintf(voltagefile,"\n");
			columncounter++;
		}

		counter++;
	}

	printf("\n");

	fclose(electrofile);
	fclose(voltagefile);
	fflush(stdout);
}

void plotData(int skipEveryX, int skipEveryY, int scaleFactor){
	FILE* gpProcess=popen("gnuplot", "w");
	char skipEveryP[40]="";
	char skipEveryE[256]="";

	sprintf(skipEveryP, "splot \"potentials.dat\" every %d:%d", skipEveryX, skipEveryY);
	sprintf(skipEveryE, "plot \"electricfield.dat\" every %d:%d u 1:2:3:4 w vectors nofilled head lw 1", skipEveryX, skipEveryY);

	/*char* gpElectric[]={"set term qt 1", "set xrange [75:424]", \
		"set yrange [75:424]", skipEveryE};*/

	char* gpPotential[]={"set term qt", "set pm3d", "set xrange [75:424]"\
		, "set title \"Potential\"", "set yrange [75:424]", skipEveryP,\
			"pause mouse key", "if (MOUSE_KEY != 27) reread"};

	//int gpElectricLen=(double)sizeof(gpElectric)/sizeof(char*);
	int gpPotentialLen=(double)sizeof(gpPotential)/sizeof(char*);


	/*for(int i=0; i<gpElectricLen; i++){
		fprintf(gpProcess,"%s\n", gpElectric[i]);
	}*/

	for(int i=0; i<gpPotentialLen; i++){
		fprintf(gpProcess,"%s\n", gpPotential[i]);
	}

	pclose(gpProcess);
}
