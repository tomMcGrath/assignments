#include<stdio.h>
#include<math.h>

int quad_roots(double, double , double, double*, double*);

int main(void)
{
	double t1;
	double t2;
	double a2,a1, a0;
	printf("Name: <Tom McGrath>\n");
	printf("CID: <00898098>, LIBRARY NO: <0246656362>\n");
	printf("Email Address: <t.mcgrath13@imperial.ac.uk>\n");
	printf("Course Code: <M5SC>\n");
}

int quad_roots(double a2, double a1, double a0, double* r1, double* r2)
{
	double disc;
	int four, two;
	four = 4;
	two = 2;

	if(a2 == 0 && a1 != 0)
	{
		printf("Linear equation %lfx + %lf = 0 has root x = %lf\n", a1, a0, -(a0/a1));		
		return(1); // linear equation has 1 real root
	}
	else if (a2== 0 && a1 == 0)
	{
		printf("Equation is poorly specified, either have a0 = 0 or 0=0\n");
		return(0); // no roots, either have 0==0 (a0 = 0) or a0==0 (inconsistent)
	}
	
	else
	{
		disc = a1*a1 - four*a2*a0;
		if(disc == 0)
		{
			// handle 2 equal real roots
			*r1 = -(a1)/(two*a2);
			*r2 = -(a1)/(two*a2);
			return(1);
		}
		else if(disc > 0)
		{
			// handle 2 distinct real roots
			*r1 = (-a1 + sqrt(disc))/(two*a2);
			*r2 = (-a1 - sqrt(disc))/(two*a2);
			return(2);
		}
		else if(disc < 0)
		{
			// handle complex conjugate roots
			printf("Quadratic equation %lfx^2 + %lf x + %lf = 0 has 2 complex roots\n", a2, a1, a0);
			return(0); // we want _real_ roots
		}
		else
		{
			printf("Flow control error"); // we should never get here
			return(-3);
		}	
	}	
}
