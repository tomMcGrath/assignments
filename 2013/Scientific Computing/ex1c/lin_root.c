#include<stdio.h>
#include<math.h>
#include"header.h"

/*
int main(void) {
	double t1;
	double a1, a0;
	printf("Name: <Tom McGrath>\n");
	printf("CID: <00898098>, LIBRARY NO: <0246656362>\n");
	printf("Email Address: <t.mcgrath13@imperial.ac.uk>\n");
	printf("Course Code: <M5SC>\n");
	scanf("%lf %lf", &a1, &a0);
	lin_root(a1,a0,&t1);
	printf("%e\n", t1);
}
*/

int lin_root(double args[2], double r1[1]){
	double A = args[1];
	double B = args[0];
	if (A == 0 && B == 0){
		return(-1); // any x will satisfy this
	} else if (A == 0 && B != 0){
		return(0); // no x will satisfy this
	} else if (A != 0 && B != 0){
		r1[0] = -B/A;
		return(1);
	}
}
