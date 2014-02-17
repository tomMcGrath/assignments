#include<complex.h>
#include<math.h>
#include<float.h>
#include<stdio.h>

int complex_cubic(double complex, double complex, double complex, double complex*, double complex*, double complex*);

int main(void) {
	double complex t1, t2, t3;
	double complex a2, a1, a0;
	a2 = 7.0 + 1.0*I;
	a1 = 1.0 + 0.5*I;
	a0 = 94.0 + 1000.0*I;
	complex_cubic(a2,a1,a0,&t1,&t2,&t3);
}

int complex_cubic(double complex a2, double complex a1, double complex a0, double complex* r1, double complex* r2, double complex* r3){
	int i, num_iter;
	double complex z;
	// do Newton's root method to find a root
	num_iter = 20;
	z = 1.0 + 1.0*I;
	for(i = 0; i < num_iter; i++){
		z = z - (z*z*z + a2*z*z + a1*z + a0)/(3.0*z*z + 2.0*a2*z + a1);
		printf("guess at iteration %d: z = %g + %gi\n", i, creal(z), cimag(z));
	}
	printf("final guess: z = %g + %gi\n", creal(z), cimag(z));
}