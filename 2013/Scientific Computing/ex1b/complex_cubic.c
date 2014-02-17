#include<complex.h>
#include<math.h>
#include<float.h>
#include<stdio.h>

int complex_cubic(double complex a2, double complex a1, double complex a0, double complex* r1, double complex* r2, double complex* r3){
	int i, num_iter;
	double complex z, b1, b0;
	// do Newton's root method to find a root
	num_iter = 20;
	z = 1.0 + 1.0*I;
	for(i = 0; i < num_iter; i++){
		z = z - (z*z*z + a2*z*z + a1*z + a0)/(3.0*z*z + 2.0*a2*z + a1);
		printf("guess at iteration %d: z = %g + %gi\n", i, creal(z), cimag(z));
	}
	printf("final guess: z = %g + %gi\n", creal(z), cimag(z));
	*r1 = z;
	b1 = a2 + z;
	b0 = -1.0*a0/z;
	complex_quad(1.0, b1, b0, &r2, &r3);
}
