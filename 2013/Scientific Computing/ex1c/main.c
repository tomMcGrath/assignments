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
	printf("Name: <Tom McGrath>\n");
	printf("CID: <00898098>, LIBRARY NO: <0246656362>\n");
	printf("Email Address: <t.mcgrath13@imperial.ac.uk>\n");
	printf("Course Code: <M5SC>\n");
	printf("Time: %s\n",__TIME__); 
	printf("Date: %s\n",__DATE__); 

	X = 1.0/3.0;
	Y = 1.0/3.0;
	printf("%5s\t%4s\t%10s\t%10s\t%10s\t%10s\t%10s\t%10s\t%10s\t%10s\n", "b", "r", "root 1", "phi 1", "root 2", "phi 2", "root 3", "phi 3", "root 4", "phi 4");
	for(b = 0.05; b < 1.0; b += 0.05){
		args[3] = (2.0/b) + (2.0/(b*Y)) - (2.0*b)/Y;
		args[2] = 0;
		args[1] = (2.0/b) - (2.0/(b*Y)) + (2.0*b)/Y;
		args[0] = -1.0;
		rVal = rquartic_roots(args, r);
		if(rVal == 4){
			printf("%5.2g\t%4d\t%10.5g\t%10.5g\t%10.5g\t%10.5g\t%10.5g\t%10.5g\t%10.5g\t%10.5g\n", b, rVal, r[1], 2.0*atan(r[1]), r[2], 2.0*atan(r[2]), r[3], 2.0*atan(r[3]), r[4], 2.0*atan(r[4]));
		} else {
			printf("%5.2g\t%4d\t%10.5g\t%10.5g\t%10.5g\t%10.5g\t%10.5g\t%10.5s\t%10.5g\t%10.5s\n", b, rVal, r[1], 2.0*atan(r[1]), r[2], 2.0*atan(r[2]), r[3], "cplx", r[4], "cplx");
		}
	}
}

