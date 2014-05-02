#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"McGrath.h"

int main(void){
  int i,j,k,N, NMIN, NMAX;
  double time, TMAX, xMax, yMax, zMax, psiMax;
  double dx;
  double ***rho, ***psi;
  double *w, *S, *temp1, *temp2;
  //double **output;

  NMIN = 8;
  NMAX = 512;
  TMAX = 600;

  // initialise tensors
  //output = make_matrix(NMAX,NMAX);
  rho = make_tensor(NMAX,NMAX,NMAX);
  psi = make_tensor(NMAX,NMAX,NMAX);
  temp1 = (double*)malloc(NMAX*sizeof(double));
  temp2 = (double*)malloc(NMAX*sizeof(double));
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
  printf("%10s\t%10s\t%10s\t%10s\t%10s\t%10s\n", "N", "Psi Max", "X Max", "Y Max", "Z Max", "Time");

  for(N=NMIN;N<=NMAX;N*=2){
    dx = 1.0/(double)N;
    //printf("dx = %lf\n", dx);

    // clear arrays
    for(i=1;i<N;i++){
      for(j=1;j<N;j++){
	for(k=1;k<N;k++){
	  rho[i][j][k] = 0.0;
	  psi[i][j][k] = 0.0;
	}
      }
    }

    time = 0.0;
    timer(-1);

    // define rho
    defineMQ(rho,N);


    //printf("transforming x\n");
    for(i=1;i<N;i++){
      for(j=1;j<N;j++){
	for(k=1;k<N;k++){
	  temp1[k] = rho[i][j][k];
	}
	FastSN(temp2, temp1, w, S, N, 1);
	for(k=1;k<N;k++){
	  rho[i][j][k] = temp2[k];
	}
      }
    }

    //printf("transforming y\n");
    for(i=1;i<N;i++){
      for(j=1;j<N;j++){
	for(k=1;k<N;k++){
	  temp1[k] = rho[i][k][j];
	}
	FastSN(temp2,temp1,w,S,N,1);
	for(k=1;k<N;k++){
	  rho[i][k][j] = temp2[k];
	}
      }
    }

    //printf("transforming z\n");
    for(i=1;i<N;i++){
      for(j=1;j<N;j++){
	for(k=1;k<N;k++){
	  temp1[k] = rho[k][i][j];
	}
	FastSN(temp2,temp1,w,S,N,1);
	for(k=1;k<N;k++){
	  rho[k][i][j] = temp2[k];
	}
      }
    }

    //printf("calculating psi from rho\n");
    calcPsiGood3D(rho,psi,N);

    //printf("transforming z back\n");
    for(i=1;i<N;i++){
      for(j=1;j<N;j++){
	for(k=1;k<N;k++){
	  temp1[k] = psi[k][i][j];
	}
	FastSN(temp2,temp1,w,S,N,1);
	for(k=1;k<N;k++){
	  psi[k][i][j] = temp2[k];
	}
      }
    }

    //printf("transforming y back\n");
    for(i=1;i<N;i++){
      for(j=1;j<N;j++){
	for(k=1;k<N;k++){
	  temp1[k] = psi[i][k][j];
	}
	FastSN(temp2,temp1,w,S,N,1);
	for(k=1;k<N;k++){
	  psi[i][k][j] = temp2[k];
	}
      }
    }

    //printf("transforming x back\n");
    for(i=1;i<N;i++){
      for(j=1;j<N;j++){
	for(k=1;k<N;k++){
	  temp1[k] = psi[i][j][k];
	}
	FastSN(temp2, temp1, w, S, N, 1);
	for(k=1;k<N;k++){
	  psi[i][j][k] = temp2[k];
	}
      }
    }

    time = timer(1);
    psiMax = amax3D(psi, N-1);
    xMax = dx*xMax3D(psi, N-1);
    yMax = dx*yMax3D(psi, N-1);
    zMax = dx*zMax3D(psi, N-1);

    printf("%10d\t%10.8g\t%10.8g\t%10.8g\t%10.8g\t%10.8g\n", N, psiMax, xMax, yMax, zMax, time);

    if(time > TMAX){
      break;
    }
    
    /*
    for(i=1;i<N;i++){
      for(j=1;j<N;j++){
	output[i][j] = psi[i][j][N/4];
      }
    }
    writeMatrix(output, N, "MQii.txt");
    */
    
  }
}
