#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include<omp.h>
#include"McGrath.h"

int main(void){
	double * psi, * charge, *prev, *tmp, results[8];
	double dx, time;
	int i, j, conv, N, numRuns, iter[4], checkf;
	FILE *answers;


	char hPrint[] =  "%8s,%12s,%12s,%12s,%12s,%12s,%12s,%12s,%12s,%12s\n";
	char rPrint[] = "%8g\t%12g,%12g,%12g,%12g,%12d,%12g%12d,%12g,%12d\n";

	checkf = 50;

	// setup initial variables
	N = 8;
	dx = 1.0/((double)N);
	numRuns = 30;
	
	// allocate space (to be reused dynamically)
	psi = (double *)malloc(N*sizeof(double));
	charge = (double *)malloc(N*sizeof(double));
	prev = (double *)malloc(N*sizeof(double));

	// generate charge, psi
	for(i = 0; i <= N; i++){
		psi[i] = 0.0;
		charge[i] = 0.0i;
	}
	for(i = 0; i <= 0.25*N; i++){
		charge[i] = 40;
	}

	//print header
	answers = fopen("1DSOR.txt", "w");
	fprintf(answers, hPrint, "N", "max psi r", "x max psi", "max psi s", "psi=0 time", "# sweeps", "psi prev t", "sweeps", "t best", "sweeps");
	printf(hPrint, "N", "max psi r", "x max psi", "max psi s", "psi=0 time", "# sweeps", "psi prev t", "sweeps", "t best", "sweeps");

	for(i = 0; i <= numRuns; i++){
		// ROUGH DISTRIBUTION
		for(j = 0; j <= 0.25*N; j++){
			charge[j] = 40.0;
			psi[j] = 0.0;
		}
		for(j = 1 + 0.25*N; j <= N; j++){
			charge[j] = 0.0;
			psi[j] = 0.0;
		}

		results[0] = N;
		// iterate
		conv = 0;
		while(!conv){
			conv = GaussSeid1D(psi, charge, N,1.0);
		}
		if(N==64){
		writeArray(psi,N,"test1.txt");
		}
		// save psi, max x of psi
		//printf("max = %lf\n", amax(psi,N));
		//printf("argamax = %d\n", argamax(psi,N));
		//printf("max charge = %lf\n", amax(charge, N));
		results[1] = amax(psi, N);
		results[2] = argamax(psi, N);

		// SMOOTH DISTRIBUTION, reset psi
		for(j=0;j<=N;j++){
			if(j*dx<0.25){
				charge[j] = 40.0;
				psi[j] = 0.0;
			} else if(j*dx==0.25) {
				charge[j] = 20.0;
				psi[j] = 0.0;
			} else {
				charge[j] = 0.0;
				psi[j] = 0.0;
			}
		}

		// iterate and time
		conv = 0;
		iter[0] = 0;
		timer(0);
		while(!conv){
			conv = GaussSeid1D(psi, charge, N,1.0);
			iter[0]+=1;
		}
		time = timer(-1);
		results[3] = amax(psi, N);
		results[4] = time;

		writeArray(psi, N, "1dSOR0.txt");

		// ROUGH DISTRIBUTION, interpolated from previous by eq 3
		for(j = 0; j <= 0.25*N; j++){
			charge[j] = 40.0;
			psi[j] = prev[j];
		}
		for(j = 1 + 0.25*N; j <= N; j++){
			charge[j] = 0.0;
			psi[j] = prev[j];
		}

		// interpolate by eq 3
		for(j=1;j<=N;j+=2){
			psi[j] = psi[j] + 0.5*(psi[j-1] - 2.0*psi[j] + psi[j+1] + dx*dx*charge[j]);
		}

		// iterate and time
		timer(0);
		iter[1] = 0;
		conv = 0;
		while(!conv){
			conv = GaussSeid1D(psi, charge, N,1.0);
			iter[1]+=1;
		}
		time = timer(-1);
		results[5] = time;

		// SMOOTH DISTRIBUTION, interpolated from previous by equation 3
		for(j=0;j<=N;j++){
			if(j*dx<0.25){
				charge[j] = 40.0;
				psi[j] = prev[j];
			} else if(j*dx==0.25) {
				charge[j] = 20.0;
				psi[j] = prev[j];
			} else {
				charge[j] = 0.0;
				psi[j] = prev[j];
			}
		}

		// interpolate by eq 3
		for(j=1;j<=N;j+=2){
			psi[j] = psi[j] + 0.5*(psi[j-1] - 2.0*psi[j] + psi[j+1] + dx*dx*charge[j]);
		}

		// iterate and time
		timer(0);
		iter[2] = 0;
		conv = 0;
		while(!conv){
			conv = GaussSeid1D(psi, charge, N,1.0);
			iter[2]+=1;
		}
		time = timer(-1);
		results[6] = time;

		// need to save the previous psi
		prev = realloc(prev, 2*N*sizeof(double));

		for(j=0;j<N;j++){
			prev[2*j] = psi[j];
		}

		// realloc space (saves memory rather than generate new array and using memcpy)
		N *= 2;
		dx = 1.0/(double)N;
		psi = realloc(psi, N*sizeof(double));
		charge = realloc(charge, N*sizeof(double));
		
		// print results - why is the smooth case from previous results so quick?
		printf(rPrint, results[0], results[1], dx*results[2], results[3], results[4], iter[0], results[5], iter[1],results[6],iter[2]);
		fprintf(answers, rPrint, results[0], results[1], dx*results[2], results[3], results[4], iter[0], results[5], iter[1],results[6],iter[2]);
		
	}
	fclose(answers);

	//RBSOR case
	printf("Red Black SOR in parallel\n");
	// setup initial variables
	N = 8;
	dx = 1.0/((double)N);
	numRuns = 20;
	
	// allocate space (to be reused dynamically)
	psi = (double *)malloc(N*sizeof(double));
	charge = (double *)malloc(N*sizeof(double));
	prev = (double *)malloc(N*sizeof(double));
	tmp = (double *)malloc(N*sizeof(double));

	// generate charge, psi
	for(i = 0; i <= N; i++){
		psi[i] = 0.0;
		charge[i] = 0.0;
		tmp[i] = 0.0;
	}
	for(i = 0; i <= 0.25*N; i++){
		charge[i] = 40;
	}

	answers = fopen("1DRBSOR.txt", "w");
	fprintf(answers, hPrint, "N", "max psi r", "x max psi", "max psi s", "psi=0 time", "# sweeps", "psi prev t", "sweeps", "t best", "sweeps");

	//print header
	printf(hPrint, "N", "max psi r", "x max psi", "max psi s", "psi=0 time", "# sweeps", "psi prev t", "sweeps", "t best", "sweeps");

	for(i = 0; i <= numRuns; i++){
		// ROUGH DISTRIBUTION
		for(j = 0; j <= 0.25*N; j++){
			charge[j] = 40.0;
			psi[j] = 0.0;
		}
		for(j = 1 + 0.25*N; j <= N; j++){
			charge[j] = 0.0;
			psi[j] = 0.0;
		}

		results[0] = N;
		// iterate
		conv = 0;
		iter[0] = 0;
		while(!conv){
			for(j=0;j<=checkf;j++){
				conv=RBSOR1D(psi,charge,N,tmp,0); // don't check
				iter[0] += 1;
			}
			conv = RBSOR1D(psi,charge,N,tmp,1);
			iter[0] += 1;
		}
		// save psi, max x of psi
		results[1] = amax(psi, N);
		results[2] = argamax(psi, N);

		// write to file
		writeArray(psi, N, "1dSOR.txt");

		// SMOOTH DISTRIBUTION, reset psi
		for(j=0;j<=N;j++){
			if(j*dx<0.25){
				charge[j] = 40.0;
				psi[j] = 0.0;
			} else if(j*dx==0.25) {
				charge[j] = 20.0;
				psi[j] = 0.0;
			} else {
				charge[j] = 0.0;
				psi[j] = 0.0;
			}
		}

		// iterate and time
		conv = 0;
		iter[1] = 0;
		timer(0);
		while(!conv){
			for(j=0;j<=checkf;j++){
				conv=RBSOR1D(psi,charge,N,tmp,0); // don't check
				iter[1] += 1;
			}
			conv = RBSOR1D(psi,charge,N,tmp,1);
			iter[1] += 1;
		}
		time = timer(-1);
		results[3] = amax(psi, N);
		results[4] = time;

		writeArray(psi, N, "1dSOR2.txt");

		// ROUGH DISTRIBUTION, interpolated from previous by eq 3
		for(j = 0; j <= 0.25*N; j++){
			charge[j] = 40.0;
			psi[j] = prev[j];
		}
		for(j = 1 + 0.25*N; j <= N; j++){
			charge[j] = 0.0;
			psi[j] = prev[j];
		}

		// interpolate by eq 3
		for(j=1;j<=N;j+=2){
			psi[j] = psi[j] + 0.5*(psi[j-1] - 2.0*psi[j] + psi[j+1] + dx*dx*charge[j]);
		}

		// iterate and time
		timer(0);
		iter[2] = 0;
		conv = 0;
		while(!conv){
			for(j=0;j<=checkf;j++){
				conv=RBSOR1D(psi,charge,N,tmp,0); // don't check
				iter[2] += 1;
			}
			conv = RBSOR1D(psi,charge,N,tmp,1);
			iter[2] += 1;
		}
		time = timer(-1);
		results[5] = time;

		writeArray(psi, N, "1dSOR3.txt");

		// SMOOTH DISTRIBUTION, interpolated from previous by equation 3
		for(j=0;j<=N;j++){
			if(j*dx<0.25){
				charge[j] = 40.0;
				psi[j] = prev[j];
			} else if(j*dx==0.25) {
				charge[j] = 20.0;
				psi[j] = prev[j];
			} else {
				charge[j] = 0.0;
				psi[j] = prev[j];
			}
		}

		// interpolate by eq 3
		for(j=1;j<=N;j+=2){
			psi[j] = psi[j] + 0.5*(psi[j-1] - 2.0*psi[j] + psi[j+1] + dx*dx*charge[j]);
		}

		// iterate and time
		timer(0);
		iter[3] = 0;
		conv = 0;
		while(!conv){
			for(j=0;j<=checkf;j++){
				conv=RBSOR1D(psi,charge,N,tmp,0); // don't check
				iter[3] += 1;
			}
			conv = RBSOR1D(psi,charge,N,tmp,1);
			iter[3] += 1;
		}
		time = timer(-1);
		results[6] = time;

		writeArray(psi, N, "1dSOR4.txt");

		// need to save the previous psi
		prev = realloc(prev, 2*N*sizeof(double));

		for(j=0;j<N;j++){
			prev[2*j] = psi[j];
		}

		// realloc space (saves memory rather than generate new array and using memcpy)
		N *= 2;
		dx = 1.0/(double)N;
		psi = realloc(psi, N*sizeof(double));
		charge = realloc(charge, N*sizeof(double));
		tmp = realloc(tmp, N*sizeof(double));
		
		// print results - why is the smooth case from previous results so quick?
		printf(rPrint, results[0], results[1], dx*results[2], results[3], results[4], iter[0], results[5], iter[1],results[6],iter[3]);
		fprintf(answers, rPrint, results[0], results[1], dx*results[2], results[3], results[4], iter[0], results[5], iter[1],results[6],iter[2]);
	}
	fclose(answers);

}

