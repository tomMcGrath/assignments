#include<complex.h>
#include<math.h>
#include<float.h>
#include<stdio.h>
#include"header.h"

int complex_quad(double complex a2, double complex a1, double complex a0, double complex* r1, double complex* r2){
	double complex disc, d_div_a0, d_div_a1;
	double complex lrg_arg1, lrg_arg2;
	double maxval = DBL_MAX;
	int four, two;
	four = 4;
	two = 2;

	// debug prints:
	/*printf("a2 %.10g \t maxval/a2 %.10g\n", a2, maxval/a2);
	printf("a1 %.10g \t sqrt(maxval) %.10g\n", a1, sqrt(maxval));
	printf("a0 %.10g \t maxval/a0 %.10g\n", a0, maxval/a0);*/

	if (a2 == 0 && a1 != 0) {		
		return(-1); // linear equation has 1 real root
	} else if (a2== 0 && a1 == 0) {
		return(0); // no roots, either have 0==0 (a0 = 0) or a0==0 (inconsistent)
	} else {
		if (cabs(a1) > sqrt(maxval) && (cabs(a2) > maxval/cabs(a0) || cabs(a0) > maxval/cabs(a2))) {
			// divide through by one of the arguments (largest?) and go again
			//printf("All arguments too large, dividing\n");		
			lrg_arg1 = fmax(cabs(a2), cabs(a1));
			lrg_arg2 = fmax(cabs(lrg_arg1), cabs(a0));
			a2 = a2/lrg_arg2;
			a1 = a1/lrg_arg2;
			a0 = a0/lrg_arg2;
			disc = a1*a1 - four*a2*a0;
		} else if (cabs(a1) > sqrt(maxval))	{
			// re-form discriminant avoiding a1*a1
			//printf("a1*a1 too large, dividing disc by a1 first\n");
			d_div_a1 = a1 - four*(a2*a0/a1);
			disc = d_div_a1 * a1;
		} else if (cabs(a2) > maxval/cabs(a0) || cabs(a0) > maxval/cabs(a2)) {
			// re-form discriminant avoiding a2*a0
			//printf("a0 or a2 too large, dividing disc by a0 first\n");
			d_div_a0 = ((a1*a1)/a0) - four*a2;
			disc = d_div_a0*a0;
		} else {
			//printf("arguments fine, proceeding\n");
			disc = a1*a1 - four*a2*a0;
		}		
	} // so now we have disc, just do the calculation
	if (cimag(disc) == 0 && cabs(disc) == 0) { // no imaginary component, discriminant == 0
		// handle 2 equal real roots
		*r1 = -(a1)/(two*a2);
		*r2 = -(a1)/(two*a2);
		return(1);
	} else {
	// we can now return distinct roots
		if(cabs(a1) > 0) {			
			*r2 = (-a1 - csqrt(disc))/(two*a2); // avoid loss of significance by subtracting different signs
			*r1 = (a0)/(*r2*a2);
			return(2);
		} else if (cabs(a1) <= 0) {
			*r1 = (-a1 + csqrt(disc))/(two*a2); // we need to calculate the other root first this time
			*r2 = (a0)/(*r1*a2);
			return(2);
		}
	}	
}
