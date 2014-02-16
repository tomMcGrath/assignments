#include<math.h>
#include<stdio.h>
#include"header.h"

int rcubic_roots(double a2, double a1, double a0, double *r1, double *r2, double *r3){
	double q, r, q3_r2;
	double root_1, root_2, root_3;
	double b1, b0;
	q = calcQ(a2, a1);
	printf("q: %lf\n", q);
	r = calcR(a2, a1, a0);
	printf("r: %lf\n", r);
	q3_r2 = q*q*q - r*r;
	printf("q3_r2: %lf\n", q3_r2);
	if (q3_r2 < 0){
		//handle 2 complex roots
		printf("sqrt(-q3_r2) = %g\n", sqrt(-q3_r2));
		printf("sqrt(-q3_r2) + absval(r) = %g\n", sqrt(-q3_r2) + absval(r));
		printf("pow(sqrt(-q3_r2) + absval(r), 1.0/3.0) = %g\n", pow(sqrt(-q3_r2) + absval(r), 1.0/3.0));
		root_1 = (-absval(r)/r)*(pow(sqrt(-q3_r2) + absval(r), 1.0/3.0) + q/(pow(sqrt(r*r - q*q*q) + absval(r), 1.0/3.0))) - a2/3.0;
		printf("First root: %g\n", root_1);
		b1 = a2 + root_1;
		b0 = -1.0*a0/root_1;
		printf("b1 = %g\nb0 = %g\n", b1, b0);
		quad_roots(1.0, b1, b0, &root_2, &root_3);
	} else if (q3_r2 >= 0){
		// handle 3 real roots
		printf("pow(q*q*q, 1.0/2.0) = %g\n", pow(q*q*q, 1.0/2.0));
		printf("acos(r/pow(q*q*q, 1.0/2.0)) = %g\n", acos(r/pow(q*q*q, 1.0/2.0)));
		root_1 = -2.0*sqrt(q)*cos((acos(r/pow(q*q*q, 1.0/2.0)))/3.0) - a2/3.0;
		printf("First root: %g\n", root_1);
		b1 = a2 + root_1;
		b0 = -1.0*a0/root_1;
		printf("b1 = %g\n b0 = %g\n", b1, b0);
		quad_roots(1.0, b1, b0, &root_2, &root_3);		
	}
	*r1 = root_1;
	*r2 = root_2;
	*r3 = root_3;
}	

double calcQ(double a2, double a1){
	double qVal;
	qVal = (a2*a2 - 3.*a1)/9.;
	return(qVal);
}

double calcR(double a2, double a1, double a0){
	double rVal;
	rVal = (2.*a2*a2*a2 - 9.*a1*a2 + 27.*a0)/54.;
	return(rVal);
}