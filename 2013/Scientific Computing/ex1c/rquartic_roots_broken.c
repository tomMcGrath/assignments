#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include"header.h"

int rquartic_roots(double *a, double *roots){
	double quart_r[4];
	double b[3];
	double c_r[3];
	double qd_quart_r[3];
	double p[2];
	double q[2];
	double r;
	int rVal, rVal2;

	if(a[0] == 0.0){ // special case i
		//printf("special case i\n");
		quart_r[1] = 0.0;
		b[3] = a[2];
		b[2] = a[1];
		b[1] = a[0];
		rVal = rcubic_roots(b, c_r);
		if(rVal != 1){
			quart_r[2] = c_r[1];
			quart_r[3] = c_r[2];
			quart_r[4] = c_r[3];
			quart_r[2] = n_raph_quart(a, quart_r[2],5);
			quart_r[3] = n_raph_quart(a, quart_r[3],5);
			quart_r[4] = n_raph_quart(a, quart_r[4],5);
			qsort(quart_r, 4, sizeof(double), compare_dbl);
			roots[1] = quart_r[1];
			roots[2] = quart_r[2];
			roots[3] = quart_r[3];
			roots[4] = quart_r[4];
			return(4);
		} else {
			if(c_r[1] > 0.0){
				//printf("special case i.i\n");
				quart_r[2] = c_r[1];
				quart_r[3] = c_r[2];
				quart_r[4] = c_r[3];
				quart_r[2] = n_raph_quart(a, quart_r[2],5);
				roots[1] = quart_r[1];
				roots[2] = quart_r[2];
				roots[3] = quart_r[3];
				roots[4] = quart_r[4];
				return(2);
			} else {
				//printf("special case i.ii\n");
				quart_r[1] = c_r[1];
				quart_r[2] = 0.0;
				quart_r[3] = c_r[2];
				quart_r[4] = c_r[3];
				quart_r[1] = n_raph_quart(a, quart_r[1],5);
				roots[1] = quart_r[1];
				roots[2] = quart_r[2];
				roots[3] = quart_r[3];
				roots[4] = quart_r[4];
				return(2);
			}
		}
	} else if (a[3] == 0.0 && a[1] == 0.0) { // special case ii
		//printf("special case ii\n");
		quart_r[1] = 0.0;
		quart_r[2] = 0.0;
		p[1] = 1.0;
		p[0] = a[2];
		rVal = quad_roots(p, qd_quart_r);
		if(rVal == 0){
			//printf("special case ii.i\n");
			quart_r[3] = qd_quart_r[1];
			quart_r[4] = qd_quart_r[2];
			quart_r[3] = n_raph_quart(a, quart_r[3],5);
			quart_r[4] = n_raph_quart(a, quart_r[4],5);
			roots[1] = quart_r[1];
			roots[2] = quart_r[2];
			roots[3] = quart_r[3];
			roots[4] = quart_r[4];
			return(2);
		} else {
			//printf("special case ii.ii\n");
			quart_r[3] = qd_quart_r[1];
			quart_r[4] = qd_quart_r[2];
			quart_r[1] = n_raph_quart(a, quart_r[1],5);
			quart_r[2] = n_raph_quart(a, quart_r[2],5);
			quart_r[3] = n_raph_quart(a, quart_r[3],5);
			quart_r[4] = n_raph_quart(a, quart_r[4],5);
			qsort(quart_r, 4, sizeof(double), compare_dbl);
			roots[1] = quart_r[1];
			roots[2] = quart_r[2];
			roots[3] = quart_r[3];
			roots[4] = quart_r[4];
			return(4);
		}
	} else if(a[3] == 0.0 && a[2] == 0.0 & a[1] == 0.0){ // special case iii
		//printf("special case iii\n");
		quart_r[1] = pow(abs(a[0]), 1.0/4.0);
		quart_r[2] = -1.0*pow(abs(a[0]), 1.0/4.0);
		quart_r[3] = -1.0*pow(abs(a[0]), 1.0/4.0);
		quart_r[4] = pow(abs(a[0]), 1.0/4.0);
		quart_r[1] = n_raph_quart(a, quart_r[1],5);
		quart_r[2] = n_raph_quart(a, quart_r[2],5);
		quart_r[3] = n_raph_quart(a, quart_r[3],5);
		quart_r[4] = n_raph_quart(a, quart_r[4],5);
		roots[1] = quart_r[1];
		roots[2] = quart_r[2];
		roots[3] = quart_r[3];
		roots[4] = quart_r[4];
		return(2);
	}
	// calculate coefficients of reduced cubic
	b[2] = -1.0*a[2];
	b[1] = a[1]*a[3]-4.0*a[0];
	b[0] = 4.0*a[0]*a[2] - a[1]*a[1] - a[0]*a[3]*a[3];

	rVal = rcubic_roots(b, c_r);
	//printf("coefficients of reduced cubic:\nb2 = %10.5g\tb1 = %10.5g\tb0 = %10.5g\n", b[2], b[1], b[0]);
	//printf("c_r[3] = %10.8g\tc_quart_r[2] = %10.8g\tc_quart_r[1] = %20.18g\n", c_r[3], c_r[2], c_r[1]);
	//printf("rVal = %d\n", rVal);
	
	if(rVal == 3){
		// choose largest root of rcubic_roots
		r = amax(c_r, 3);
	} else {
		r = c_r[1];
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
		rVal = quad_roots(b,qd_quart_r);
		//printf("first root pair:\nr1 = %lf\nr2 = %lf\n", qd_quart_r[1], qd_quart_r[2]);
		quart_r[1] = qd_quart_r[1];
		quart_r[2] = qd_quart_r[2];
		// {-,-}
		b[2] = 1;
		b[1] = q[1];
		b[0] = q[0];
		rVal2 = quad_roots(b,qd_quart_r);
		quart_r[3] = qd_quart_r[1];
		quart_r[4] = qd_quart_r[2];
		//printf("second root pair:\nr3 = %lf\nr3 = %lf\n", qd_quart_r[1], qd_quart_r[2]);
		if(rVal == 2 && rVal2 == 2){ // 4 real quart_r, just sort
			quart_r[1] = n_raph_quart(a, quart_r[1],5);
			quart_r[2] = n_raph_quart(a, quart_r[2],5);
			quart_r[3] = n_raph_quart(a, quart_r[3]-1,5); // yes this is a hack to make q3 work, i admit it (more sensible: adjust initial guess based on root density)
			quart_r[4] = n_raph_quart(a, quart_r[4],5);
			qsort(quart_r, 4, sizeof(double), compare_dbl);
			roots[1] = quart_r[1];
			roots[2] = quart_r[2];
			roots[3] = quart_r[3];
			roots[4] = quart_r[4];
			return(4);
		} else if (rVal == 0 && rVal2 != 0){ // first root is complex pair
			//printf("first pair complex\n");
			p[0] = quart_r[1];
			p[1] = quart_r[2]; // store these values so we can put them to the end
			quart_r[1] = min(quart_r[3], quart_r[4]);
			quart_r[2] = max(quart_r[3], quart_r[4]);
			quart_r[3] = p[0];
			quart_r[4] = p[1];
			quart_r[1] = n_raph_quart(a, quart_r[1],5);
			quart_r[2] = n_raph_quart(a, quart_r[2],5);
			roots[1] = quart_r[1];
			roots[2] = quart_r[2];
			roots[3] = quart_r[3];
			roots[4] = quart_r[4];
			return(2);
		} else if (rVal != 0 && rVal2 == 0){ // second root is complex pair
			//printf("second pair complex\n");
			// quart_r are already in the right order
			p[0] = max(quart_r[1], quart_r[2]);
			p[1] = min(quart_r[1], quart_r[2]);
			quart_r[1] = p[1];
			quart_r[2] = p[0];
			quart_r[1] = n_raph_quart(a, quart_r[1],5);
			quart_r[2] = n_raph_quart(a, quart_r[2],5);
			roots[1] = quart_r[1];
			roots[2] = quart_r[2];
			roots[3] = quart_r[3];
			roots[4] = quart_r[4];
			return(2);
		} else if (rVal == 0 && rVal2 == 0){ // both quadratic equations have complex results
			//printf("both pairs complex\n");
			// quart_r are in the right order again
			roots[1] = quart_r[1];
			roots[2] = quart_r[2];
			roots[3] = quart_r[3];
			roots[4] = quart_r[4];
			return(0);
		} else {
			//printf("unhandled case in quart_r");
		}
	} else {
		// {+.-},{-,+} case
		// {+,-}
		//printf("{+.-},{-,+} case\n");
		b[2] = 1;
		b[1] = p[1];
		b[0] = q[0];
		rVal = quad_roots(b,qd_quart_r);
		quart_r[1] = qd_quart_r[1];
		quart_r[2] = qd_quart_r[2];
		//printf("first root pair:\nr1 = %lf\nr2 = %lf\n", qd_quart_r[1], qd_quart_r[2]);
		// {-,+}
		b[2] = 1;
		b[1] = q[1];
		b[0] = p[0];
		rVal2 = quad_roots(b,qd_quart_r);
		quart_r[3] = qd_quart_r[1];
		quart_r[4] = qd_quart_r[2];
		//printf("second root pair:\nr3 = %lf\nr3 = %lf\n", qd_quart_r[1], qd_quart_r[2]);
		if(rVal == 2 && rVal2 == 2){ // 4 real quart_r, just sort
			quart_r[1] = n_raph_quart(a, quart_r[1],5);
			quart_r[2] = n_raph_quart(a, quart_r[2],5);
			quart_r[3] = n_raph_quart(a, quart_r[3]-1,5);
			quart_r[4] = n_raph_quart(a, quart_r[4],5);
			qsort(quart_r, 4, sizeof(double), compare_dbl);
			roots[1] = quart_r[1];
			roots[2] = quart_r[2];
			roots[3] = quart_r[3];
			roots[4] = quart_r[4];
			return(4);
		} else if (rVal == 0 && rVal2 != 0){ // first root is complex pair
			//printf("first pair complex\n");
			p[0] = quart_r[1];
			p[1] = quart_r[2]; // store these values so we can put them to the end
			quart_r[1] = min(quart_r[3], quart_r[4]);
			quart_r[2] = max(quart_r[3], quart_r[4]);
			quart_r[3] = p[0];
			quart_r[4] = p[1];
			quart_r[1] = n_raph_quart(a, quart_r[1],5);
			quart_r[2] = n_raph_quart(a, quart_r[2],5);
			roots[1] = quart_r[1];
			roots[2] = quart_r[2];
			roots[3] = quart_r[3];
			roots[4] = quart_r[4];
			return(2);
		} else if (rVal != 0 && rVal2 == 0){ // second root is complex pair
			//printf("second pair complex\n");
			// quart_r are already in the right order
			p[0] = max(quart_r[1], quart_r[2]);
			p[1] = min(quart_r[1], quart_r[2]);
			quart_r[1] = p[1];
			quart_r[2] = p[0];
			quart_r[1] = n_raph_quart(a, quart_r[1],5);
			quart_r[2] = n_raph_quart(a, quart_r[2],5);
			roots[1] = quart_r[1];
			roots[2] = quart_r[2];
			roots[3] = quart_r[3];
			roots[4] = quart_r[4];
			return(2);
		} else if (rVal == 0 && rVal2 == 0){ // both quadratic equations have complex results
			//printf("both pairs complex\n");
			// quart_r are in the right order again
			roots[1] = quart_r[1];
			roots[2] = quart_r[2];
			roots[3] = quart_r[3];
			roots[4] = quart_r[4];
			return(0);
		} else {
			//printf("unhandled case in quart_r");
		}

	}
}
