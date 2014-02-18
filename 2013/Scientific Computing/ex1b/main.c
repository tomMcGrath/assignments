#include<stdio.h>
#include<math.h>
#include<complex.h>
#include"header.h"

int main(void) {
	double t1, t2, t3;
	double complex c_a2, c_a1, c_a0, c_t1, c_t2, c_t3;
	double a2, a1, a0;
	int rVal;
	double test;
	printf("Name: <Tom McGrath>\n");
	printf("CID: <00898098>, LIBRARY NO: <0246656362>\n");
	printf("Email Address: <t.mcgrath13@imperial.ac.uk>\n");
	printf("Course Code: <M5SC>\n");
	c_a2 = 1.0 + 1.0*I;
	c_a1 = 1.0 - 1.0*I;
	c_a0 = 2.0 + 0.0*I;
	rVal = complex_cubic(c_a2, c_a1, c_a0, &c_t1, &c_t2, &c_t3);
	printf("r1 = %g + %gi\nr2 = %g + %gi\nr3 = %g + %gi\n", creal(c_t1), cimag(c_t1), creal(c_t2), cimag(c_t2), creal(c_t3), cimag(c_t3));
	printf("Return value: %d\n", rVal);	
	printf("Enter reduced cubic root coeffs a2 a1 a0\n");
	scanf("%lf %lf %lf", &a2, &a1, &a0);
	rVal = rcubic_roots(a2, a1, a0, &t1, &t2, &t3);
	printf("r1 = %g\nr2 = %g\nr3 = %g\n", t1, t2, t3);
	printf("Return value: %d\n", rVal);
	printf("Enter quadratic root coeffs a2 a1 a0\n");
	scanf("%lf %lf %lf", &a2, &a1, &a0);
	rVal = quad_roots(a2,a1,a0,&t1,&t2);
	printf("r1 = %g\nr2 = %g\n", t1, t2);
	printf("Return value: %d\n", rVal);
	printf("Enter linear root coeffs a1 a0\n");
	scanf("%lf %lf", &a1, &a0);
	rVal = lin_root(a1, a0, &t1);
	printf("r = %g\n", t1);
	printf("Return value: %d\n", rVal);
}
