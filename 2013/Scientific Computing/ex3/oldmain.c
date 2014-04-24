#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"McGrath.h"

int main(void){
  double *ans, **m1, **m2, **m3;
  int i,N;

  // slowSN testing
  m1 = slowSN(4);
  m2 = slowTN(4);
  printf("SN matrix\n");
  displayMatrix(m1,4);
  printf("TN matrix\n");
  displayMatrix(m2,4);
  

// SFactors testing
  /* ans = (double*)malloc(((32/2)-1)*sizeof(double)); */
  /* ans = SFactors(32); */
  /* for(i=0;i<((32/2)-1);i++){ */
  /*   printf("%d\t%lf\n",i, ans[i]); */
  /* } */
  /* ans = (double*)realloc(ans, ((64/2)-1)*sizeof(double)); */
  /* ans = SFactors(64); */
  /* for(i=0;i<((64/2)-1);i++){ */
  /*   printf("%d\t%lf\n",i, ans[i]); */
  /* } */


  // matrix multiplication testing
  /* m1 = make_matrix(2,2); */
  /* m2 = make_matrix(2,2); */
  /* m1[0][0]=1.0; */
  /* m1[1][1]=6.0; */
  /* m1[0][1]=9.0; */
  /* m1[1][0]=7.0; */
  /* m2[0][0]=8.0; */
  /* m2[1][1]=5.0; */
  /* m2[1][0]=3.0; */
  /* m2[0][1]=4.0; */
  /* m3 = make_matrix(2,2); */
  /* m3 = matrix_multiply(m1,m2,2,2,2,2); */
  /* displayMatrix(m1,2); */
  /* displayMatrix(m2,2); */
  /* displayMatrix(m3,2); */
}

int FastSN(double *x, double *y, double *w, double *S, int N, int skip){
  return(0);
}

double **slowSN(int N){
  // wrong - need to start from i,j = 1
  int i,j;
  double **SN;

  SN = make_matrix(N,N);
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      SN[i][j]=sin((i*j*M_PI)/(double)N);
    }
  }
  return(SN);
}

double **slowTN(int N){
  // wrong - need to start from i,j = 1
  int i,j;
  double **TN;

  TN = make_matrix(N,N);
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      TN[i][j]=sin(((2.0*i-1)*j*M_PI)/(2.0*(double)N));
    }
  }
  return(TN);
}

double* SFactors(int N){
  static int maxN;
  static double *factors;
  double *rVals, *tmp;
  int i,j,k;

  printf("maxN = %d\n", maxN);

  if(maxN>=N){
    printf("returning from memory\n");
    rVals = (double*)malloc(((N/2)-1)*sizeof(double));
    for(i=0;i<=((N/2)-1);i++){
      rVals[i] = factors[i];
    }
    return(rVals);
  } else if (maxN < N){
    // could improve by only calculating new values
    printf("calculating extra factors\n");
    factors = (double*)realloc(factors, ((N/2)-1)*sizeof(double));
    k=0;
    for(i=4;i<=N;i*=2){
      for(j=1;j<=((i/2)-1);j+=2){
	factors[k]=M_PI*j/i;
	k++;
      }
    }
    maxN = N;
    return(factors);
  }

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

double **matrix_multiply(double **M1, double **M2, int n1, int m1, int n2, int m2){
  double **ans;
  int i,j,k;
  // multiply two matrices, first n1xm1, second n2xm2
  // returns n1xm2 matrix product
  // first check that the matrix dimensions agree
  // we need that n1 = m2
  if(n1 != m2){
    printf("matrix dimensions do not agree\n");
    exit(0);
  }

  // create result matrix
  ans = make_matrix(n1, m2);

  // if the dimensions agree we can continue
  // three-loop structure, can reorder for efficiency? can parallelise?

  for(i=0;i<n1;i++){
    for(j=0;j<m2;j++){
      for(k=0;k<m1;k++){
	ans[i][j] += M1[i][k]*M2[k][j];
      }
    }
  }
  return(ans);
}

void displayMatrix(double ** M, int len){
	int i, j;
	for(i = 0; i < len; i++){
		for(j = 0; j < len; j++){
			printf("%3.3g\t", M[i][j]);
		}
	printf("\n");
	}
}
