#include<stdio.h>
#include"header.h"

int main(void) {
	double t1;
	double t2;
	double a2,a1, a0;
	printf("Name: <Tom McGrath>\n");
	printf("CID: <00898098>, LIBRARY NO: <0246656362>\n");
	printf("Email Address: <t.mcgrath13@imperial.ac.uk>\n");
	printf("Course Code: <M5SC>\n");
	printf("Enter quadratic root coeffs a2 a1 a0\n");
	scanf("%lf %lf %lf", &a2, &a1, &a0);
	quad_roots(a2,a1,a0,&t1,&t2);
	printf("%e %e\n", t1, t2);
	printf("Enter linear root coeffs a1 a0\n");
	scanf("%lf %lf", &a1, &a0);
	lin_root(a1, a0, &t1);
	printf("%e\n", t1);
}
