#include<stdio.h>
#include<math.h>
#include<complex.h>
#include"header.h"

int main(void){
	double args[4];
	double r[4];
	double b, Y, X, x, y, d1, d2, dX, dY, theta1, theta2;
	int rVal;
	printf("Name: <Tom McGrath>\n");
	printf("CID: <00898098>, LIBRARY NO: <0246656362>\n");
	printf("Email Address: <t.mcgrath13@imperial.ac.uk>\n");
	printf("Course Code: <M5SC>\n");
	printf("Time: %s\n",__TIME__); 
	printf("Date: %s\n",__DATE__); 
	// First part of question
	X = 62997033.307818345/71492000.0;
	Y = 62997033.307818345/71492000.0;
	b = 66854000.0/71492000.0;
	//printf("X=%lf\tY=%lf\n", X, Y);
	printf("%5s\t%2s\t%10s\t%10s\t%10s\t%10s\t%10s\t%10s\t%10s\t%10s\n", "b", "r", "root 1", "phi 1", "root 2", "phi 2", "root 3", "phi 3", "root 4", "phi 4");

	args[3] = (2.0/b) + (2.0/(b*Y)) - (2.0*b)/Y;
	args[2] = 0;
	args[1] = (2.0/b) - (2.0/(b*Y)) + (2.0*b)/Y;
	args[0] = -1.0;
	rVal = rquartic_roots(args, r);
	if(rVal == 4){
		printf("%5.2g\t%2d\t%10.5g\t%10.5g\t%10.5g\t%10.5g\t%10.5g\t%10.5g\t%10.5g\t%10.5g\n", b, rVal, r[1], 2.0*atan(r[1]), r[2], 2.0*atan(r[2]), r[3], 2.0*atan(r[3]), r[4], 2.0*atan(r[4]));
	} else {
		printf("%5.2g\t%2d\t%10.5g\t%10.5g\t%10.5g\t%10.5g\t%10.5g\t%10.5s\t%10.5g\t%10.5s\n", b, rVal, r[1], 2.0*atan(r[1]), r[2], 2.0*atan(r[2]), r[3], "cplx", r[4], "cplx");
	}
	dX = X-cos(2.0*atan(r[1]));
	dY = Y-b*sin(2.0*atan(r[1]));
	//printf("d1_X = %20.16g\td1_Y = %20.16g\n", dX, dY);
	d1 = 71492000.0*sqrt(dX*dX + dY*dY);
	theta1 = atan(dX/dY);
	dX = X-cos(2.0*atan(r[2]));
	dY = Y-b*sin(2.0*atan(r[2]));
	d2 = 71492000.0*sqrt(dX*dX + dY*dY);
	theta2 = atan(dX/dY);
	//printf("d2_X = %20.16g\td2_Y = %20.16g\n", dX, dY);
	printf("d1 = %20.13g\nd2 = %20.13g\n", d1, d2);
	printf("theta 1 = %20.13g rad\t%20.13g deg\ntheta 2 = %20.13g rad\t%20.13g deg\n", theta1, theta1*180.0/M_PI, theta2, theta2*180.0/M_PI);

	// Second part of question
	X = 46656362.0/71492000.0;
	Y = 52636566.4/71492000.0;
	//printf("X=%lf\tY=%lf\n", X, Y);
	printf("%5s\t%2s\t%10s\t%10s\t%10s\t%10s\t%10s\t%10s\t%10s\t%10s\n", "b", "r", "root 1", "phi 1", "root 2", "phi 2", "root 3", "phi 3", "root 4", "phi 4");
	args[3] = (2.0*X/(b*Y)) + (2.0/(b*Y)) - (2.0*b)/Y;
	args[2] = 0;
	args[1] = (2.0*X/(b*Y)) - (2.0/(b*Y)) + (2.0*b)/Y;
	args[0] = -1.0;
	rVal = rquartic_roots(args, r);
	if(rVal == 4){
		printf("%5.2g\t%2d\t%10.5g\t%10.5g\t%10.5g\t%10.5g\t%10.5g\t%10.5g\t%10.5g\t%10.5g\n", b, rVal, r[1], 2.0*atan(r[1]), r[2], 2.0*atan(r[2]), r[3], 2.0*atan(r[3]), r[4], 2.0*atan(r[4]));
	} else {
		printf("%5.2g\t%2d\t%10.5g\t%10.5g\t%10.5g\t%10.5g\t%10.5g\t%10.5s\t%10.5g\t%10.5s\n", b, rVal, r[1], 2.0*atan(r[1]), r[2], 2.0*atan(r[2]), r[3], "cplx", r[4], "cplx");
	}
	//d1 = 71492000.0*sqrt( (X-cos(2.0*atan(r[0])))*(X-cos(2.0*atan(r[0]))) + (Y-b*sin(2.0*atan(r[0])))*(Y-b*sin(2.0*atan(r[0]))) );
	//d2 = 71492000.0*sqrt( (X-cos(2.0*atan(r[1])))*(X-cos(2.0*atan(r[1]))) + (Y-b*sin(2.0*atan(r[1])))*(Y-b*sin(2.0*atan(r[1]))) );
	dX = X-cos(2.0*atan(r[1]));
	dY = Y-b*sin(2.0*atan(r[1]));
	theta1 = atan(dX/dY);
	//printf("d1_X = %20.16g\td1_Y = %20.16g\n", dX, dY);
	d1 = 71492000.0*sqrt(dX*dX + dY*dY);
	dX = X-cos(2.0*atan(r[2]));
	dY = Y-b*sin(2.0*atan(r[2]));
	theta2 = atan(dX/dY);
	d2 = 71492000.0*sqrt(dX*dX + dY*dY);
	//printf("d2_X = %20.16g\td2_Y = %20.16g\n", dX, dY);
	printf("d1 = %20.13g\nd2 = %20.13g\n", d1, d2);
	printf("theta 1 = %20.13g rad\t%20.13g deg\ntheta 2 = %20.13g rad\t%20.13g deg\n", theta1, theta1*180.0/M_PI, theta2, theta2*180.0/M_PI);
}