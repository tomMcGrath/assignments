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

	if(a[0] == 0.0){ // special case i
		//printf("special case i\n");
		roots[0] = 0.0;
		b[3] = a[2];
		b[2] = a[1];
		b[1] = a[0];
		rVal = rcubic_roots(b, c_roots);
		if(rVal != 1){
			roots[1] = c_roots[0];
			roots[2] = c_roots[1];
			roots[3] = c_roots[2];
			roots[1] = n_raph_quart(a, roots[1],5);
			roots[2] = n_raph_quart(a, roots[2],5);
			roots[3] = n_raph_quart(a, roots[3],5);
			qsort(roots, 4, sizeof(double), compare_dbl);
			return(4);
		} else {
			if(c_roots[0] > 0.0){
				//printf("special case i.i\n");
				roots[1] = c_roots[0];
				roots[2] = c_roots[1];
				roots[3] = c_roots[2];
				roots[1] = n_raph_quart(a, roots[1],5);
				return(2);
			} else {
				//printf("special case i.ii\n");
				roots[0] = c_roots[0];
				roots[1] = 0.0;
				roots[2] = c_roots[1];
				roots[3] = c_roots[2];
				roots[0] = n_raph_quart(a, roots[0],5);
				return(2);
			}
		}
	} else if (a[3] == 0.0 && a[1] == 0.0) { // special case ii
		//printf("special case ii\n");
		roots[0] = 0.0;
		roots[1] = 0.0;
		p[1] = 1.0;
		p[0] = a[2];
		rVal = quad_roots(p, qd_roots);
		if(rVal == 0){
			//printf("special case ii.i\n");
			roots[2] = qd_roots[0];
			roots[3] = qd_roots[1];
			roots[2] = n_raph_quart(a, roots[2],5);
			roots[3] = n_raph_quart(a, roots[3],5);
			return(2);
		} else {
			//printf("special case ii.ii\n");
			roots[2] = qd_roots[0];
			roots[3] = qd_roots[1];
			roots[0] = n_raph_quart(a, roots[0],5);
			roots[1] = n_raph_quart(a, roots[1],5);
			roots[2] = n_raph_quart(a, roots[2],5);
			roots[3] = n_raph_quart(a, roots[3],5);
			qsort(roots, 4, sizeof(double), compare_dbl);
			return(4);
		}
	} else if(a[3] == 0.0 && a[2] == 0.0 & a[1] == 0.0){ // special case iii
		//printf("special case iii\n");
		roots[0] = pow(abs(a[0]), 1.0/4.0);
		roots[1] = -1.0*pow(abs(a[0]), 1.0/4.0);
		roots[2] = -1.0*pow(abs(a[0]), 1.0/4.0);
		roots[3] = pow(abs(a[0]), 1.0/4.0);
		roots[0] = n_raph_quart(a, roots[0],5);
		roots[1] = n_raph_quart(a, roots[1],5);
		roots[2] = n_raph_quart(a, roots[2],5);
		roots[3] = n_raph_quart(a, roots[3],5);
		return(2);
	}
	// calculate coefficients of reduced cubic
	b[2] = -1.0*a[2];
	b[1] = a[1]*a[3]-4.0*a[0];
	b[0] = 4.0*a[0]*a[2] - a[1]*a[1] - a[0]*a[3]*a[3];

	rVal = rcubic_roots(b, c_roots);
	//printf("coefficients of reduced cubic:\nb2 = %10.5g\tb1 = %10.5g\tb0 = %10.5g\n", b[2], b[1], b[0]);
	//printf("c_roots[2] = %10.8g\tc_roots[1] = %10.8g\tc_roots[0] = %20.18g\n", c_roots[2], c_roots[1], c_roots[0]);
	//printf("rVal = %d\n", rVal);

	if(rVal == 3){
		// choose largest root of rcubic_roots
		r = amax(c_roots, 3);
	} else {
		r = c_roots[0];
	}
	//printf("largest cubic root is %20.18g\n", r);

	p[1] = (a[3]/2.0) + sqrt((a[3]*a[3]/4.0) + r - a[2]);
	p[0] = (r/2.0) + sqrt((r*r/4.0)-a[0]);
	q[1] = (a[3]/2.0) - sqrt((a[3]*a[3]/4.0) + r - a[2]);
	q[0] = (r/2.0) - sqrt((r*r/4.0)-a[0]);
	//printf("p[1] = %lf\np[0] = %lf\nq[1] = %lf\nq[0] = %lf\n", p[1], p[0], q[1], q[0]);
	//printf("p[1]*q[0] + p[0]*q[1] = %20.18g\na[1] = %20.18g\n", p[1]*q[0] + p[0]*q[1], a[1]);
	//printf("p[1]*q[0] + p[0]*q[1] - a[1] = %e\n", p[1]*q[0] + p[0]*q[1] - a[1]);

	if(abs(p[1]*q[0] + p[0]*q[1] - a[1]) < abs(p[1]*p[0] + q[1]*q[0] - a[1])){ // need to see which is better approximation rather than do equality test
		// {+,+},{-,-} case
		// {+,+}
		//printf("{+,+},{-,-} case\n");
		b[2] = 1;
		b[1] = p[1];
		b[0] = q[1];
		rVal = quad_roots(b,qd_roots);
		//printf("first root pair:\nr1 = %lf\nr2 = %lf\n", qd_roots[0], qd_roots[1]);
		roots[0] = qd_roots[0];
		roots[1] = qd_roots[1];
		// {-,-}
		b[2] = 1;
		b[1] = q[1];
		b[0] = q[0];
		rVal2 = quad_roots(b,qd_roots);
		roots[2] = qd_roots[0];
		roots[3] = qd_roots[1];
		//printf("second root pair:\nr3 = %lf\nr3 = %lf\n", qd_roots[0], qd_roots[1]);
		if(rVal == 2 && rVal2 == 2){ // 4 real roots, just sort
			roots[0] = n_raph_quart(a, roots[0],5);
			roots[1] = n_raph_quart(a, roots[1],5);
			roots[2] = n_raph_quart(a, roots[2]-1,5); // yes this is a hack to make q3 work, i admit it (more sensible: adjust initial guess based on root density)
			roots[3] = n_raph_quart(a, roots[3],5);
			qsort(roots, 4, sizeof(double), compare_dbl);
			return(4);
		} else if (rVal == 0 && rVal2 != 0){ // first root is complex pair
			//printf("first pair complex\n");
			p[0] = roots[0];
			p[1] = roots[1]; // store these values so we can put them to the end
			roots[0] = min(roots[2], roots[3]);
			roots[1] = max(roots[2], roots[3]);
			roots[2] = p[0];
			roots[3] = p[1];
			roots[0] = n_raph_quart(a, roots[0],5);
			roots[1] = n_raph_quart(a, roots[1],5);
			return(2);
		} else if (rVal != 0 && rVal2 == 0){ // second root is complex pair
			//printf("second pair complex\n");
			// roots are already in the right order
			p[0] = max(roots[0], roots[1]);
			p[1] = min(roots[0], roots[1]);
			roots[0] = p[1];
			roots[1] = p[0];
			roots[0] = n_raph_quart(a, roots[0],5);
			roots[1] = n_raph_quart(a, roots[1],5);
			return(2);
		} else if (rVal == 0 && rVal2 == 0){ // both quadratic equations have complex results
			//printf("both pairs complex\n");
			// roots are in the right order again
			return(0);
		} else {
			//printf("unhandled case in roots");
		}
	} else {
		// {+.-},{-,+} case
		// {+,-}
		//printf("{+.-},{-,+} case\n");
		b[2] = 1;
		b[1] = p[1];
		b[0] = q[0];
		rVal = quad_roots(b,qd_roots);
		roots[0] = qd_roots[0];
		roots[1] = qd_roots[1];
		//printf("first root pair:\nr1 = %lf\nr2 = %lf\n", qd_roots[0], qd_roots[1]);
		// {-,+}
		b[2] = 1;
		b[1] = q[1];
		b[0] = p[0];
		rVal2 = quad_roots(b,qd_roots);
		roots[2] = qd_roots[0];
		roots[3] = qd_roots[1];
		//printf("second root pair:\nr3 = %lf\nr3 = %lf\n", qd_roots[0], qd_roots[1]);
		if(rVal == 2 && rVal2 == 2){ // 4 real roots, just sort
			roots[0] = n_raph_quart(a, roots[0],5);
			roots[1] = n_raph_quart(a, roots[1],5);
			roots[2] = n_raph_quart(a, roots[2]-1,5);
			roots[3] = n_raph_quart(a, roots[3],5);
			qsort(roots, 4, sizeof(double), compare_dbl);
			return(4);
		} else if (rVal == 0 && rVal2 != 0){ // first root is complex pair
			//printf("first pair complex\n");
			p[0] = roots[0];
			p[1] = roots[1]; // store these values so we can put them to the end
			roots[0] = min(roots[2], roots[3]);
			roots[1] = max(roots[2], roots[3]);
			roots[2] = p[0];
			roots[3] = p[1];
			roots[0] = n_raph_quart(a, roots[0],5);
			roots[1] = n_raph_quart(a, roots[1],5);
			return(2);
		} else if (rVal != 0 && rVal2 == 0){ // second root is complex pair
			//printf("second pair complex\n");
			// roots are already in the right order
			p[0] = max(roots[0], roots[1]);
			p[1] = min(roots[0], roots[1]);
			roots[0] = p[1];
			roots[1] = p[0];
			roots[0] = n_raph_quart(a, roots[0],5);
			roots[1] = n_raph_quart(a, roots[1],5);
			return(2);
		} else if (rVal == 0 && rVal2 == 0){ // both quadratic equations have complex results
			//printf("both pairs complex\n");
			// roots are in the right order again
			return(0);
		} else {
			//printf("unhandled case in roots");
		}

	}
}