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

double absval(double v){
	if (v > 0){
		return(v);
	} else if (v < 0){
		return(-v);
	} else if (v == 0){
		return(0);
	}
}
