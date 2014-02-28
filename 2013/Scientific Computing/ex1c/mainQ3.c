#include<stdio.h>
#include<math.h>
#include<complex.h>
#include"header.h"

int main(void){
	double args[4];
	double r[5];
	double b, Y, X;
	double closest;
	int rVal;
	X = 1.0/3.0;
	Y = 1.0/3.0;
	printf("%20s\t%2s\n", "b", "r");
	for(b = 0.535926580439790; b < 0.535926580439800; b += 0.000000000000001){
		args[3] = (2.0/b) + (2.0/(b*Y)) - (2.0*b)/Y;
		args[2] = 0;
		args[1] = (2.0/b) - (2.0/(b*Y)) + (2.0*b)/Y;
		args[0] = -1.0;
		rVal = rquartic_roots(args, r);
		if(rVal == 4){
			printf("%20.15g\t%2d\n", b, rVal);
		} else {
			printf("%20.15g\t%2d\n", b, rVal);
		}
	}
	b = 0.535926580439797;
	args[3] = (2.0/b) + (2.0/(b*Y)) - (2.0*b)/Y;
	args[2] = 0;
	args[1] = (2.0/b) - (2.0/(b*Y)) + (2.0*b)/Y;
	args[0] = -1.0;
	rVal = rquartic_roots(args, r);
	printf("%5s\t%2s\t%10s\t%10s\t%10s\t%10s\t%10s\t%10s\t%10s\t%10s\n", "b", "r", "root 1", "phi 1", "root 2", "phi 2", "root 3", "phi 3", "root 4", "phi 4");
	printf("%5.2g\t%2d\t%10.5g\t%10.5g\t%10.5g\t%10.5g\t%10.5g\t%10.5g\t%10.5g\t%10.5g\n", b, rVal, r[1], 2.0*atan(r[1]), r[2], 2.0*atan(r[2]), r[3], 2.0*atan(r[3]), r[4], 2.0*atan(r[4]));

}

