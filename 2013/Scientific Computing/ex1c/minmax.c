#include<stdio.h>
#include<math.h>
#include"header.h"

double max(double v1, double v2){
	if (v1 < v2){
		return(v2);
	} else if (v1 > v2) {
		return(v1);
	} else {
		return(v1);
	}
}

double min(double v1, double v2){
	if (v1 > v2){
		return(v2);
	} else if (v1 < v2) {
		return(v1);
	} else {
		return(v1);
	}
}

int compare_dbl(const void *x, const void *y){
	double *v1 = (double *)x;
	double *v2 = (double *)y;
	if (*v1 < *v2){
		return(-1);
	} else if (*v1 > *v2){
		return(1);
	} else {
		return(0);
	}
}

double amax(double* vals, int siz){
	double maxval;
	int i;
	maxval = vals[0];
	for(i = 1; i < siz; i++){
		if(vals[i] > maxval){
			maxval = vals[i];
		}
	}
	return(maxval);
}

double amin(double* vals, int siz){
	double minval;
	int i;
	minval = vals[0];
	for(i = 1; i < siz; i++){
		if(vals[i] < minval){
			minval = vals[i];
		}
	}
	return(minval);
}

double mid(double v1, double v2, double v3){
	if (v1 < v2 && v2 < v3 || v3 < v2 && v2 < v1){
		return(v2);
	} else if (v2 < v1 && v1 < v3 || v3 < v1 && v1 < v2){
		return(v1);
	} else if (v1 < v3 && v3 < v2 || v2 < v3 && v3 < v1){
		return(v3);
	} else {
		return(v1);
	}
}

double absval(double v){
	if (v > 0){
		return(v);
	} else if (v < 0){
		return(-v);
	} else if (v == 0){
		return(0);
	}
}

double n_raph_quart(double args[4], double init, int num_iter){
	double x;
	int i;
	x = init;
	for(i = 0; i < num_iter; i++){	
		x = x - (x*x*x*x + args[3]*x*x*x + args[2]*x*x + args[1]*x + args[0])/(4.0*x*x*x + 3.0*args[3]*x*x + 2.0*args[2]*x + args[1]);
	}
	return(x);
}

double n_raph_cub(double args[3], double init, int num_iter){
	double x;
	int i;
	x = init;
	for(i = 0; i < num_iter; i++){	
		x = x - (x*x*x + args[2]*x*x + args[1]*x + args[0])/(3.0*x*x + 2.0*args[2]*x + args[1]);
	}
	return(x);
}

double n_raph_quad(double args[3], double init, int num_iter){
	double x;
	int i;
	x = init;
	for(i = 0; i < num_iter; i++){	
		x = x - (args[2]*x*x + args[1]*x + args[0])/(2.0*args[2]*x + args[1]);
	}
	return(x);
}

double n_raph_lin(double args[2], double init, int num_iter){
	double x;
	int i;
	x = init;
	for(i = 0; i < num_iter; i++){	
		x = x - (args[1]*x + args[0])/(args[1]);
	}
	return(x);
}































