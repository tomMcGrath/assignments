#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"McGrath.h"

int main(void){
  // matrix convention: start from 1,1 (blanks in (0,j) and (i,0))
  double **ans;
  double *x, *y, *w, *S;
  int i,j,N;

  // TODO
  // - debug recursive call of SN - probably done now but needs checking. Works for N=4
  // - debug TN - done
  // - debug UN - the problem is in reassembling the values
  // - use SFactors to return values in base case, FastTN, FastUN

  N=4;
  y = (double*)malloc((N-1)*sizeof(double));
  x = (double*)malloc((N-1)*sizeof(double));
  w = (double*)malloc(N*sizeof(double));
  S = (double*)malloc(N*sizeof(double));
  for(i=1;i<=N;i++){
    y[i] = i;
  }

  // testing code
  /*
  printf("Running SlowSN\n");
  SlowSN(x,y,w,S,N,1);
  printf("Running SlowTN\n");
  SlowTN(x,y,w,S,N,1);
  printf("Running SlowUN\n");
  SlowUN(x,y,w,S,N,1);
  */

  /*
  printf("TESTING FastSN:\n");
  printf("running FastSN\n");
  FastSN(x,y,w,S,N,1);
  displayVector(x,N-1);

  printf("running SlowSN\n");
  for(i=1;i<=N;i++){
    x[i] = 0;
    y[i] = i;
  }
  SlowSN(x,y,w,S,N,1);
  // displayVector(x,N-1);
  */

  /*
  printf("TESTING FastTN:\n");
  printf("running FastTN:\n");
  for(i=1;i<=N;i++){
    x[i] = 0;
    y[i] = i;
  }
  FastTN(x,y,w,S,N,1);
  printf("Results from SlowTN:\n");
  displayVector(x,N);

  printf("running SlowTN:\n");
  for(i=1;i<=N;i++){
    x[i] = 0;
    y[i] = i;
  }
  SlowTN(x,y,w,S,N,1);
  */

  
  printf("TESTING FastUN:\n");
  printf("running FastUN:\n");
  for(i=1;i<=N;i++){
    x[i] = 0;
    y[i] = i;
  }
  FastUN(x,y,w,S,N,1);
  printf("Result from FastUN\n");
  displayVector(x,N);

  printf("running SlowUN:\n");
  for(i=1;i<=N;i++){
    x[i] = 0;
    y[i] = i;
  }
  SlowUN(x,y,w,S,N,1);
  

  return(0);
}

int FastSN(double *x, double *y, double *w, double *S, int N, int skip){
  int i,j;

  if(N==2){
    // the base case for recursion
    printf("Base case for FastSN\n");
    x[skip] = y[skip]; // should this be skip or 1?
    return(0);
  } else if(N%2==0) {
    // recursive block
    // store s and a in the work array
    for(i=1;i<(N/2);i+=2){
      w[i] = y[i] + y[N-i]; // s values
      printf("s value w[%d] = %lf\n", i, w[i]);
    }
    w[N-1] = y[N/2]; // central s value
    printf("w[%d] = %lf\n", N-1, w[N-1]);
    for(i=1;i<=N/2;i+=2){
      w[i+1] = y[i] - y[N-i]; // a values
      printf("a value w[%d] = %lf - %lf\n", i, y[i], y[N-i]);
    }
    // now call FastSN and FastTN recursively - need to ensure that the correct part of w is used!
    printf("FastSN calling FastSN with N = %d\n", N/2);
    FastSN(x,w,y,S,N/2,skip*2);
    printf("FastSN calling FastTN with N = %d\n", N/2);
    FastTN(x-skip,w-skip,y-skip,S,N/2,skip*2);
  } else {
    // this happens if we can go no further - our initial N was not a power of 2
    for(i=1;i<=N;i++){
      for(j=1;j<=N;j++){
	x[i*skip] = sin(i*j*M_PI/N)*y[j];
      }
    }
  }
}

