#include<stdio.h>
#include<math.h>
#include"header.h"

int rquartic_roots(double *a, double *roots){
	double a3 = a[3];
	double a2 = a[2];
	double a1 = a[1];
	double a0 = a[0];
	double d2, d1, b0;

	// calculate coefficients of reduced cubic
	b2 = -1.0*a2;
	b1 = a1*a3-4.0*a0;
	b0 = 4.0*a0*a2 - a1*a1 - a0*a3*a3;
}
