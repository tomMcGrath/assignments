#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<omp.h>
#include<time.h>
#include"McGrath.h"

int main(void){
	double **charge, **psi, **tmp, **prev;
	double dx, omega, pos[2], results[5], times[2];
	int n, i, j, N, conv, numRuns, count;
	FILE *answers;
	char hPrint[] =  "%8s,%12s,%12s,%12s,%12s,%12s,%12s,%12s,%12s,%12s\n";
	char rPrint[] = "%8g\t%12g,%12g,%12g,%12g,%12d,%12g%12d,%12g,%12d\n";

	numRuns = 1;
	N = 2048;
	dx = 1.0/(double)N;

	// initialise matrices
	charge = make_matrix(N,N);
	psi = make_matrix(N,N);
	prev = make_matrix(N,N);

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
			prev[i][j] = 0.0;
		}
	}


	answers = fopen("2DRBSOR.txt", "w");
	// OMEGA = opt;
	printf("Omega = opt\n");
	omega = 2.0 - ((2.0*M_PI)/(double)N);
	// results header
	printf("%6s\t%10s\t%10s\t%10s\t%10s\t%10s\t%10s\t%10s\n", "N", "max psi", "x max psi", "y max psi", "psi=0 t", "sweeps", "psi interp t", "sweeps");
	omega = 2.0-((2.0*M_PI)/(double)N);
	for(n = 1; n <= numRuns; n++){
		// PSI = 0
		// iterate on this size matrix
		conv = 0;
		count = 0;
		timer(0);
		while(!conv){
			conv = RBSOR2D(charge, psi, N, omega);
			count++;
		}
		times[0] = timer(-1);
		results[0] = amax2D(psi, N);
		argamax2D(psi, N, pos);
		results[1] = dx*pos[0];
		results[2] = dx*pos[1];
		results[3] = count;

		// interpolate from previous psi
		for(i=0;i<=N;i++){
			for(j=0;j<=N;j++){
				psi[i][j] = prev[i][j];
			}
		}
		interpPsi2D(charge, psi, N);
		// PSI = prev
		// iterate on this size matrix
		conv = 0;
		count = 0;
		timer(0);
		while(!conv){
			conv = RBSOR2D(charge, psi, N, omega);
			count++;
		}
		times[1] = timer(-1);
		results[4] = count;


		// need to save the previous psi
		prev = growMatrix(prev, N);
		for(i=0;i<=N;i++){
			for(j=0;j<=N;j++){
				prev[2*i][2*j] = psi[i][j];
			}
		}

		// write data to file
		writeMatrix(psi, N, "SOR2D.txt");

		charge = growMatrix(charge, N);
		psi = growMatrix(psi, N);
		N *= 2;
		dx = 1.0/(double)N;
		omega = 2.0 - ((2.0*M_PI)/(double)N);
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
		// print results
		printf("%6d\t%10g\t%10g\t%10g\t%10g\t%10g\t%10g\t%10g\n", N/2, results[0], results[1], results[2], times[0], results[3], times[1], results[4]);

	}
	fclose(answers);

	// OMEGA = opt;
	printf("Omega = optimal\n");
	// results header
	printf("%6s\t%10s\t%10s\t%10s\t%10s\t%10s\t%10s\t%10s\n", "N", "max psi", "x max psi", "y max psi", "psi=0 t", "sweeps", "psi interp t", "sweeps");
	N = 8;
	omega = 2 - (2*M_PI)/(double)N;
	for(n = 1; n <= numRuns; n++){
		// PSI = 0
		// iterate on this size matrix
		conv = 0;
		count = 0;
		timer(0);
		while(!conv){
			conv = RBSOR2D(charge, psi, N, omega);
			count++;
		}
		times[0] = timer(-1);
		results[0] = amax2D(psi, N);
		argamax2D(psi, N, pos);
		results[1] = dx*pos[0];
		results[2] = dx*pos[1];
		results[3] = count;

		// interpolate from previous psi
		for(i=0;i<=N;i++){
			for(j=0;j<=N;j++){
				psi[i][j] = prev[i][j];
			}
		}
		interpPsi2D(charge, psi, N);
		// PSI = prev
		// iterate on this size matrix
		conv = 0;
		count = 0;
		timer(0);
		while(!conv){
			conv = RBSOR2D(charge, psi, N, omega);
			count++;
		}
		times[1] = timer(-1);
		results[4] = count;


		// need to save the previous psi
		prev = growMatrix(prev, N);
		for(i=0;i<=N;i++){
			for(j=0;j<=N;j++){
				prev[2*i][2*j] = psi[i][j];
			}
		}

		// write data to file
		writeMatrix(psi, N, "SOR2D.txt");

		charge = growMatrix(charge, N);
		psi = growMatrix(psi, N);
		N *= 2;
		dx = 1.0/(double)N;
		omega = 2 - (2*M_PI)/(double)N;

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
		// print results
		printf("%6d\t%10g\t%10g\t%10g\t%10g\t%10g\t%10g\t%10g\n", N/2, results[0], results[1], results[2], times[0], results[3], times[1], results[4]);

	}
}

