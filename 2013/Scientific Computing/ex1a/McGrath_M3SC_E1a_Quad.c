/* McGrath  M3SC 2014 quad_roots file  */ 
#include<math.h> 
#include<float.h>
int lin_root(double *,double *); 
double fmax(double d1,double d2)
{if(d1>d2)return(d1);
return(d2);}

int quad_roots(double a2, double a1, double a0, double* r1, double* r2) {
	double disc, d_div_a0, d_div_a1;
	double lrg_arg1, lrg_arg2;
	double maxval = DBL_MAX;
	int four, two;
	four = 4;
	two = 2;
	if (a2 == 0 && a1 != 0) {		
		return(-1); // linear equation has 1 real root
	} else if (a2== 0 && a1 == 0) {
		return(0); // no roots, either have 0==0 (a0 = 0) or a0==0 (inconsistent)
	} else {
		if (a1 > sqrt(maxval) && (a2 > maxval/a0 || a0 > maxval/a2)) {
			// divide through by one of the arguments (largest?) and go again
			//printf("All arguments too large, dividing\n");		
			lrg_arg1 = fmax(a2, a1);
			lrg_arg2 = fmax(lrg_arg1, a0);
			a2 = a2/lrg_arg2;
			a1 = a1/lrg_arg2;
			a0 = a0/lrg_arg2;
			disc = a1*a1 - four*a2*a0;
		} else if (a1 > sqrt(maxval))	{
			// re-form discriminant avoiding a1*a1
			//printf("a1*a1 too large, dividing disc by a1 first\n");
			d_div_a1 = a1 - four*(a2*a0/a1);
			disc = d_div_a1 * a1;
		} else if (a2 > maxval/a0 || a0 > maxval/a2) {
			// re-form discriminant avoiding a2*a0
			//printf("a0 or a2 too large, dividing disc by a0 first\n");
			d_div_a0 = ((a1*a1)/a0) - four*a2;
			disc = d_div_a0*a0;
		} else {
			//printf("arguments fine, proceeding\n");
			disc = a1*a1 - four*a2*a0;
		}		
	} // so now we have disc, just do the calculation
	if (disc == 0) {
		// handle 2 equal real roots
		*r1 = -(a1)/(two*a2);
		*r2 = -(a1)/(two*a2);
		return(1);
	} else if (disc > 0) {
	// handle 2 distinct real roots
		if(a1 > 0) {			
			*r2 = (-a1 - sqrt(disc))/(two*a2); // avoid loss of significance by subtracting different signs
			*r1 = (a0)/(*r2*a2);
			return(2);
		} else if (a1 <= 0) {
			*r1 = (-a1 + sqrt(disc))/(two*a2); // we need to calculate the other root first this time
			*r2 = (a0)/(*r1*a2);
			return(2);
		}
	} else if (disc < 0) {
		// handle complex conjugate roots
		return(-2); // we want _real_ roots
	} else {
		//printf("You have a problem!\n"); // we should never get here
		return(-3);
	}	
}