int GaussSeid1D(double * psi, double * charge, int length, double r){
	double iter, dt, diff, omega;
	int i, conv;
	dt = 1.0/(double)length;
	conv = 1;
	omega = 2.0-((2.0*M_PI)/(double)length);

	for(i = 0; i <= length; i++){
		if(i == 0 || i == length){
			psi[i] = 0;
			iter = 0;
			//printf("site %d\t x %3lf\t psi_old %lf\t psi_new %lf\t diff %e\t charge %lf\n", i, (double)i*dt, psi[i], iter, psi[i] - iter, charge[i]);
		} else {
			iter = psi[i] + (omega/2.0)*(psi[i-1] + - 2.0*psi[i] + psi[i+1] + dt*dt*charge[i]);
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

int RBSOR1D(double *psi, double *charge, int N, double *tmp, int check){
	double iter, dx, diff, omega;
	int i, conv;
	dx = 1.0/(double)N;
	omega = 1;

	#pragma omp parallel private(i)
	{
	#pragma omp for
	for(i=0;i<=N;i+=2){
		if(i==0||i==N){
			tmp[i] = 0.0;
		} else {
			tmp[i] = psi[i] + (omega/2.0)*(psi[i-1] - 2.0*psi[i] + psi[i+1] + dx*dx*charge[i]);
			//printf("prev %d = %lf\t new %d = %lf\n", i, psi[i], i, tmp[i]);
		}
	}
	#pragma omp for
	for(i=1;i<=N;i+=2){
		if(i==0||i==N){
			tmp[i] = 0.0;
		} else {
			tmp[i] = psi[i] + (omega/2.0)*(psi[i-1] - 2.0*psi[i] + psi[i+1] + dx*dx*charge[i]);
			//printf("prev %d = %lf\t new %d = %lf\n", i, psi[i], i, tmp[i]);
		}	
	}
	}
	//check convergence
	conv = 1;
	if(check == 1){
		for(i=0;i<=N;i++){
			diff = dabs(psi[i] - tmp[i]);
			if(conv == 1 && diff < 1e-12){ // sites up till i have converged, site i has converged
				conv = 1;
			} else if(conv == 1 && diff > 1e-12){ // sites up till i have converged, but i has not
				conv = 0;
			} else if(conv == 0){ // sites up till i have not converged
				conv = 0;
			} else {
				printf("error in convergence code\n");
			}
			psi[i] = tmp[i];
		}
		// copy results back
		for(i=0;i<=N;i++){
			psi[i] = tmp[i];
		}
		return(conv);
	} else {
		// copy results back
		for(i=0;i<=N;i++){
			psi[i] = tmp[i];
		}
	return(0);
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
	for(i=0;i<=len;i++){
		if(M[i] > max){
			max = M[i];
		} else {
			;
		}
	}
	return(max);
}

int argamax(double *M, int len){
	double maxval;
	int i, maxi;

	maxval = M[0];
	maxi=0;
	for(i=0;i<=len;i++){
		if(M[i] > maxval){
			maxval = M[i];
			maxi=i;
		} else {
			;
		}
	}
	return(maxi);
}

int writeArray(double *M, int len, char *path){
	FILE *writeFile;
	int i;
	
	writeFile = fopen(path, "w");
	//printf("File opened OK\n");
	for(i = 0; i <= len; i++){
		fprintf(writeFile, "%g,", M[i]);
	fprintf(writeFile, "\n");
	}

	fclose(writeFile);
	//printf("File closed OK\n");
	return(0);
}














