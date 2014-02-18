#include<complex.h>
#include<math.h>
#include<float.h>
#include<stdio.h>
#include"header.h"

int complex_cubic(double complex a2, double complex a1, double complex a0, double complex* r1, double complex* r2, double complex* r3){
	int i, num_iter;
	double complex z, b1, b0;
	if (creal(a0) == 0 && cimag(a0) == 0){ // one root is zero
		printf("one root is zero\n");
		*r1 = 0;
		complex_quad(1.0, a2, a1, r2, r3);
		return(3);
	}
	// do Newton's root method to find a root
	num_iter = 20;
	z = 1.0 + 1.0*I;
	for(i = 0; i < num_iter; i++){
		z = z - (z*z*z + a2*z*z + a1*z + a0)/(3.0*z*z + 2.0*a2*z + a1);
		//printf("guess at iteration %d: z = %g + %gi\n", i, creal(z), cimag(z));
	}
	//printf("final guess: z = %g + %gi\n", creal(z), cimag(z));
	*r1 = z;
	b1 = a2 + z;
	if(a0 == 0){
		b0 = 0;
	} else {
		b0 = -1.0*a0/z;
	}
	//printf("b1 = %6.5g+%6.5gi\tb0 = %6.5g+%6.5gi\n", creal(b1), cimag(b1), creal(b0), cimag(b0)); 
	return(complex_quad(1.0, b1, b0, r2, r3));
}