int FastTN(double *x, double *y, double *w, double *S, int N, int skip){
  int i,j;
  double y1,y2;
  if(N==2){
    // don't factor down any further - just do the multiplication
    printf("Base case for FastTN\n");
    y1 = y[skip];
    y2 = y[2*skip];
    printf("y[%d] = %lf\ty[%d] = %lf\n", skip, y[skip], 2*skip, y[2*skip]);
    x[skip] = 0.5*sqrt(2)*y1 + y2;
    x[2*skip] = 0.5*sqrt(2)*y1 - y2;
    printf("x[%d] = %lf\tx[%d] = %lf\n", skip, x[skip], 2*skip, x[2*skip]);
    /*
    // This is the old version, delete once it's working
    printf("Base case for FastTN\n");
    printf("y[%d] = %lf\ty[%d] = %lf\n",skip, y[skip], 2*skip, y[2*skip]);
    x[skip] = 0.5*sqrt(2)*y[skip]+y[2*skip];
    printf("x[%d] = %lf + %lf\n", skip, 0.5*sqrt(2)*y[skip], y[2*skip]);
    x[2*skip] = 0.5*sqrt(2)*y[skip]-y[2*skip];
    printf("x[%d] = %lf + %lf\n", 2*skip, 0.5*sqrt(2)*y[skip], y[2*skip]);
    printf("x[%d] = %lf\n", 2*skip, x[2*skip]);
    //printf("x[%d] = %lf\tx[%d] = %lf\n", skip, x[skip], 2*skip, x[2*skip]);
    */
    return(0);
  } else if (N==1) {
    // the base case for recursion - this shouldn't happen with powers of 2
    x[skip] = y[1];
    return(0);
  } else if (N%2==0) {
    // the recursive case
    // do FastTN on the even numbers - note reversal of w & y
    printf("FastTN calling FastTN with N = %d\n", N/2);
    FastTN(w,y,w,S,N/2,skip*2);
    // do FastUN on the odd numbers - reversal of w & y here as well
    printf("FastTN calling FastUN with N = %d\n", N/2);
    FastUN(w-skip,y-skip,w-skip,S,N/2,skip*2);
    // add the z's back together from the work array
    printf("Work array:\n");
    displayVector(w,N);
    for(i=1;i<=N/2;i++){
      x[i] = w[(2*i)-1] + w[2*i];
      x[N+1-i] = w[(2*i)-1] - w[2*i];
    }
  } else {
    // we can go no further - initial N was not a power of 2
    // just brute-force multiply
    SlowTN(x,y,w,S,N,skip);
  }
  return(0);
}

int FastUN(double *x, double *y, double *w, double *S, int N, int skip){
  int i,j;
  if(N==2){
    // don't factor down any further - multiply - can SFactors help here?
    printf("Base case for FastUN\n");
    printf("y[%d] = %lf\ty[%d] = %lf\n",skip, y[skip], 2*skip, y[2*skip]);
    x[skip] = 0.5*(sqrt(2-sqrt(2)))*y[skip] + 0.5*(sqrt(2+sqrt(2)))*y[2*skip];
    x[2*skip] = 0.5*(sqrt(2+sqrt(2)))*y[skip] - 0.5*sqrt(2-sqrt(2))*y[2*skip];
    printf("x[%d] = %lf\tx[%d] = %lf\n", skip, x[skip], 2*skip, x[2*skip]);
    return(0);
  } else if (N==1) {
    // recursion base case
    x[skip] = 0.5*sqrt(2)*y[1];
    return(0);
  } else if (N%2==0) {
    // recursive case
    // preprocess to u and v - store in work array - do these need to be skip?
    
    // this is just to test U4 - delete it!
    w[1] = y[3] - y[2];
    w[2] = y[2] + y[3];
    w[3] = y[1];
    w[4] = y[4];

    /*
    for(i=1;i<N;i+=2){
      w[i] = y[N+1-2*i]-y[N-2*i]; // store u in odd numbers
      printf("w[%d] = %lf\n", i, w[i]);
    }
    w[N/2] = y[1];
    printf("w[%d] = %lf\n", N/2, w[N/2]);

    for(i=2;i<N;i+=2){
      w[i] = y[2*i] + y[2*i+1]; // store v in even numbers
      printf("w[%d] = %lf\n", i, w[i]);
    }
    w[N] = y[N];
    printf("w[%d] = %lf\n", N, w[N]);
    */

    printf("work array:\n");
    displayVector(w,N);
    // do FastTN on u and v for a and b
    printf("FastUN calling FastTN with N = %d\n", N/2);
    FastTN(w,w,x,S,N/2,skip*2);
    printf("FastUN calling FastTN with N = %d\n", N/2);
    FastTN(w-skip,w-skip,x-skip,S,N/2,skip*2);

    printf("work array before reassembling:\n");
    displayVector(w,N);
    // reassemble into x
    for(i=1;i<=N/2;i++){
      if(i%2==0){ // even, so sign factors are negative
      x[i*skip] = -1.0*sin(((2.0*(double)i-1)*M_PI)/(4.0*(double)N))*w[i*skip] + sin(((2.0*(double)N+1-2.0*(double)i)*M_PI)/(4.0*(double)N))*w[(i+1)*skip];
      x[N+1-(i*skip)] = -1.0*sin(((2.0*(double)N+1-2.0*(double)i)*M_PI)/(4.0*(double)N))*w[i*skip] - sin(((2.0*(double)i-1)*M_PI)/(4.0*(double)N))*w[(i+1)*skip];
      } else if (i%2==1) { // odd, so sign factors are positive
	x[i*skip] = sin(((2.0*(double)i-1)*M_PI)/(4.0*(double)N))*w[i*skip] + sin(((2.0*(double)N+1-2.0*(double)i)*M_PI)/(4.0*(double)N))*w[(i+1)*skip];
      x[N+1-(i*skip)] = sin(((2.0*(double)N+1-2.0*(double)i)*M_PI)/(4.0*(double)N))*w[i*skip] - sin(((2.0*(double)i-1)*M_PI)/(4.0*(double)N))*w[(i+1)*skip];
      }

    }
  } else {
    // just brute-force multiply
    SlowUN(x,y,w,S,N,skip);
  }
}

