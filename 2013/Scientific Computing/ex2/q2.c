#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"McGrath.h"

int main(void){
	double **charge, **psi, **tmp;
	double dx, omega;
	int n, i, j, N, conv, numRuns;

	numRuns = 10;
	N = 8;
	dx = 1.0/(double)N;

	// initialise matrices
	charge = make_matrix(N,N);
	psi = make_matrix(N,N);

	// assign values to charge
	for(i = 0; i <= N; i++){
		for(j = 0; j <= N; j++){
			if((i*dx < 0.25) && (j*dx < 0.25)){
				charge[i][j] = 100.0;
			} else if (((i*dx == 0.25) && (j*dx < 0.25)) || ((i*dx < 0.25) && (j*dx == 0.25))){
				charge[i][j] = 50;
			} else if ((i*dx == 0.25) && (j*dx == 0.25)){
				charge[i][j] = 25;
			}
		}
	}

	for(i = 0; i <= N; i++){
		for(j = 0; j <= N; j++){
			psi[i][j] = 0.0;
		}
	}

	//printf("Before iterations\n");
	//displayMatrix(psi, N);

	for(n = 1; n <= numRuns; n++){
		printf("i = %d\n", n);
		// iterate on this size matrix
		conv = 0;
		while(!conv){
			conv = RBSOR2D(charge, psi, N);
		}

		// write data to file
		writeMatrix(psi, N, "SOR2D.txt");

		// show psi
		//printf("After iterations\n");
		//displayMatrix(psi, N);
		// show charge
		//printf("Charge matrix\n");
		//displayMatrix(charge, N);

		//printf("Expanding matrix\n");
		charge = growMatrix(charge, N);
		psi = growMatrix(psi, N);
		N *= 2;
		dx = 1.0/(double)N;
		omega = 2.0 - (2*M_PI)/(double)N;

		//displayMatrix(psi, N);

		// assign values to charge
		for(i = 0; i <= N; i++){
			for(j = 0; j <= N; j++){
				if((i*dx < 0.25) && (j*dx < 0.25)){
					charge[i][j] = 100.0;
				} else if (((i*dx == 0.25) && (j*dx < 0.25)) || ((i*dx < 0.25) && (j*dx == 0.25))){
					charge[i][j] = 50;
				} else if ((i*dx == 0.25) && (j*dx == 0.25)){
					charge[i][j] = 25;
				}
			}
		}
		//printf("Expanded charge matrix\n");
		//displayMatrix(charge, N);

		// interpolate psi
		for(i = 1; i <= N; i += 2){
			for(j = 1; j <= N; j += 2){
				psi[i][j] = (omega/4.0)*(psi[i-1][j] + psi[i][j-1] + psi[i+1][j] + psi[i][j+1] + dx*dx*charge[i][j]);
			}
		}
	}
}

int RBSOR2D(double ** charge, double ** psi, int N){
	double dx, iter, diff, omega;
	int i, j, conv;

	conv = 1;
	dx = 1.0/(double)N;
	omega = 2.0 - (2.0*M_PI)/(double)N;

	// even (red) points
	for(i = 0; i <= N; i+=2){
		for(j = 0; j <= N; j+=2){
			// SOR calculation
			if((i == 0 || i == N) || (j == 0 || j == N)){
				psi[i][j] = 0.0;
				iter = 0.0;
			} else {
				iter = psi[i][j] + (omega/4.0)*(psi[i-1][j] + psi[i][j-1] - 4.0*psi[i][j] + psi[i+1][j] + psi[i][j+1] + dx*dx*charge[i][j]);
				diff = dabs(iter - psi[i][j]);
				// convergence testing
				if(conv == 1 && diff < 1e-12){ // sites up till i have converged, site i has converged
					conv = 1;
				} else if(conv == 1 && diff > 1e-12){ // sites up till i have converged, but i has not
					conv = 0;
				} else if(conv == 0){ // sites up till i have not converged
					conv = 0;
				} else {
					printf("error in convergence code\n");
				}
				psi[i][j] = iter;
			}
		}
	}

	// odd (black) points
	for(i = 1; i <= N; i+=2){
		for(j = 1; j <= N; j+=2){
			// SOR calculation
			if((i == 0 || i == N) || (j == 0 || j == N)){
				psi[i][j] = 0.0;
				iter = 0.0;
			} else {
				iter = psi[i][j] + (omega/4.0)*(psi[i-1][j] + psi[i][j-1] - 4.0*psi[i][j] + psi[i+1][j] + psi[i][j+1] + dx*dx*charge[i][j]);
				diff = dabs(iter - psi[i][j]);
				// convergence testing
				if(conv == 1 && diff < 1e-12){ // sites up till i have converged, site i has converged
					conv = 1;
				} else if(conv == 1 && diff > 1e-12){ // sites up till i have converged, but i has not
					conv = 0;
				} else if(conv == 0){ // sites up till i have not converged
					conv = 0;
				} else {
					printf("error in convergence code\n");
				}
				psi[i][j] = iter;
			}
		}
	}
	return(conv);
}

