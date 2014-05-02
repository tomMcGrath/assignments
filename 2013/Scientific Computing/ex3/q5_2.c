#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"McGrath.h"

int main(void){
  // matrix convention: start from 1,1 (blanks in (0,j) and (i,0))
  double **ans;
  double *x, *y, *w, *S;
  double **rho, **psi, *temp1, *temp2;
  double dx, time, psiMax, TMAX, xMax, yMax;
  int i,j,N,NMAX,NMIN;

  NMIN = 8;
  NMAX = 16384;
  TMAX = 600;

  // preallocate as in Q4
  rho = make_matrix(NMAX,NMAX);
  psi = make_matrix(NMAX,NMAX);
  temp1 = (double*)malloc(NMAX*sizeof(double));
  temp2 = (double*)malloc(NMAX*sizeof(double));
  w = (double*)malloc(NMAX*sizeof(double));
  S = (double*)malloc(((NMAX/2)-1)*sizeof(double));
  S = SFactors(NMAX);

  // print table header
  printf("%10s\t%10s\t%10s\t%10s\t%10s\n", "N", "Psi Max", "X Max", "Y Max", "Time");

  for(N=NMIN;N<=NMAX;N*=2){
    // clear arrays
    for(i=1;i<N;i++){
      for(j=1;j<N;j++){
	rho[i][j] = 0.0;
	psi[i][j] = 0.0;
      }
    }

    time = 0.0;
    timer(-1);
    dx = 1.0/(double)N;

    // define rho
    defineQ5(rho, N);
    // transform rows first - should it be ij or ji?
    for(i=1;i<N;i++){
      for(j=1;j<N;j++){
	temp1[j] = rho[i][j];
      }
      FastSN(temp2,temp1,w,S,N,1);
      for(j=1;j<N;j++){
	rho[i][j] = temp2[j];
      }
    }

    // now transform columns
    for(i=1;i<N;i++){
      for(j=1;j<N;j++){
	temp1[j] = rho[j][i];
      }
      FastSN(temp2,temp1,w,S,N,1);
      for(j=1;j<N;j++){
	rho[j][i] = temp2[j];
      }
    }
    
    // calculate psi from rho
    calcPsiGood2D(rho, psi, N);

    // transform rows back
    for(i=1;i<N;i++){
      for(j=1;j<N;j++){
	temp1[j] = psi[j][i];
      }
      FastSN(temp2,temp1,w,S,N,1);
      for(j=1;j<N;j++){
	psi[j][i] = temp2[j];
      }
    }

    // now transform columns
    for(i=1;i<N;i++){
      for(j=1;j<N;j++){
	temp1[j] = psi[i][j];
      }
      FastSN(temp2,temp1,w,S,N,1);
      for(j=1;j<N;j++){
	psi[i][j] = temp2[j];
      }
    }
    psiMax = amax2D(psi, N-1);
    xMax = dx*(double)xMax2D(psi, N-1);
    yMax = dx*(double)yMax2D(psi, N-1);

    time = timer(1);
    printf("%10d\t%10.8g\t%10.8g\t%10.8g\t%10.8g\n", N, psiMax, xMax, yMax, time);

    if(time > TMAX){
      break;
    }
    //writeMatrix(psi, N, "q5.txt");
  }
}

