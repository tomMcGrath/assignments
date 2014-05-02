#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"McGrath.h"

int main(void){
  double *x, *y, *w, *S;
  double timeSN, timeTN, timeUN;
  int i, N, NMAX, NMIN;

  NMIN = 8;
  NMAX = 268435456;

  x = (double*)malloc((NMAX)*sizeof(double));
  y = (double*)malloc((NMAX)*sizeof(double));
  w = (double*)malloc(NMAX*sizeof(double));
  S = (double*)malloc(((NMAX/2)-1)*sizeof(double));
  S = SFactors(NMAX);

  printf("Name: <Tom McGrath>\n");
  printf("CID: <00898098>, LIBRARY NO: <0246656362>\n");
  printf("Email Address: <t.mcgrath13@imperial.ac.uk>\n");
  printf("Course Code: <M5SC>\n");
  printf("Time: %s\n",__TIME__); 
  printf("Date: %s\n",__DATE__); 

  printf("%10s\t%10s\t%10s\t%10s\n", "N", "SN", "TN", "UN");

  for(N=NMIN;N<=NMAX;N*=2){
    for(i=1;i<N;i++){
      y[i] = i;
      x[i] = 0.0;
    }

    timeSN = 0.0;
    timer(-1);

    FastSN(x,y,w,S,N,1);

    timeSN = timer(1);

    for(i=1;i<N;i++){
      y[i] = i;
      x[i] = 0.0;
    }

    timeTN = 0.0;
    timer(-1);

    FastTN(x,y,w,S,N,1);

    timeTN = timer(1);

    for(i=1;i<N;i++){
      y[i] = i;
      x[i] = 0.0;
    }

    timeUN = 0.0;
    timer(-1);

    FastUN(x,y,w,S,N,1);

    timeUN = timer(1);

    printf("%10d\t%10.8g\t%10.8g\t%10.8g\n", N, timeSN, timeTN, timeUN);

  }

}
