#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "fpstar.h"

int main(int argc, char** argv){

	//********INITIALISATIONS AND INPUT CHECKING**********// 

	//Initialise Csparse formats
	cs* ST;
	cs* CC;
	//Initialise SuperLU formats
	SuperMatrix A, L, U, B;
	double *a;
	int *asub, *xa;
	//perm_r: row permutations from partial pivoting.
	//perm_c: column permutation vector.
	int *perm_r, *perm_c; 
	int nrhs, info, m, n, nnz;
	superlu_options_t	options;
	//Variables to hold performance statistics.
	SuperLUStat_t		stat;	
	mem_usage_t		mem_usage;
	clock_t start_clock, end_clock;
	double total_clock;

	//check for arguments
	if(argc!=4){
		printf("Program Syntax:\n\n./<program_name> <image>.png <skip X> <skip Y>\n\n");
		exit(INPUT_FAILURE);
	}

	//Reserve variables for height, width, and bits per pixel of the PNG.
	int width, height, bpp;
	char filename[25]="";
	int skipEveryX=atoi(argv[2]), skipEveryY=atoi(argv[3]);
	strcpy(filename, argv[1]);

	if(fopen(filename, "r")==NULL){
		printf("Failed to open %s. Please check the file and try again.\n", filename);
		exit(2);
	}
	
	//Start the clock for the pre-solving 
	start_clock=clock();
	//Load the PNG into memory.
	unsigned char *rgb_image=stbi_load(filename, &width, &height, &bpp, CHANNEL_NO);
	int N=height, Nsquare=N*N;
	
	//Dynamically Allocate space for the A and b matrices.
	double *b=calloc(Nsquare, sizeof(double));

	//Initialise array to hold canvas data i.e, charge and geometry.
	float (*canvas)[width][2]=malloc(sizeof(float[height][width][2]));

	//The maximum voltage the user will specify.	!CHANGE!
	float maxV = 1000;

	//create a file which will hold the Sparse Triplet
	FILE* sparseTripletFile=fopen("sparsematrix.dat", "w+");
	
	if(!sparseTripletFile){
		printf("Failed to generate sparse data file!\n");
		exit(3);
	}

	//**********PARSING PNG DATA AND GENERATING PROBLEM DATA**********//

	//These two functions convert the specified PNG into voltages based on colours
	//fill the canvas, and update the sparseTriplet file and the b vector
	//according to the specified geometry.
	png2ElectroData(height, width, rgb_image, canvas, maxV);
	genSparseFile(sparseTripletFile, height, width, canvas, N);

	//Linearising canvas as the b vector.
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			b[i*N+j]=canvas[i][j][0];
		}
	}
	
	//**********CONVERTING FROM COO TO CCS FORMAT**********//

	//reset pointer to start of file
	fseek(sparseTripletFile,0,SEEK_SET);
	
	//load the Sparse Triplet file into cs ST form, then compress it to cs CC form
	ST = cs_load(sparseTripletFile);
	CC = cs_triplet(ST);
	
	//get some basic information from the cs CC fromat
	nnz = CC->nzmax; // = maximum number of entries
	n = CC->n; // = number of columns
	m = CC->m; // = numer of rows
		
	//Allocate space for matrix A.
	if(!(a=doubleMalloc(nnz)))
		ABORT("Malloc fails for a[].");
	if(!(asub=intMalloc(nnz)))
		ABORT("Malloc fails for asub[].");
	if(!(xa=intMalloc(n+1)))
		ABORT("Malloc fails for xa[].");
	
	//get it into superLU expected form by ->. i.e. go from CS notation to SLU
	a = CC->x; //of size nzmax
	asub = CC->i; //of size nzmax
	xa = CC->p; //of size n(columns) + 1
	
	//End timing of pre-solving part of the code and print the results.
	end_clock=clock();
	total_clock=(double)(end_clock-start_clock)/CLOCKS_PER_SEC;
	printf("\n\n********%f********\n\n", total_clock);

	//*****SOLVING THE SYSTEM WITH LU DECOMPOSITION FROM SUPERLU*****//
	
	//Create matrix A in the format expected by SuperLU.
	dCreate_CompCol_Matrix(&A, m, n, nnz, a, asub, xa, SLU_NC, SLU_D, SLU_GE);

	//Create the dense matrix B to solve AX = B.
	//B matrix will be of size m * nrhs, from entries of b.
	nrhs = 1; 
	dCreate_Dense_Matrix(&B, m, nrhs, b, m, SLU_DN, SLU_D, SLU_GE);

	if(!(perm_r=intMalloc(m)))
		ABORT("Malloc fails for perm_r[].");
	if(!(perm_c=intMalloc(n)))
		ABORT("Malloc fails for perm_c[].");

	//Set the default input options.
	set_default_options(&options);
	options.ColPerm = NATURAL;
	options.DiagPivotThresh = 0.0;

	//Initialize the statistics variables.
	StatInit(&stat);

	//Solve the linear system.
	dgssv(&options, &A, perm_c, perm_r, &L, &U, &B, &stat, &info);

	printPlotData("\nSOLUTION", &B);	
	plotData(skipEveryX,skipEveryY,100);
	
	//*********SLU PERFORMANCE STATISTICS*************//
	
	if(options.PrintStat)
		StatPrint(&stat);

	dQuerySpace(&L, &U, &mem_usage);
	printf("L\\U MB %.3f\ttotal MB needed %.3f\n", mem_usage.for_lu/1e6, mem_usage.total_needed/1e6);

	// De-allocate SLU storage
	SUPERLU_FREE (perm_r);
	SUPERLU_FREE (perm_c);
	Destroy_CompCol_Matrix(&A);
	Destroy_SuperMatrix_Store(&B);
	Destroy_SuperNode_Matrix(&L);
	Destroy_CompCol_Matrix(&U);
	StatFree(&stat);
	
	//De-allocate other storage
	fclose(sparseTripletFile);
	free(canvas);
	free(b);
	stbi_image_free(rgb_image);

	return 0;
}
