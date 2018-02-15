#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "fpstar.h"

int main(int argc, char** argv){

	if(argc!=2){
		printf("Program Syntax:\n\n./<program_name> <image>.png\n\n");
		exit(INPUT_FAILURE);
	}

	//Reserve variables for height, width, and bits per pixel of the PNG.
	int width, height, bpp;
	char filename[25]="";
	strcpy(filename, argv[1]);

	if(fopen(filename, "r")==NULL){
		printf("Failed to open %s. Please check the file and try again.\n", filename);
		exit(2);
	}

	//Load the PNG into memory.
	unsigned char *rgb_image=stbi_load(filename, &width, &height, &bpp, CHANNEL_NO);
	int N=height, Nsquare=N*N;
	//Dynamically Allocate space for the A and b matrices.
	int (*A)[Nsquare]=malloc(sizeof(int[Nsquare][Nsquare]));
	float *b=calloc(Nsquare, sizeof(float));
	//Initialise array to hold canvas data i.e, charge and geometry.
	
	//float canvas[50][50][2] = {0};
	float (*canvas)[width][2]=malloc(sizeof(int[height][width][2]));
	//The maximum voltage the user will specify.
	float maxV = 1000;

	//These three function convert the PNG into raw numerical data, fill
	//the canvas, generate A, and edit the appropriate rows of A to
	//account for known voltages.
	png2ElectroData(height, width, maxV, rgb_image, canvas);
	genSparseFile(*A, N);
	vSeek(*A, b, N);

	//**********************TEMPORARY*************************
	FILE* chargefile=fopen("chargefile.dat", "w");
	FILE *geometryfile=fopen("geometryfile.dat", "w");
	
	//print test 
	for(int i=0; i<height; i++){	
		for(int j=0; j<width; j++){
			fprintf(chargefile, "%4f ", canvas[i][j][0]);
			fprintf(geometryfile, "%1f ", canvas[i][j][1]);

		}

		fprintf(chargefile, "\n");
		fprintf(geometryfile, "\n");
	}

	fclose(chargefile);
	fclose(geometryfile);
	//**********************TEMPORARY*************************

	//Free loaded memory.
	free(A);
	free(b);
	stbi_image_free(rgb_image);

	return 0;
}
