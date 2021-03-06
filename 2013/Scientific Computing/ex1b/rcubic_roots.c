#include<math.h>
#include<float.h>
#include<stdio.h>
#include"header.h"

int rcubic_roots(double a2, double a1, double a0, double *r1, double *r2, double *r3){
	double q, r, q3_r2;
	double root_1, root_2, root_3;
	double b1, b0;
	double y;
	int rVal;
	q = calcQ(a2, a1);
	//printf("q: %g\n", q);
	r = calcR(a2, a1, a0);
	//printf("r: %g\n", r);
	q3_r2 = q*q*q - r*r;
	//printf("q3_r2: %g\n", q3_r2);
	if (a2 == 0 && a1 == 0){ // special case i
		//printf("case i\n");
		*r1 = pow(absval(a0), 1.0/3.0);
		*r2 = (-1.0/2.0)*pow(absval(a0), 1.0/3.0); // real part of complex root of unity
		*r3 = (sqrt(3.0)/2.0)*pow(absval(a0), 1.0/3.0); // positive value of imaginary part
		return(1);
	} else if (a0 == 0){ // special case ii
		//printf("case ii\n");
		*r1 = 0;
		rVal = quad_roots(1, a2, a1, r2, r3);
		return(rVal);
	} else if (a0 == a1*a2) { // special case iii
		//printf("case iii\n");
		root_1 = -1.0*a2;
		if (a1 < 0){
			root_2 = sqrt(-1.0*a1);
			root_3 = -1.0*sqrt(-1.0*a1);
			*r1 = min(min(root_1, root_2), min(root_2, root_3));
			*r2 = mid(root_1, root_2, root_3);
			*r3 = max(max(root_1, root_2), max(root_2, root_3));
			return(3);
		} else if (a1 > 0){
			root_2 = 0; // there's no real part to the other roots
			root_3 = sqrt(a1); // only complex root exists
			return(1);
		}
	} else if (3.0*a1 == a2*a2){ // special case iv
		//printf("case iv\n");		
		*r1 = (-1.0/3.0)*a2;
		*r2 = (-1.0/3.0)*a2;
		*r3 = (-1.0/3.0)*a2;
		return(2);
	} else if (r == 0){ // special case v
		//printf("case v\n");
		if (q >= 0){
			*r1 = -1.0*sqrt(3.0*q) - (1.0/3.0)*a2;
			*r2 = (-1.0/3.0)*a2;
			*r3 = sqrt(3.0*q) - (1.0/3.0)*a2;
			return(3);
		} else if (q < 0) {
			*r1 = (-1.0/3.0)*a2;
			*r2 = (-1.0/3.0)*a2;
			*r3 = sqrt(-3.0*q);
			return(1);
		}
	} else if (q == 0){ // special case vi
		//printf("case vi\n");
		*r1 = pow(absval(-2.0*r), 1.0/3.0) - (a2/3.0);
		*r2 = pow(absval(-2.0*r), 1.0/3.0)*(1.0/2.0) - (a2/3.0);
		*r3 = pow(absval(-2.0*r), 1.0/3.0)*(sqrt(3.0)/2.0);
		return(1);
	} else if (q*q*q < DBL_MAX && r*r < DBL_MAX && q*q*q == r*r){ // special case vii
		//printf("case vii\n");
		*r1 = sqrt(q) - (a2/3.0);
		*r2 = sqrt(q) - (a2/3.0);
		*r3 = -1.0*a2 - 2.0*root_1;
		return(2);
	} else {
		//printf("general case\n");
		if (q3_r2 < 0){
			//handle 2 complex roots
			//printf("sqrt(-q3_r2) = %g\n", sqrt(-q3_r2));
			//printf("sqrt(-q3_r2) + absval(r) = %g\n", sqrt(-q3_r2) + absval(r));
			//printf("pow(sqrt(-q3_r2) + absval(r), 1.0/3.0) = %g\n", pow(sqrt(-q3_r2) + absval(r), 1.0/3.0));
			*r1 = (-absval(r)/r)*(pow(sqrt(-q3_r2) + absval(r), 1.0/3.0) + q/(pow(sqrt(r*r - q*q*q) + absval(r), 1.0/3.0))) - a2/3.0;
			//printf("First root: %g\n", *r1);
			b1 = a2 + *r1;
			b0 = -1.0*a0/(*r1);
			//printf("b1 = %g\nb0 = %g\n", b1, b0);
			quad_roots(1.0, b1, b0, r2, r3);
			return(1);
		} else if (q3_r2 >= 0){
			// handle 3 real roots
			//printf("pow(q*q*q, 1.0/2.0) = %g\n", pow(q*q*q, 1.0/2.0));
			//printf("acos(r/pow(q*q*q, 1.0/2.0)) = %g\n", acos(r/pow(q*q*q, 1.0/2.0)));
			root_1 = -2.0*sqrt(q)*cos((acos(r/pow(q*q*q, 1.0/2.0)))/3.0) - a2/3.0;
			//printf("First root: %g\n", root_1);
			b1 = a2 + root_1;
			b0 = -1.0*a0/root_1;
			//printf("b1 = %g\nb0 = %g\n", b1, b0);
			rVal = quad_roots(1.0, b1, b0, &root_2, &root_3);
			*r1 = min(min(root_1, root_2), min(root_2, root_3));
			*r2 = mid(root_1, root_2, root_3);
			*r3 = max(max(root_1, root_2), max(root_2, root_3));
			return(3);
		}
	}
}	

double calcQ(double a2, double a1){
	double qVal;
	//qVal = (a2*a2 - 3.*a1)/9.;
	qVal = (a2/3.0)*(a2/3.0) - a1/3.0;
	return(qVal);
}

double calcR(double a2, double a1, double a0){
	double rVal;
	//rVal = (2.*a2*a2*a2 - 9.*a1*a2 + 27.*a0)/54.;
	rVal = a2*((a2/3.0)*(a2/3.0)*(1/3.0) - (a1/6.0)) + a0/2.0;
	return(rVal);
}
