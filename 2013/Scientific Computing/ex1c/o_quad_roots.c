#include<stdio.h>
#include<math.h>
#include<float.h>
#include"header.h"

int quad_roots(double args[3], double roots[2]) {
	double a2 = args[2];
	double a1 = args[1];
	double a0 = args[0];
	double lr_args[2];
	double lr_r[1];
	double q, a_range, disc, lrg_arg1, lrg_arg2;
	double maxval = DBL_MAX;
	//printf("solving quadratic with coefficients a2 = %10.5g\ta1 = %10.5g\ta0 = %10.5g\n", a2, a1, a0);
	a_range = max(max(a2,a1),max(a1,a0)) - min(min(a2,a1),min(a1,a0)); // dividing through reduces risk of fp overflow
	// DEBUG PRINTS
	//printf("max = %.5g\nmin = %.5g\n", max(max(a2,a1),max(a1,a0)), min(min(a2,a1),min(a1,a0)));
	if (a_range < DBL_MAX && a_range > 1.0e+100){	
		//printf("Dividing by a_range = %.5g\n", a_range);
		a2 = a2/sqrt(a_range);
		a1 = a1/sqrt(a_range);
		a0 = a0/sqrt(a_range);
	}
	// DEBUG PRINT
	//printf("a2 = %.5g\n a1 = %.5g\n a0 = %.5g\n", a2, a1, a0);
	if (a1 > sqrt(maxval) && (a2 > maxval/a0 || a0 > maxval/a2)) {
			// divide through by one of the arguments (largest?) and go again
			//printf("All arguments too large, dividing\n");		
			lrg_arg1 = fmax(a2, a1);
			lrg_arg2 = fmax(lrg_arg1, a0);
			a2 = a2/lrg_arg2;
			a1 = a1/lrg_arg2;
			a0 = a0/lrg_arg2;
			disc = a1*a1 - 4.0*a2*a0;
	} else if (a2 == 0){ // linear equation case
		lr_args[1] = args[1];
		lr_args[0] = args[0];
		lin_root(lr_args, lr_r);
		roots[0] = lr_r[0];
		roots[1] = lr_r[0];
		return(-1);
	} else if (a0 == 0) { // one root is zero
		lin_root(lr_args, lr_r);
		roots[0] = lr_r[0];
		roots[1] = 0.0;
		return(2);
	} else if (a1 == 0 && a0 < 0) { // x^2 = -c
		roots[0] = sqrt(-a0)/sqrt(a2);
		roots[1] = -sqrt(-a0)/sqrt(a2);
		return(2);
	} else {
		disc = a1*a1 - 4.0*a2*a0;
		// DEBUG PRINT
		//printf("disc = %.5g\n", disc);
		if (disc < 0){
			roots[0] = -a1/(2.0*a2);
			roots[1] = sqrt(-1.0*disc)/(2.0*a2);
			return(0);
		} else if (disc > 0){
			if (a1 > 0){
				q = -0.5*(a1 + sqrt(disc));
			} else {
				q = -0.5*(a1 - sqrt(disc));
			}
			// DEBUG PRINT
			//printf("q = %.5g\n", q);	
			roots[0] = a0/q;
			roots[1] = q/a2;
			return(2);
		} else if (disc == 0){
			roots[0] = -a1/(2.0*a2);
			roots[1] = -a1/(2.0*a2);
			return(1);
		}
	}
}
