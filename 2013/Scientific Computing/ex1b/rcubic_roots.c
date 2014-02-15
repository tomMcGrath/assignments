#include<math.h>
#include<stdio.h>
#include"header.h"

int rcubic_roots(double a2, double a1, double a0, double *r1, double *r2, double *r3){
	double q, r, q3_r3;
	q = calcQ(a2, a1);
	printf("q: %lf\n", q);
	r = calcR(a2, a1, a0);
	printf("r: %lf\n", r);
	q3_r3 = q*q*q - r*r*r;
	printf("q3_r3: %lf\n", q3_r3);	
	if (q3_r3 < 0){
		//handle 2 complex roots
	} else if (q3_r3 >= 0){
		// handle 3 real roots
	}
}	

int calcQ(double a2, double a1){
	double qVal;
	qVal = (a2*a2 - 3.*a1)/9.;
	return(qVal);
}

int calcR(double a2, double a1, double a0){
	double rVal;
	rVal = (2.*a2*a2*a2 - 9.*a1*a2 + 27.*a0)/54.;
	return(rVal);
}
