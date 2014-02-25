#include<stdio.h>
#include<math.h>
#include<complex.h>
#include"header.h"

int complex_lin_root(double complex A, double complex B, double complex *r1){
	if (A == 0 && B == 0){
		return(-1); // any x will satisfy this
	} else if (A == 0 && B != 0){
		return(0); // no x will satisfy this
	} else if (A != 0 && B != 0){
		*r1 = -B/A;
		return(1);
	}
}
