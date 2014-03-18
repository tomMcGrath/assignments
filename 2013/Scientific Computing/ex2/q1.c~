#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include"McGrath.h"

int main(void){
	double * psi, * charge;
	double dx;
	int i, j, conv, N, numRuns;

	// setup initial variables
	N = 8;
	dx = 1.0/((double)N);
	numRuns = 4;
	
	// allocate space (to be reused dynamically)
	psi = (double *)malloc(N*sizeof(double));
	charge = (double *)malloc(N*sizeof(double));

	// generate charge, psi
	for(i = 0; i <= N; i++){
		psi[i] = 0.0;
		charge[i] = 0.0i;
	}
	for(i = 0; i <= 0.25*N; i++){
		charge[i] = 40;
	}
	for(i = 0; i <= N; i++){
		printf("i = %d\t x = %8g\t charge = %4g\n", i, (double)i*dx, charge[i]);
	}

	for(i = 0; i <= numRuns; i++){
		printf("Iteration %d\n", i);
		// iterate
		conv = 0;
		while(!conv){
			conv = GaussSeid1D(psi, charge, N);
		}
		// display
		for(j = 0; j <= N; j++){
			printf("%10.8g\t%12.8g\t%12.8g\n", j*dx, psi[j], charge[j]);
		}
		// realloc space (saves memory rather than generate new array and using memcpy)
		N *= 2;
		dx = 1.0/(double)N;
		psi = realloc(psi, N*sizeof(double));
		charge = realloc(charge, N*sizeof(double));
		// fill in gaps in charge
		for(j = 0; j <= 0.25*N; j++){
			charge[j] = 40.0;
		}
		for(j = 1 + 0.25*N; j <= N; j++){
			charge[j] = 0.0;
		}
		// smooth out psi
		// WRITE THIS CODE
	}
}

int GaussSeid1D(double * psi, double * charge, int length){
	double iter, dt, diff;
	int i, conv;
	dt = 1.0/(double)length;
	conv = 1;

	for(i = 0; i <= length; i++){
		if(i == 0 || i == length){
			psi[i] = 0;
			iter = 0;
			//printf("site %d\t x %3lf\t psi_old %lf\t psi_new %lf\t diff %e\t charge %lf\n", i, (double)i*dt, psi[i], iter, psi[i] - iter, charge[i]);
		} else {
			iter = psi[i] + 0.5*(psi[i-1] - 2.0*psi[i] + psi[i+1] + dt*dt*charge[i]);
			diff = dabs(psi[i] - iter);
			//printf("site %d\t x %3lf\t psi_old %lf\t psi_new %lf\t diff %e\t charge %lf\n", i, (double)i*dt, psi[i], iter, diff, charge[i]);
			if(conv == 1 && diff < 1e-12){ // sites up till i have converged, site i has converged
				conv = 1;
			} else if(conv == 1 && diff > 1e-12){ // sites up till i have converged, but i has not
				conv = 0;
			} else if(conv == 0){ // sites up till i have not converged
				conv = 0;
			} else {
				printf("error in convergence code\n");
			}
			psi[i] = iter;
		}
	}
	return(conv);
}

double dabs(double x){
	if(x>0.0){return(x);}
	else if (x<0.0){return(-1.0*x);}
	else{return(0.0);}
}
