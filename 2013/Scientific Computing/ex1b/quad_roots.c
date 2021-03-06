#include<stdio.h>
#include<math.h>
#include<float.h>
#include"header.h"

int quad_roots(double a2, double a1, double a0, double* r1, double* r2) {
	double q, a_range, disc, lrg_arg1, lrg_arg2;
	double maxval = DBL_MAX;
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
		lin_root(a1, a0, r1);
		lin_root(a1, a0, r2);
		return(-1);
	} else if (a0 == 0) { // one root is zero
		lin_root(a2, a1, r1);
		*r2 = 0;
		return(2);
	} else if (a1 == 0 && a0 < 0) { // x^2 = -c
		*r1 = sqrt(-a0)/sqrt(a2);
		*r2 = -sqrt(-a0)/sqrt(a2);
		return(2);
	} else {
		disc = a1*a1 - 4.0*a2*a0;
		// DEBUG PRINT
		//printf("disc = %.5g\n", disc);
		if (disc < 0){
			*r1 = -a1/(2.0*a2);
			*r2 = sqrt(-1.0*disc)/(2.0*a2);
			return(0);
		} else if (disc > 0){
			if (a1 > 0){
				q = -0.5*(a1 + sqrt(disc));
			} else {
				q = -0.5*(a1 - sqrt(disc));
			}
			// DEBUG PRINT
			//printf("q = %.5g\n", q);	
			*r1 = a0/q;
			*r2 = q/a2;
			return(2);
		} else if (disc == 0){
			*r1 = -a1/(2.0*a2);
			*r2 = -a1/(2.0*a2);
			return(1);
		}
	}
}










