#include<stdio.h>
#include<math.h>
#include<complex.h>
#include"header.h"

int main(void){
	double args[4];
	double r[4];
	double b, Y, X;
	int rVal;
	X = 1.0/3.0;
	Y = 1.0/3.0;
	printf("%5s\t%2s\t%10s\t%10s\t%10s\t%10s\t%10s\n", "b", "r", "phi", "root 1", "root 2", "root 3", "root 4");
	/*for(b = 0.05; b < 1.0; b += 0.05){
		args[3] = (2.0*X + 2.0 + 2.0*b*b)/(b*Y);
		args[2] = 0.0;
		args[1] = (2.0*X-2.0+2.0*b*b)/(b*Y);
		args[0] = 1.0;	
		rVal = rquartic_roots(args, r);
		printf("%5.2g\t%2d\t%10.5g\t%10.5g\t%10.5g\t%10.5g\t%10.5g\n", b, rVal, atan(r[1]), r[0], r[1], r[2], r[3]);
	}*/
	args[3] = 13.0;
	args[2] = 0.0;
	args[1] = -5.0;
	args[0] = 1.0;
	rVal = rquartic_roots(args, r);
	printf("%5s\t%2s\t%10s\t%10s\t%10s\t%10s\t%10s\n", "b", "r", "phi", "root 1", "root 2", "root 3", "root 4");
	printf("%5.2g\t%2d\t%20.18g\t%20.18g\t%20.18g\t%20.18g\n", b, rVal, r[0], r[1], r[2], r[3]);
	r[0] = n_raph_quart(args, r[0], 10);	
	r[1] = n_raph_quart(args, r[1], 10);
	r[2] = n_raph_quart(args, r[2], 10);
	r[3] = n_raph_quart(args, r[3], 10);
	printf("After N-R step\n");
	printf("%5.2g\t%2d\t%20.18g\t%20.18g\t%20.18g\t%20.18g\n", b, rVal, r[0], r[1], r[2], r[3]);
}

