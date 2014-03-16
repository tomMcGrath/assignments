#include<stdio.h>
#include<math.h>

int GaussSeid1D(double* psi, double* charge, int length){
	int i, conv;
	double dx, iter, diff;
	dx = 1.0/(double)length;
	conv = 0;
	for(i = 0; i < length; i++){
		if(i == 0 || i == length){
			psi[i] = 0;
			iter = 0;
		} else {
			iter = psi[i] + 0.5*(psi[i-1] - 2.0*psi[i] - psi[i+1] + dx*dx*charge[i]);
		}
		if(abs(iter - psi[i]) < 1e-12){ // test if this site has converged
			conv = 1;
		} else {
			conv = 0; // this should flip conv back if we have not converged
		}
		diff = abs(iter - psi[i]);
		psi[i] = iter;
		printf("site %d\t psi = %e\t diff = %e\n", i, psi[i], diff);
	}
	return(conv);
}
