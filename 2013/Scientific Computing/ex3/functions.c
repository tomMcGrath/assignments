#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"McGrath.h"

int FastSN(double *x, double *y, double *w, double *S, int N, int skip){
  int i,j;

  if(N==2){
    // the base case for recursion
    //printf("Base case for FastSN\n");
    x[skip] = y[skip]; // should this be skip or 1?
    //displayXYW(x,y,w,(N*skip)-1);
    return(0);
  } else if(N%2==0) {
    // recursive block
    // store s and a in the work array

    for(i=1;i<=N/2;i++){
      if(i!=N/2){
	//printf("i = %d\n", i);
	w[(2*i*skip)-skip] = y[i*skip] + y[(N-i)*skip]; // s components
	w[2*i*skip] = y[i*skip] - y[(N-i)*skip]; // a components

	//printf("w[%d] = y[%d] + y[%d] = %lf + %lf = %lf\n", (2*i*skip)-1, i*skip, (N-i)*skip, y[i*skip], y[(N-i)*skip],w[(2*i*skip)-skip]);
	//printf("w[%d] = y[%d] - y[%d] = %lf - %lf = %lf\n", 2*i*skip, i*skip, (N-i)*skip, y[i*skip], y[(N-i)*skip],w[(2*i*skip)]);
      }
    }

    w[(N-1)*skip] = y[(N/2)*skip];
    //printf("w[%d] = y[%d] = %lf\n", (N-1)*skip, (N/2)*skip, y[(N/2)*skip]);

    //displayXYW(x,y,w,(N*skip)-1);

    // now call FastSN and FastTN recursively - need to ensure that the correct part of w is used so offset arrays by skip
    //printf("FastSN calling FastSN with N = %d\n", N/2);
    FastSN(x,w,y,S,N/2,skip*2);
    //printf("FastSN calling FastTN with N = %d\n", N/2);
    FastTN(x-skip,w-skip,y-skip,S,N/2,skip*2);
    //printf("vectors after recursion in FastSN with N=%d\n", N);
    //displayXYW(x,y,w,(N*skip)-1);
  } else {
    // this happens if we can go no further - our initial N was not a power of 2
    return(-1);
  }
}

int FastTN(double *x, double *y, double *w, double *S, int N, int skip){
  int i,j;
  double y1,y2;
  if(N==2){
    // don't factor down any further - just do the multiplication
    //printf("Base case for FastTN\n");
    //displayXYW(x+skip,y+skip,w+skip,(N*skip)-1);
    y1 = S[1]*y[skip]; // precalculating to save time
    y2 = y[2*skip];
    //printf("y[%d] = %lf\ty[%d] = %lf\n", skip, y[skip], 2*skip, y[2*skip]);
    x[skip] = y1 + y2;
    x[2*skip] = y1 - y2;
    //printf("x[%d] = %lf\tx[%d] = %lf\n", skip, x[skip], 2*skip, x[2*skip]);
    //printf("arrays after base case with N = %d\n", N);
    //displayXYW(x+skip,y+skip,w+skip,(N*skip)-1);
    return(0);
  } else if (N==1) {
    // the base case for recursion - this shouldn't happen with powers of 2
    x[skip] = y[1];
    return(0);
  } else if (N%2==0) {
    // the recursive case
    // do FastTN on the even numbers - note reversal of w & y
    // all this is debug printing
    //printf("Recursive step in FastTN with N = %d\n", N);
    //displayXYW(x+skip,y+skip,w+skip,(N*skip)-1);


    // the work goes on here
    //printf("FastTN calling FastTN with N = %d\n", N/2);
    FastTN(w,y,x,S,N/2,skip*2);
    // do FastUN on the odd numbers - reversal of w & x here as well
    //printf("FastTN calling FastUN with N = %d\n", N/2);
    FastUN(w-skip,y-skip,x-skip,S,N/2,skip*2);

    // add the z's back together from the work array
    //printf("arrays before reassembly\n");
    //displayXYW(x+skip,y+skip,w+skip,(N*skip)-1);

    // reassemble arrays
    for(i=1;i<=N/2;i++){
      x[i*skip] = w[(2*i-1)*skip] + w[2*i*skip];
      x[((N+1-i)*skip)] = w[(2*i-1)*skip] - w[2*i*skip];
    }

    //printf("arrays after reassembly\n");
    //displayXYW(x+skip,y+skip,w+skip,(N*skip)-1);
  } else {
    // we can go no further - initial N was not a power of 2
    // just brute-force multiply
    return(-1);
  }
  return(0);
}

