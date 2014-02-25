#include<stdio.h>
#include<math.h>
#include<complex.h>
#include"header.h"

int main(void) {
	double args[4];
	double cr_args[3];
	double cr_r[3];
	double r[4];
	double lr_r[1];
	int rVal;
	args[3] = 5.0;
	args[2] = -39.0;
	args[1] = -47.0;
	args[0] = 210.0;	
	rVal = rquartic_roots(args, r);
	printf("r1 = %10.5g\nr2 = %10.5g\nr3 = %10.5g\nr4 = %10.5g\n", r[0], r[1], r[2], r[3]);
	printf("rVal = %d\n", rVal);
}

