#include <complex.h>
#include <math.h>
#include <stdio.h>

int main(void)
{
double complex z = 1.0 + 3.0*I;
double x;
printf("z = %f + %f*I\n", creal(z), cimag(z));
printf ("Phase is %f, modulus is %f\n", carg (z), cabs (z));
z = csqrt(I);
printf("z = %f + %f*I\n", creal(z), cimag(z));
}