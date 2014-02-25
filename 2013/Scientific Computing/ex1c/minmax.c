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
