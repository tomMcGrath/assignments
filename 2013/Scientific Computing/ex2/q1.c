#include<stdio.h>
#include<math.h>
#include"McGrath.h"

int main(void){
	double grid[8];
	double charge[8];
	int i, j, conv;

	for(i = 0; i < 8; i++){
		grid[i] = 0;
		charge[i] = 0;
	}
	charge[0] = 40;
	charge[1] = 40;

	conv = 0;
	i = 0;
	while(conv != 1){
		printf("i = %d\n", i);
		conv =  GaussSeid1D(grid, charge, 8);
		i++;
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
			printf("site %d\t x %3lf\t psi_old %lf\t psi_new %lf\t diff %e\n", i, (double)i*dt, psi[i], iter, psi[i] - iter);
		} else {
			iter = psi[i] + 0.5*(psi[i-1] - 2.0*psi[i] + psi[i+1] + dt*dt*charge[i]);
			diff = dabs(psi[i] - iter);
			printf("site %d\t x %3lf\t psi_old %lf\t psi_new %lf\t diff %e\n", i, (double)i*dt, psi[i], iter, diff);
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
