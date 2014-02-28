#include<stdio.h>
#include<stdlib.h>
#include"header.h"

#define double long double

int main(void){
	int n_recurr, i;
	int I1, I2, I3;
	double A, B;
	double *x;
	n_recurr = 25; // set in question
	printf("Enter integers I1, I2, I3:\n");
	scanf("%d %d %d", &I1, &I2, &I3);
	A = (double)I1 + 1.0;
	B = -1.0*(double)I1;
	x = (double *)malloc((n_recurr+1)*sizeof(double));
	x[0] = (double)I2/(double)I3;
	x[1] = x[0];
	printf("x[0] = %20.15LG\nx[1] = %20.15LG\n", x[0], x[1]);
	for(i = 2; i <= n_recurr; i++){
		x[i] = A*x[i-1] + B*x[i-2];
	printf("x[%d] = %20.15LG\n", i, x[i]);
	}
	free(x);
}
