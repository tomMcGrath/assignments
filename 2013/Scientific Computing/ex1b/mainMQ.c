#include<stdio.h>
#include<math.h>
#include<complex.h>
#include"header.h"

int main(void) {
	int j;
	double complex s_j, c2, c1, c0;
	double complex t1, t2, t3;

	for (j = 0; j < 100; j++){
		s_j = cexp(j*M_PI/50.0);
		c2 = -1.0*(2.0*s_j + 1.0)/(2.0*s_j - 1.0);
		c1 = (15.0*s_j + 3.0)/(4.0*s_j - 2.0);
		c0 = (9.0*s_j*s_j - 9.0*s_j)/(4.0*s_j - 2.0);
		complex_cubic(c2, c1, c0, &t1, &t2, &t3);
		printf("%3.2g + %3.2gi\t %3.2g + %3.2gi\t %3.2g + %3.2gi\t %10.5g + %10.5gi\t %10.5g + %10.5gi\t %10.5g + %10.5gi\n", creal(c2), cimag(c2), creal(c1), cimag(c1), creal(c0), cimag(c0), creal(t1), cimag(t1), creal(t2), cimag(t2), creal(t3), cimag(t3));
	}
/*
	complex_cubic(-3.0, 9.0, 0.0, &t1, &t2, &t3);
	printf("%10.5g + %10.5gi\t%10.5g + %10.5gi\t%10.5g + %10.5gi\n", creal(t1), cimag(t1), creal(t2), cimag(t2), creal(t3), cimag(t3));
	complex_quad(1.0, -3.0, 9.0, &t2, &t3);
	printf("%10.5g + %10.5gi\t%10.5g + %10.5gi\n", creal(t2), cimag(t2), creal(t3), cimag(t3));
*/
}
