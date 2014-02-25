#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include"header.h"

int rquartic_roots(double *a, double *roots){
	double b[3];
	double c_roots[3];
	double qd_roots[2];
	double p[2];
	double q[2];
	double r;
	int rVal, rVal2;

	// calculate coefficients of reduced cubic
	b[2] = -1.0*a[2];
	b[1] = a[1]*a[3]-4.0*a[0];
	b[0] = 4.0*a[0]*a[2] - a[1]*a[1] - a[0]*a[3]*a[3];

	rVal = rcubic_roots(b, c_roots);
	printf("b2 = %10.5g\tb1 = %10.5g\tb0 = %10.5g\n", b[2], b[1], b[0]);
	printf("c_roots[2] = %10.5g\tc_roots[1] = %10.5g\tc_roots[0] = %10.5g\n", c_roots[2], c_roots[1], c_roots[0]);
	printf("rVal = %d\n", rVal);
	
	if(rVal == 3){
		// choose largest root of rcubic_roots
		r = amax(c_roots, 3);
	} else {
		r = c_roots[0];
	}

	p[1] = (a[3]/2.0) + sqrt((a[3]*a[3]/4.0) + r - a[2]);
	p[0] = (r/2.0) + sqrt((r*r/4.0)-a[0]);
	q[1] = (a[3]/2.0) - sqrt((a[3]*a[3]/4.0) + r - a[2]);
	q[0] = (r/2.0) - sqrt((r*r/4.0)-a[0]);

	if(p[1]*q[0] + p[0]*q[1] == a[1]){
		// {+,+},{-,-} case
		// {+,+}
		b[2] = 1;
		b[1] = (a[3]/2.0) + sqrt((a[3]*a[3]/4.0) + r - a[2]);
		b[0] = (r/2.0) + sqrt((r*r/4.0)-a[0]);
		rVal = quad_roots(b,qd_roots);
		roots[0] = qd_roots[0];
		roots[1] = qd_roots[1];
		// {-,-}
		b[2] = 1;
		b[1] = (a[3]/2.0) - sqrt((a[3]*a[3]/4.0) + r - a[2]);
		b[0] = (r/2.0) - sqrt((r*r/4.0)-a[0]);
		rVal2 = quad_roots(b,qd_roots);
		roots[2] = qd_roots[0];
		roots[3] = qd_roots[1];
		if(rVal == 2 && rVal2 == 2){
			qsort(roots, 4, sizeof(double), compare_dbl);
		} else {
			qsort(roots, 4, sizeof(double), compare_dbl); // change this!
		}
	} else {
		// {+.-},{-,+} case
		// {+,-}
		b[2] = 1;
		b[1] = (a[3]/2.0) + sqrt((a[3]*a[3]/4.0) + r - a[2]);
		b[0] = (r/2.0) - sqrt((r*r/4.0)-a[0]);
		rVal = quad_roots(b,qd_roots);
		roots[0] = qd_roots[0];
		roots[1] = qd_roots[1];
		// {-,+}
		b[2] = 1;
		b[1] = (a[3]/2.0) - sqrt((a[3]*a[3]/4.0) + r - a[2]);
		b[0] = (r/2.0) + sqrt((r*r/4.0)-a[0]);
		rVal2 = quad_roots(b,qd_roots);
		roots[2] = qd_roots[0];
		roots[3] = qd_roots[1];
		if(rVal == 2 && rVal2 == 2){
			qsort(roots, 4, sizeof(double), compare_dbl);
		} else {
			qsort(roots, 4, sizeof(double), compare_dbl); // change this!
		}
	}
}
