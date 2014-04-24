#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(void){
  int i,N;
  double *x;

  N = 8;

  x = (double*)malloc(N*sizeof(double));
  for(i=0;i<=N;i++){
    printf("x[%d] = %lf\n", i, x[i]);
  }
  printf("---\n");
  test(x, N);
  for(i=0;i<=N;i++){
    printf("x[%d] = %lf\n", i, x[i]);
  }

}

int test(double *x, int N){
  int i;
  for(i=0;i<=N;i++){
    x[i] = i;
  }
}
