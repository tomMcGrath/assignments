#include <stdio.h>
#include <float.h>
#include <quadmath.h>

int main(void)
{
	double a1 = DBL_MAX;
	double a2;
	printf("Name: <Tom McGrath>\n");
	printf("CID: <00898098>, LIBRARY NO: <0246656362>\n");
	printf("Email Address: <t.mcgrath13@imperial.ac.uk>\n");
	printf("Course Code: <M5SC>\n");
	printf("DBL_EPSILON = %.10e\n", DBL_EPSILON);
	printf("DBL_MAX = %.10e\n", DBL_MAX);
	printf("DBL_MIN = %.10e\n", DBL_MIN);
	printf("LDBL_EPSILON = %.10Le\n", LDBL_EPSILON);
	printf("LDBL_MAX = %.10Le\n", LDBL_MAX);
	printf("LDBL_MIN = %.10Le\n", LDBL_MIN);
	printf("%.10g\n", a1);
	return(0);
}
