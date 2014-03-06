#include<stdio.h>
#include<math.h>
#include<complex.h>
#include"header.h"

int main(void){
	double args[4];
	double r[5];
	double roots_X[4];
	double roots_Y[4];
	double b, Y, X;
	double closest;
	int rVal;
	printf("Name: <Tom McGrath>\n");
	printf("CID: <00898098>, LIBRARY NO: <0246656362>\n");
	printf("Email Address: <t.mcgrath13@imperial.ac.uk>\n");
	printf("Course Code: <M5SC>\n");
	printf("Time: %s\n",__TIME__); 
	printf("Date: %s\n",__DATE__); 
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

	// Second part of question
	printf("b = 0.535926580439797\n");
	b = 0.535926580439797;
	args[3] = (2.0/b) + (2.0/(b*Y)) - (2.0*b)/Y;
	args[2] = 0;
	args[1] = (2.0/b) - (2.0/(b*Y)) + (2.0*b)/Y;
	args[0] = -1.0;
	rVal = rquartic_roots(args, r);
	printf("%5s\t%2s\t%10s\t%10s\t%10s\t%10s\t%10s\t%10s\t%10s\t%10s\n", "b", "r", "root 1", "phi 1", "root 2", "phi 2", "root 3", "phi 3", "root 4", "phi 4");
	printf("%5.2g\t%2d\t%10.5g\t%10.5g\t%10.5g\t%10.5g\t%10.5g\t%10.5g\t%10.5g\t%10.5g\n", b, rVal, r[1], 2.0*atan(r[1]), r[2], 2.0*atan(r[2]), r[3], 2.0*atan(r[3]), r[4], 2.0*atan(r[4]));

	roots_X[0] = cos(2.0*atan(r[1]));
	roots_X[1] = cos(2.0*atan(r[2]));
	roots_X[2] = cos(2.0*atan(r[3]));
	roots_X[3] = cos(2.0*atan(r[4]));
	roots_Y[0] = b*sin(2.0*atan(r[1]));
	roots_Y[1] = b*sin(2.0*atan(r[2]));
	roots_Y[2] = b*sin(2.0*atan(r[3]));
	roots_Y[3] = b*sin(2.0*atan(r[4]));
	printf("X[0] = %15.10g\tY[0] = %15.10g\n", roots_X[0], roots_Y[0]);
	printf("X[1] = %15.10g\tY[1] = %15.10g\n", roots_X[1], roots_Y[1]);
	printf("X[2] = %15.10g\tY[2] = %15.10g\n", roots_X[2], roots_Y[2]);
	printf("X[3] = %15.10g\tY[3] = %15.10g\n", roots_X[3], roots_Y[3]);
}

