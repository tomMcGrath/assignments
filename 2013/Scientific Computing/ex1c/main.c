#include<stdio.h>
#include<math.h>
#include<complex.h>
#include"header.h"

int main(void) {
	double args[3];
	double r[3];
	double lr_r[1];
	args[0] = 1.0;
	args[1] = 1.0;
	args[2] = 1.0;
	rcubic_roots(args, r);
	printf("r1 = %10.5g\nr2=%10.5g\nr3 = %10.5g\n", r[0], r[1], r[2]);
}

