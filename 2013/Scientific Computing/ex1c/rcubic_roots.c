#include<math.h>
#include<float.h>
#include<stdio.h>
#include"header.h"

int rcubic_roots(double args[3], double roots[3]){
	double q, r, q3_r2;
	double a2, a1, a0;
	double root_1, root_2, root_3;
	double lr_r[1], qr_r[2];
	double args_b[2], args_qr[2];
	double y;
	int rVal;
	a2 = args[2];
	a1 = args[1];
	a0 = args[0];
	//printf("solving cubic with args a2 = %10.5g\ta1 = %10.5g\ta0 = %10.5g\n", a2, a1, a0);
	q = calcQ(a2, a1);
	//printf("q: %g\n", q);
	r = calcR(a2, a1, a0);
	//printf("r: %g\n", r);
	q3_r2 = q*q*q - r*r;
	//printf("q3_r2: %g\n", q3_r2);
	if (a2 == 0 && a1 == 0){ // special case i
		//printf("case i\n");
		roots[0] = pow(absval(a0), 1.0/3.0);
		roots[1] = (-1.0/2.0)*pow(absval(a0), 1.0/3.0); // real part of complex root of unity
		roots[2] = (sqrt(3.0)/2.0)*pow(absval(a0), 1.0/3.0); // positive value of imaginary part
		return(1);
	} else if (a0 == 0){ // special case ii
		//printf("case ii\n");
		roots[0] = 0;
		args_qr[2] = 1.0;
		args_qr[1] = a2;
		args_qr[0] = a1;
		rVal = quad_roots(args_qr, qr_r);
		roots[1] = qr_r[0];
		roots[2] = qr_r[1];
		return(rVal);
	} else if (a0 == a1*a2) { // special case iii
		//printf("case iii\n");
		root_1 = -1.0*a2;
		if (a1 < 0){
			root_2 = sqrt(-1.0*a1);
			root_3 = -1.0*sqrt(-1.0*a1);
			roots[0] = min(min(root_1, root_2), min(root_2, root_3));
			roots[1] = mid(root_1, root_2, root_3);
			roots[2] = max(max(root_1, root_2), max(root_2, root_3));
			return(3);
		} else if (a1 > 0){
			roots[0] = root_1;
			roots[1] = 0; // there's no real part to the other roots
			roots[2] = sqrt(a1); // only complex root exists
			return(1);
		}
	} else if (3.0*a1 == a2*a2){ // special case iv
		//printf("case iv\n");		
		roots[0] = (-1.0/3.0)*a2;
		roots[1] = (-1.0/3.0)*a2;
		roots[2] = (-1.0/3.0)*a2;
		return(2);
	} else if (r == 0){ // special case v
		//printf("case v\n");
		if (q >= 0){
			roots[0] = -1.0*sqrt(3.0*q) - (1.0/3.0)*a2;
			roots[1] = (-1.0/3.0)*a2;
			roots[2] = sqrt(3.0*q) - (1.0/3.0)*a2;
			return(3);
		} else if (q < 0) {
			roots[0] = (-1.0/3.0)*a2;
			roots[1] = (-1.0/3.0)*a2;
			roots[2] = sqrt(-3.0*q);
			return(1);
		}
	} else if (q == 0){ // special case vi
		//printf("case vi\n");
		roots[0] = pow(absval(-2.0*r), 1.0/3.0) - (a2/3.0);
		roots[1] = pow(absval(-2.0*r), 1.0/3.0)*(1.0/2.0) - (a2/3.0);
		roots[2] = pow(absval(-2.0*r), 1.0/3.0)*(sqrt(3.0)/2.0);
		return(1);
	} else if (q*q*q < DBL_MAX && r*r < DBL_MAX && q*q*q == r*r){ // special case vii
		//printf("case vii\n");
		roots[0] = sqrt(q) - (a2/3.0);
		roots[1] = sqrt(q) - (a2/3.0);
		roots[2] = -1.0*a2 - 2.0*root_1;
		return(2);
	} else {
		//printf("general case\n");
		if (q3_r2 < 0){
			//printf("2 complex roots\n");
			//handle 2 complex roots
			//printf("sqrt(-q3_r2) = %g\n", sqrt(-q3_r2));
			//printf("sqrt(-q3_r2) + absval(r) = %g\n", sqrt(-q3_r2) + absval(r));
			//printf("pow(sqrt(-q3_r2) + absval(r), 1.0/3.0) = %g\n", pow(sqrt(-q3_r2) + absval(r), 1.0/3.0));
			roots[0] = (-absval(r)/r)*(pow(sqrt(-q3_r2) + absval(r), 1.0/3.0) + q/(pow(sqrt(r*r - q*q*q) + absval(r), 1.0/3.0))) - a2/3.0;
			//printf("First root: %g\n", roots[0]);
			args_qr[2] = 1.0;
			args_qr[1] = a2 + roots[0];
			args_qr[0] = -1.0*a0/(roots[0]);
			//printf("args_qr[1] = %g\nargs_qr[0] = %g\n", args_qr[1], args_qr[0]);
			quad_roots(args_qr, qr_r);
			roots[1] = qr_r[0];
			roots[2] = qr_r[1];
			return(1);
		} else if (q3_r2 >= 0){
			//printf("3 real roots\n");
			//printf("roots[0] = %g\n", roots[0]);
			// handle 3 real roots
			//printf("pow(q*q*q, 1.0/2.0) = %g\n", pow(q*q*q, 1.0/2.0));
			//printf("acos(r/pow(q*q*q, 1.0/2.0)) = %g\n", acos(r/pow(q*q*q, 1.0/2.0)));
			root_1 = -2.0*sqrt(q)*cos((acos(r/pow(q*q*q, 1.0/2.0)))/3.0) - a2/3.0;
			//printf("First root: %g\n", root_1);
			//printf("args_qr[1] = %g\nargs_qr[0] = %g\n", args_qr[1], args_qr[0]);
			args_qr[2] = 1.0;
			args_qr[1] = a2 + root_1;
			args_qr[0] = -1.0*a0/(root_1);
			rVal = quad_roots(args_qr, qr_r);
			root_2 = qr_r[0];
			root_3 = qr_r[1];
			//printf("root 2: %g\nroot 3: %g\n", root_2, root_3);
			roots[0] = min(min(root_1, root_2), min(root_2, root_3));
			roots[1] = mid(root_1, root_2, root_3);
			roots[2] = max(max(root_1, root_2), max(root_2, root_3));
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