double RBSOR2D(double ** charge, double ** psi, int N, double omega){
	double **tmp;
	double dx, iter, diff;
	int i, j, conv;
	omp_lock_t lck;
	omp_init_lock(&lck);

	tmp = make_matrix(N,N);
	conv = 1;
	dx = 1.0/(double)N;
	omega = 2.0 - (2.0*M_PI)/(double)N;

	#pragma omp parallel private(i, j)
	{
	// colour 1
	#pragma omp for 
	for(i = 0; i <= N; i += 2){
		for(j = 0; j <= N; j += 2){
			if((i==0||i==N) || (j==0||j==N)){
				psi[i][j] = 0.0;
			} else {
				tmp[i][j] = psi[i][j];
				psi[i][j] = psi[i][j] + (omega/4.0)*(psi[i-1][j] + psi[i][j-1] - 4.0*psi[i][j] + psi[i+1][j] + psi[i][j+1] + dx*dx*charge[i][j]);	
			}
		}
	}

	// colour 2
	#pragma omp for 
	for(i = 1; i <= N; i += 2){
		for(j = 1; j <= N; j += 2){
			if((i==0||i==N) || (j==0||j==N)){
				psi[i][j] = 0.0;
			} else {
				tmp[i][j] = psi[i][j];
				psi[i][j] = psi[i][j] + (omega/4.0)*(psi[i-1][j] + psi[i][j-1] - 4.0*psi[i][j] + psi[i+1][j] + psi[i][j+1] + dx*dx*charge[i][j]);
			}
		}
	}

	// colour 3
	#pragma omp for 
	for(i = 0; i <= N; i += 2){
		for(j = 1; j <= N; j += 2){
			if((i==0||i==N) || (j==0||j==N)){
				psi[i][j] = 0.0;
			} else {
				tmp[i][j] = psi[i][j];
				psi[i][j] = psi[i][j] + (omega/4.0)*(psi[i-1][j] + psi[i][j-1] - 4.0*psi[i][j] + psi[i+1][j] + psi[i][j+1] + dx*dx*charge[i][j]);			}
		}
	}

	// colour 4
	#pragma omp for 
	for(i = 1; i <= N; i += 2){
		for(j = 0; j <= N; j += 2){
			if((i==0||i==N) || (j==0||j==N)){
				psi[i][j] = 0.0;
			} else {
				tmp[i][j] = psi[i][j];
				psi[i][j] = psi[i][j] + (omega/4.0)*(psi[i-1][j] + psi[i][j-1] - 4.0*psi[i][j] + psi[i+1][j] + psi[i][j+1] + dx*dx*charge[i][j]);			}
		}
	}
	}
	#pragma omp for
	for(i = 1; i < N; i++){
		for(j = 1; j < N; j++){
			if(dabs(tmp[i][j] - psi[i][j]) > 1e-12){
				conv = 0;
				break;
			}
		}
	}
	free(tmp[0]);
	free(tmp);
	return(conv);
}

int SOR2D(double ** charge, double ** psi, int N, double omega){
	double dx, iter, diff;
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
	for(i = 0; i <= len; i++){
		for(j = 0; j <= len; j++){
			fprintf(writeFile, "%g,", M[i][j]);
		}
	fprintf(writeFile, "\n");
	}

	fclose(writeFile);
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

double timer(int T){ // from the lecture notes
	static double then = 0.0;
	double now, diff;

	now=(double)clock()/(double)CLOCKS_PER_SEC;
	diff=now-then;
	if(T<0) then=now;

	return(diff);
}

double amax(double *M, int len){
	double max;
	int i;

	max = M[0];
	for(i=1;i<=len;i++){
		if(M[i] > max){
			max = M[i];
		} else {
			continue;
		}
	}

	return(max);
}

int argamax(double *M, int len){
	double max;
	int i;

	max = M[0];
	for(i=1;i<=len;i++){
		if(M[i] > max){
			max = i;
		} else {
			continue;
		}
	}

	return((int)max);
}


double amax2D(double **M, int len){
	double max;
	int i, j;

	max = amax(M[0], len);
	for(i=1;i<=len;i++){
		if(amax(M[i], len) > max){
			max = amax(M[i], len);
		} else {
			continue;
		}
	}
	return(max);
}


double *argamax2D(double **M, int len, double pos[2]){
	double max;
	int i,j;

	max = M[0][0];
	for(i=0;i<=len;i++){
		for(j=0;j<=len;j++){
			if(M[i][j] > max){
				max = M[i][j];
				pos[0] = i;
				pos[1] = j;
			} else {
				continue;
			}
		}
	}
	return(pos);
}

int interpPsi2D(double **charge, double ** psi, int N){
	double dx, omega;
	int i, j;

	dx = 1.0/(double)N;
	omega = 1;

	for(i=1;i<=N;i+=2){
		for(j=1;j<=N;j+=2){
			if((i == 0 || i == N) || (j == 0 || j == N)){
				psi[i][j] = 0.0;
			} else {
				psi[i][j] = (omega/4.0)*(psi[i-1][j-1] + psi[i+1][j-1] + psi[i+1][j+1] + psi[i-1][j+1] + dx*dx*charge[i][j]);
			}
		}
	}

	for(i=0;i<N;i+=2){
		for(j=1;j<=N;j+=2){
			if((i == 0 || i == N) || (j == 0 || j == N)){
				psi[i][j] = 0.0;
			} else {
				psi[i][j] = (omega/4.0)*(psi[i+1][j]+psi[i-1][j]+psi[i][j+1]+psi[i][j-1]+dx*dx*charge[i][j]);
			}
		}
	}

	for(i=1;i<N;i+=2){
		for(j=0;j<=N;j+=2){
			if((i == 0 || i == N) || (j == 0 || j == N)){
				psi[i][j] = 0.0;
			} else {
				psi[i][j] = (omega/4.0)*(psi[i+1][j]+psi[i-1][j]+psi[i][j+1]+psi[i][j-1]+dx*dx*charge[i][j]);
			}
		}
	}

}
