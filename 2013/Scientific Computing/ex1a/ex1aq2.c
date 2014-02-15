#include<stdio.h>
#include<math.h>
#define double float


int quad_roots(double, double , double, double*, double*);
int quad_roots_inaccurate(double, double , double, double*, double*);


int main(void)
{
	double t1, t2;
	double t3, t4;
	double a2,a1, a0;
	double diam_E = 12742000; // Earth's diameter in metres, because we're using 2R in the formula
	double diam_M = 3474200; // Moon's diameter in metres
	printf("Name: <Tom McGrath>\n");
	printf("CID: <00898098>, LIBRARY NO: <0246656362>\n");
	printf("Email Address: <t.mcgrath13@imperial.ac.uk>\n");
	printf("Course Code: <M5SC>\n");
	printf("A camera must be at height h above the Earth's surface to see a horizon at distance d\n");
	printf("d \t h (acccurate) \t h (inaccurate)\n");

	quad_roots(1, diam_E, -1, &t1, &t2);
	quad_roots_inaccurate(1, diam_E, -1, &t3, &t4);
	printf("%11d \t %10.12g \t %10.12g\n", 1, t1, t3);

	quad_roots(1, diam_E, -10000, &t1, &t2); // remember d^2
	quad_roots_inaccurate(1, diam_E, -10000, &t3, &t4);
	printf("%11d \t %10.12g \t %10.12g\n", 10000, t1, t3);

	quad_roots(1, diam_E, -1000000, &t1, &t2);
	quad_roots_inaccurate(1, diam_E, -1000000, &t3, &t4);
	printf("%11d \t %10.12g \t %10.12g\n", 1000000, t1, t3);

	quad_roots(1, diam_E, -10000000000, &t1, &t2);
	quad_roots_inaccurate(1, diam_E, -10000000000, &t3, &t4);
	printf("%11ld \t %10.12g \t %10.12g\n", 10000000000, t1, t3);

	printf("A camera must be at height h above the Moon's surface to see a horizon at distance d\n");
	printf("d \t h (accurate) \t h (inaccurate)\n");
	quad_roots(1, diam_M, -1, &t1, &t2);
	quad_roots_inaccurate(1, diam_M, -1, &t3, &t4);
	printf("%11d \t %10.12g \t %10.12g\n", 1, t1, t3);

	quad_roots(1, diam_M, -10000, &t1, &t2); // remember d^2
	quad_roots_inaccurate(1, diam_M, -10000, &t3, &t4);
	printf("%11d \t %10.12g \t %10.12g\n", 10000, t1, t3);

	quad_roots(1, diam_M, -1000000, &t1, &t2);
	quad_roots_inaccurate(1, diam_M, -1000000, &t3, &t4);
	printf("%11d \t %10.12g \t %10.12g\n", 1000000, t1, t3);

	quad_roots(1, diam_M, -10000000000, &t1, &t2);
	quad_roots_inaccurate(1, diam_M, -10000000000, &t3, &t4);
	printf("%11ld \t %10.12g \t %10.12g\n", 10000000000, t1, t3);
}

int quad_roots(double a2, double a1, double a0, double* r1, double* r2)
{
	double disc;
	int four, two;
	four = 4;
	two = 2;

	if(a2 == 0 && a1 != 0)
	{		
		return(1); // linear equation has 1 real root
	}
	else if (a2== 0 && a1 == 0)
	{
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
			if(a1 > 0)
			{			
				*r2 = (-a1 - sqrt(disc))/(two*a2); // avoid loss of significance by subtracting different signs
				*r1 = (a0)/(*r2*a2);
				return(2);
			}
			else if (a1 <= 0)
			{
				*r1 = (-a1 + sqrt(disc))/(two*a2); // we need to calculate the other root first this time
				*r2 = (a0)/(*r1*a2);
				return(2);
			}
		}
		else if(disc < 0)
		{
			// handle complex conjugate roots
			return(0); // we want _real_ roots
		}
		else
		{
			printf("You have a problem!"); // we should never get here
		}
	}	
}

int quad_roots_inaccurate(double a2, double a1, double a0, double* r1, double* r2)
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