int SOR2D(double ** charge, double ** psi, int N){
	double dx, iter, diff, omega;
	int i, j, conv;

	conv = 1;
	dx = 1.0/(double)N;
	omega = 2.0 - (2.0*M_PI)/(double)N;

	for(i = 0; i <= N; i++){
		for(j = 0; j <= N; j++){
			// SOR calculation
			if((i == 0 || i == N) || (j == 0 || j == N)){
				psi[i][j] = 0.0;
				iter = 0.0;
			} else {
				iter = psi[i][j] + (omega/4.0)*(psi[i-1][j] + psi[i][j-1] - 4.0*psi[i][j] + psi[i+1][j] + psi[i][j+1] + dx*dx*charge[i][j]);
				diff = dabs(iter - psi[i][j]);
				// convergence testing
				if(conv == 1 && diff < 1e-12){ // sites up till i have converged, site i has converged
					conv = 1;
				} else if(conv == 1 && diff > 1e-12){ // sites up till i have converged, but i has not
					conv = 0;
				} else if(conv == 0){ // sites up till i have not converged
					conv = 0;
				} else {
					printf("error in convergence code\n");
				}
				psi[i][j] = iter;
			}
		}
	}
	return(conv);
}

int writeMatrix(double **M, int len, char *path){
	FILE *writeFile;
	int i, j;
	
	writeFile = fopen(path, "w");
	printf("File opened OK\n");
	for(i = 0; i <= len; i++){
		for(j = 0; j <= len; j++){
			fprintf(writeFile, "%g,", M[i][j]);
		}
	fprintf(writeFile, "\n");
	}

	fclose(writeFile);
	printf("File closed OK\n");
	return(0);
}

double **growMatrix(double **t, int len){
	double ** tmp;
	int i, j;

	tmp = make_matrix(2*len, 2*len);
	for(i = 0; i <= len; i++){
		for(j = 0; j < len; j++){
			tmp[2*i][2*j] = t[i][j];
		}
	}
	free(t[0]);
	free(t);

	len *=2;
	t = make_matrix(len, len);
	for(i = 0; i <= len; i++){
		for(j = 0; j <= len; j++){
			t[i][j] = tmp[i][j];
		}
	}
	free(tmp[0]);
	free(tmp);
	return(t);
}

double **make_matrix(int NR, int NC){ // from lecture notes
	double **M;
	int i, j, n;
	M = (double **)malloc((NR+1)*sizeof(double*));
	M[0] = (double *)malloc((NR+1)*(NC+1)*sizeof(double));
	for(n = 1; n <= NR; n++) M[n] = M[n-1] + NC+1;
	for(i = 0; i <= NR; i++){
		for(j = 0; j <= NC; j++){
			M[i][j] = 0.0;
		}
	}
	return(M);
}

void displayMatrix(double ** M, int len){
	int i, j;
	for(i = 0; i <= len; i++){
		for(j = 0; j <= len; j++){
			printf("%3.3g\t", M[i][j]);
		}
	printf("\n");
	}
}

double dabs(double x){
	if(x>0.0){return(x);}
	else if (x<0.0){return(-1.0*x);}
	else{return(0.0);}
}
