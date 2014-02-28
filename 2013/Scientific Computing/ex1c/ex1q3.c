#include<stdio.h>
#include<math.h>
#include<complex.h>
#include"header.h"

int main(void){
	double args[4];
	double r[4];
	double b, Y, X;
	double closest;
	int rVal;
	X = 1.0/3.0;
	Y = 1.0/3.0;
	printf("%5s\t%2s\t%10s\t%10s\t%10s\t%10s\t%10s\t%10s\t%10s\t%10s\n", "b", "r", "root 1", "phi 1", "root 2", "phi 2", "root 3", "phi 3", "root 4", "phi 4");
	for(b = 0.45; b < 0.5; b += 0.001){
		args[3] = (2.0*X + 2.0 + 2.0*b*b)/(b*Y);
		args[2] = 0.0;
		args[1] = (2.0*X-2.0+2.0*b*b)/(b*Y);
		args[0] = 1.0;	
		rVal = rquartic_roots(args, r);
		if(rVal == 4){
			printf("%5.2g\t%2d\t%10.5g\t%10.5g\t%10.5g\t%10.5g\t%10.5g\t%10.5g\t%10.5g\t%10.5g\n", b, rVal, r[1], 2.0*atan(r[1]), r[2], 2.0*atan(r[2]), r[3], 2.0*atan(r[3]), r[4], 2.0*atan(r[4]));
		} else {
			printf("%5.2g\t%2d\t%10.5g\t%10.5g\t%10.5g\t%10.5g\t%10.5g\t%10.5s\t%10.5g\t%10.5s\n", b, rVal, r[1], 2.0*atan(r[1]), r[2], 2.0*atan(r[2]), r[3], "cplx", r[4], "cplx");
		}
	}

}

