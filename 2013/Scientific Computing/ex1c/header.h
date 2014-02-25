#include<complex.h>
int lin_root(double [], double []);
int quad_roots(double [], double []);
int rcubic_roots(double [], double []);
int rquartic_roots(double *, double *);
int complex_quad(complex double, complex double, complex double, complex double*, complex double*);
int complex_cubic(complex double, complex double, complex double, complex double*, complex double*, complex double*);
int complex_lin_root(complex double, complex double, complex double*);
double calcQ(double, double);
double calcR(double, double, double);
double max(double, double);
double min(double, double);
int compare_dbl(const void *, const void *);
double amax(double *, int);
double amin(double *, int);
double mid(double, double, double);
double absval(double);