int FastUN(double *x, double *y, double *w, double *S, int N, int skip){
  int i,j;
  if(N==2){
    // calculate N=2 case to save time
    //printf("Base case for FastUN\n");
    //printf("Arrays before base case\n");
    //displayXYW(x+skip, y+skip, w+skip, (N*skip)-1);

    x[skip] = S[2]*y[skip] + S[3]*y[2*skip];
    x[2*skip] = S[3]*y[skip] - S[2]*y[2*skip];

    //printf("Arrays after base case\n");
    //displayXYW(x+skip, y+skip, w+skip, (N*skip)-1);

  } else if (N==1) {
    // recursion base case
    x[skip] = S[1]*y[skip];
  } else if (N%2==0) {
    // recursive step
    // preprocess u and v into work array
    for(i=1;i<N/2;i++){
      w[(2*i-1)*skip] = y[(N+1-2*i)*skip] - y[(N-2*i)*skip];
      w[2*i*skip] = y[2*i*skip] + y[(2*i+1)*skip];
     //printf("w[%d] = y[%d] - y[%d] = %lf\n", (2*i-1)*skip, (N+1-2*i)*skip, (N-2*i)*skip, w[(2*i-1)*skip]);
     //printf("w[%d] = y[%d] + y[%d] = %lf\n", 2*i*skip, 2*i*skip, (2*i+1)*skip, w[2*i*skip]);
    }
    w[(N-1)*skip] = y[skip];
    w[N*skip] = y[N*skip];
    //printf("w[%d] = y[%d] = %lf\n", (N-1)*skip, skip, w[(N-1)*skip]);
    //printf("w[%d] = y[%d] = %lf\n", N*skip, N*skip, w[N*skip]);

    // call FastTN twice
    FastTN(y,w,x,S,N/2,skip*2);
    FastTN(y-skip,w-skip,x-skip,S,N/2,skip*2);

    //printf("arrays after T%d recursion\n", N/2);
    //displayXYW(x+skip,y+skip,w+skip,(N*skip)-1);

    // reassemble after recursive step
    for(i=1;i<=N/2;i++){
      if(i%2==1){ // odd => positive sign
	x[i*skip] = S[N+i-1]*y[(2*i-1)*skip] + S[(2*N)-i]*y[2*i*skip];
	x[(N+1-i)*skip] = S[(2*N)-i]*y[(2*i-1)*skip] - S[N+i-1]*y[2*i*skip];
      } else { // even => negative sign
	x[i*skip] = -1.0*S[N+i-1]*y[(2*i-1)*skip] + S[(2*N)-i]*y[2*i*skip];
	x[(N+1-i)*skip] = -1.0*S[(2*N)-i]*y[(2*i-1)*skip] - S[N+i-1]*y[2*i*skip];
      }
    }
  } else {
    // cannot calculate any further
    return(-1);
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
  //printf("SN matrix:\n");
  displayMatrix(SN,N-1);
  //printf("y:\n");
  //displayVector(y,N-1);
  //printf("x:\n");
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
  //printf("TN matrix:\n");
  displayMatrix(TN,N);
  //printf("y:\n");
  //displayVector(y,N);
  */
  //printf("x:\n");
  //displayVector(x,N);
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
  //printf("UN matrix:\n");
  displayMatrix(UN,N);
  //printf("y:\n");
  //displayVector(y,N);
  */
  //printf("x:\n");
  //displayVector(x,N);

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
    //printf("matrix dimensions do not agree\n");
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
    //printf("matrix dimensions do not agree\n");
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

void displayXYW(double *x, double *y, double *w, int N){
  int i;

  printf("Arrays in order x,y,w\n");
  // segfaults when called from a skip-adjusted context because indexing is off by skip
  for(i=1;i<=N;i++){
    printf("[%lf]\t[%lf]\t[%lf]\n", x[i], y[i], w[i]);
  }
}

double* SFactors(int N){
  static int maxN;
  static double *factors;
  double *rVals, *tmp;
  int i,j,k;

  //printf("maxN = %d\n", maxN);

  if(maxN>=N){
    //printf("returning from memory\n");
    rVals = (double*)malloc(((N/2)-1)*sizeof(double));
    for(i=0;i<=((N/2)-1);i++){
      rVals[i] = factors[i];
    }
    return(rVals);
  } else if (maxN < N){
    // could improve by only calculating new values
    //printf("calculating extra factors\n");
    factors = (double*)realloc(factors, ((N/2)-1)*sizeof(double));
    k=1;
    for(i=4;i<=N;i*=2){
      for(j=1;j<=((i/2)-1);j+=2){
	factors[k]=sin(M_PI*j/i);
	k++;
      }
    }
    maxN = N;
    return(factors);
  }

}

double signof(int n){
  // returns (-1)^n for nonnegative n
  if(n < 0){
    return(-10.0); // error
  } else if (n%2==0){
    return(1.0); // even n case => sign is positive
  } else {
    return(-1.0); // odd n case => sign is negative
  }
}

double timer(int T){ // from the lecture notes
  static double then = 0.0;
  double now, diff;

  now=(double)clock()/(double)CLOCKS_PER_SEC;
  diff=now-then;
  if(T<0) then=now;

  return(diff);
}

int defineQ4(double *rho,int N){
  int i;
  double dx;

  dx = 1.0/(double)N;

  for(i=1;i<N;i++){
    if (i*dx < 0.25) {
      rho[i] = 40.0;
    } else if (i*dx == 0.25) {
      rho[i] = 20.0;
    } else {
      rho[i] = 0.0;
    }
  }
}

int writeVector(double *V, int N, char *path){
  int i;
  FILE *writeFile;

  writeFile = fopen(path,"w");

  for(i=1;i<=N;i++){
    fprintf(writeFile, "%g\n", V[i]);
  }

  fclose(writeFile);
  return(0);
}

int calcPsiBad(double *rho, double *psi, int N){
  // use (4.3) to calculate psi from rho
  int i;
  double dx;

  dx = 1.0/(double)N;
  for(i=1;i<N-1;i++){
    psi[i] = dx*dx*rho[i]/(N*(1.0-cos(((double)i*M_PI)/(double)N)));
  }
}

int calcPsiGood(double *rho, double *psi, int N){
  // use (4.6) to calculate psi from rho
  int i;

  for(i=1;i<N;i++){
    //psi[i] = 2.0*rho[i]/(i*i*M_PI*M_PI*N);
    psi[i] = (1./(i*M_PI))*(1./(i*M_PI))*rho[i]*2.0*(1./(double)N);
  }
}

int defineQ5(double **rho, int N){
  int i,j;
  double dx;

  dx = 1.0/(double)N;

  for(i = 0; i <= N; i++){
    for(j = 0; j <= N; j++){
      if((i*dx < 0.25) && (j*dx < 0.25)){
	rho[i][j] = 100.0;
      } else if (((i*dx == 0.25) && (j*dx < 0.25)) || ((i*dx < 0.25) && (j*dx == 0.25))){
	rho[i][j] = 50;
      } else if ((i*dx == 0.25) && (j*dx == 0.25)){
	rho[i][j] = 25;
      }
    }
  }
}

int calcPsiGood2D(double **rho, double ** psi, int N){
  int i,j;
  
  for(i=1;i<N;i++){
    for(j=1;j<N;j++){
      psi[i][j] = (4.0/((double)N*(double)N))*(rho[i][j]/(((i*i)+(j*j))*M_PI*M_PI));
    }
  }
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

double ***make_tensor(int N1, int N2, int N3){
	double ***T;
	int i;

	T = malloc((N1+1)*sizeof(double**));
	for(i = 0; i <= N1; i++){
		T[i] = (double **)make_matrix(N2, N3);
	}
	return(T);
}

int defineMQ(double ***rho, int N){
  int i,j,k;
  double dx;

  dx = 1.0/(double)N;
  
  for(i=1;i<N;i++){
    for(j=1;j<N;j++){
      for(k=1;k<N;k++){
	if(i*dx<0.25&&j*dx<0.25&&k*dx<0.25){
	  rho[i][j][k] = 200.0;
	} else if((i*dx==0.25&&j*dx<0.25&&k*dx<0.25)||(i*dx<0.25&&j*dx==0.25&&k*dx<0.25)||(i*dx<0.25&&j*dx<0.25&&k*dx==0.25)){
	  rho[i][j][k] = 100.0;
	} else if((i*dx==0.25&&j*dx==0.25&&k*dx<0.25)||(i*dx==0.25&&j*dx<0.25&&k*dx==0.25)||(i*dx<0.25&&j*dx==0.25&&k*dx==0.25)){
	  rho[i][j][k] = 50.0;
	} else if(i*dx==0.25&&j*dx==0.25&&k*dx==0.25){
	  rho[i][j][k] = 25.0;
	}
      }
    }
  }
  
}

int calcPsiGood3D(double ***rho, double ***psi, int N){
  int i,j,k;

  for(i=1;i<N;i++){
    for(j=1;j<N;j++){
      for(k=1;k<N;k++){
	psi[i][j][k] = (8./((double)N*(double)N*(double)N))*(rho[i][j][k]/(((i*i)+(j*j)+(k*k))*M_PI*M_PI*M_PI));
      }
    }
  }
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
	int i, maxI;

	max = M[1];
	for(i=1;i<=len;i++){
		if(M[i] > max){
			maxI = i;
			max = M[i];
		} else {
			continue;
		}
	}

	return(maxI);
}

double amax2D(double **M, int len){
  double max;
  int i,j;

  max = M[1][1];
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
  double  max;
  int i,j;

  max = M[0][0];
  for(i=1;i<=len;i++){
    for(j=1;j<=len;j++){
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

double amax3D(double ***M, int len){
	double max;
	int i, j;

	max = M[1][1][1];
	for(i=1;i<=len;i++){
		for(j=1;j<=len;j++){
			if(amax(M[i][j], len) > max){
				max = amax(M[i][j], len);
			} else {
				continue;
			}
		}
	}
	return(max);
}


double *argamax3D(double ***M, int len, double pos[3]){
	double max;
	int i,j,k;

	max = M[0][0][0];
	for(i=0;i<=len;i++){
		for(j=0;j<=len;j++){
			for(k=0;k<=len;k++){
				if(M[i][j][k] > max){
					max = M[i][j][k];
					pos[0] = i;
					pos[1] = j;
					pos[2] = k;
				} else {
					continue;
				}
			}
		}
	}
	return(pos);
}

int xMax2D(double **M, int len){
  int i,j, maxI;
  double max;

  max = M[0][0];
  for(i=1;i<=len;i++){
    for(j=1;j<=len;j++){
      if(M[i][j] > max){
	max = M[i][j];
	maxI = i;
      } else {
	continue;
      }
    }
  }
  return(maxI);
}

int yMax2D(double **M, int len){
  int i,j, maxJ;
  double max;

  max = M[0][0];
  for(i=1;i<=len;i++){
    for(j=1;j<=len;j++){
      if(M[i][j] > max){
	max = M[i][j];
	maxJ = j;
      } else {
	continue;
      }
    }
  }
  return(maxJ);
}

int xMax3D(double ***M, int len){
  double max;
  int i,j,k, maxI;

  max = M[0][0][0];
  for(i=0;i<=len;i++){
    for(j=0;j<=len;j++){
      for(k=0;k<=len;k++){
	if(M[i][j][k] > max){
	  max = M[i][j][k];
	  maxI = i;
	} else {
	  continue;
	}
      }
    }
  }
  return(maxI);
}

int yMax3D(double ***M, int len){
  double max;
  int i,j,k, maxJ;

  max = M[0][0][0];
  for(i=0;i<=len;i++){
    for(j=0;j<=len;j++){
      for(k=0;k<=len;k++){
	if(M[i][j][k] > max){
	  max = M[i][j][k];
	  maxJ = j;
	} else {
	  continue;
	}
      }
    }
  }
  return(maxJ);
}

int zMax3D(double ***M, int len){
  double max;
  int i,j,k, maxK;

  max = M[0][0][0];
  for(i=0;i<=len;i++){
    for(j=0;j<=len;j++){
      for(k=0;k<=len;k++){
	if(M[i][j][k] > max){
	  max = M[i][j][k];
	  maxK = k;
	} else {
	  continue;
	}
      }
    }
  }
  return(maxK);
}
