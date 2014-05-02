#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"McGrath.h"

int main(void){
  // matrix convention: start from 1,1 (blanks in (0,j) and (i,0))
  double **ans;
  double *x, *y, *w, *S;
  double *rho, *psi, *temp;
  double dx, time, psiMax, xMax,TMAX;
  int i,j,N,NMAX,NMIN;

  // TODO
  // all done!

  NMIN = 8;
  NMAX = 268435456;
  //NMAX = 134217728;
  TMAX = 600;

  // preallocate maximum size array to amortize cost over all loops
  temp = (double*)malloc((NMAX)*sizeof(double));
  psi = (double*)malloc((NMAX)*sizeof(double));
  rho = (double*)malloc((NMAX)*sizeof(double));
  w = (double*)malloc(NMAX*sizeof(double));
  S = (double*)malloc(((NMAX/2)-1)*sizeof(double));
  S = SFactors(NMAX);

  printf("Name: <Tom McGrath>\n");
  printf("CID: <00898098>, LIBRARY NO: <0246656362>\n");
  printf("Email Address: <t.mcgrath13@imperial.ac.uk>\n");
  printf("Course Code: <M5SC>\n");
  printf("Time: %s\n",__TIME__); 
  printf("Date: %s\n",__DATE__); 

  // print table header
  printf("%10s\t%10s\t%10s\t%10s\n", "N", "Psi Max", "X Max", "Time");

  //SlowSN2(psi,rho,NMAX);

  
  for(N=NMIN;N<=NMAX;N*=2){
    time = 0.0;
    timer(-1);
    dx = 1./(double)N;
    //printf("dx = %lf\n", dx);

    //printf("N = %d\n", N);
    //printf("initialising rho\n");
    defineQ4(rho,N);
    //displayVector(rho, N-1);

    //printf("Transforming rho\n");
    FastSN(temp, rho, w, S, N, 1);

    //printf("Calculating psi\n");
    calcPsiGood(temp, psi, N);

    //printf("Transforming back\n");
    FastSN(temp,psi,w,S,N,1);

    //displayVector(temp, N-1);

    psiMax = amax(temp, N-1);
    xMax = dx*(double)argamax(temp, N-1);

    time = timer(1);
    printf("%10d\t%10.8g\t%10.8g\t%10.8g\n", N, psiMax, xMax, time);

    if(time > TMAX){
      break;
    }
    //displayVector(temp, N-1);
    //writeVector(temp, N-1, "q4.txt");
  }
  

  free(temp);
  free(psi);
  free(rho);
  free(w);

}