int SlowSN(double *x, double *y, double *w, double *S, int N, int skip){
  int i,j;
  double **SN;

  SN = make_matrix(N-1, N-1);
  for(i=1;i<=N-1;i++){
    for(j=1;j<=N-1;j++){
      SN[i][j] = sin(((double)i*(double)j*M_PI)/(double)N);
    }
  }

  x = mv_multiply(SN, y, N-1, N-1, N-1);
  /*
  printf("SN matrix:\n");
  displayMatrix(SN,N-1);
  printf("y:\n");
  displayVector(y,N-1);
  printf("x:\n");
  */
  displayVector(x,N-1);
  return(0);
}

int SlowTN(double *x, double *y, double *w, double *S, int N, int skip){
  int i,j;
  double **TN;

  TN = make_matrix(N,N);
  for(i=1;i<=N;i++){
    for(j=1;j<=N;j++){
      TN[i][j] = sin(((2.0*(double)i-1)*(double)j*M_PI)/(2.0*(double)N));
    }
  }

  x = mv_multiply(TN,y,N,N,N);
  /*
  printf("TN matrix:\n");
  displayMatrix(TN,N);
  printf("y:\n");
  displayVector(y,N);
  */
  printf("x:\n");
  displayVector(x,N);
  return(0);
}

int SlowUN(double *x, double *y, double *w, double *S, int N, int skip){
  int i,j;
  double **UN;

  UN = make_matrix(N,N);
  for(i=1;i<=N;i++){
    for(j=1;j<=N;j++){
      UN[i][j] = sin(((2.0*(double)i-1)*(2.0*(double)j-1)*M_PI)/(4.0*(double)N));
    }
  }

  x = mv_multiply(UN,y,N,N,N);
  /*
  printf("UN matrix:\n");
  displayMatrix(UN,N);
  printf("y:\n");
  displayVector(y,N);
  */
  printf("x:\n");
  displayVector(x,N);

  return(0);
}

double **make_matrix(int NR, int NC){ // from lecture notes
	double **M;
	int i, j, n;
	M = (double **)malloc((NR+1)*sizeof(double*));
	M[0] = (double *)malloc((NR+1)*(NC+1)*sizeof(double));
	for(n = 1; n <= NR; n++) M[n] = M[n-1] + NC+1;
	for(i = 0; i <= NR; i++){
		for(j = 0; j <= NC; j++){
		  M[i][j] = (double)i;
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

double *mv_multiply(double **M, double *V, int m, int n, int k){
  double *ans;
  int i,j;

  //check dimensions are correct
  if(n!=k){
    printf("matrix dimensions do not agree\n");
    exit(0);
  }

  ans = (double*)malloc(n*sizeof(double));
  for(i=1;i<=m;i++){
    for(j=1;j<=n;j++){
      ans[i] += M[i][j]*V[j];
    }
  }
  return(ans);
}


void displayMatrix(double ** M, int len){

	int i, j;
	for(i = 1; i <= len; i++){
		for(j = 1; j <= len; j++){
			printf("%3.3g\t", M[i][j]);
		}
	printf("\n");
	}
}

void displayVector(double *V, int len){
  int i;

  for(i=1;i<=len;i++){
    printf("%5.5g\n", V[i]);
  }
}
