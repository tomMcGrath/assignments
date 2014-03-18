#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include"McGrath.h"

int main(void){
	double **t, **tmp, *tmpRow;
	int len, i, j;

	len = 8;
	t = make_matrix(len, len);
	tmp = make_matrix(2*len, 2*len);

	for(i = 0; i <= 0.25*len; i++){
		for(j = 0; j <= 0.25*len; j++){
			t[i][j] = 40.0;
		}
	}

	displayMatrix(t, len);

	printf("ITERATE\n");
	printf("1\n");
	for(i = 0; i <= len; i++){
		if(t[i] != NULL){
			for(j = 0; j < len; j++){
				printf("%5.5g\t", t[i][j]);
				tmp[i][j] = t[i][j];
			}
			printf("\n");
		}
		if(t[i] == NULL){
			printf("%d NULL\n", i);
		}
	}
	free(t[0]);
	free(t);

	len *=2;
	t = make_matrix(len, len);
	for(i = 0; i <= len; i++){
		for(j = 0; j <= len; j++){
			t[i][j] = tmp[i][j];
		}
	}

	displayMatrix(t,len);

	free(tmp[0]);
	free(tmp);
/*
	printf("ITERATE\n");
	tmp = realloc(t, (len+1)*sizeof(double*));
	for(i = 0; i <= len; i++){
		printf("1\n");
		tmpRow = malloc((len+1)*sizeof(double));
		printf("2\n");
		for(j = 0; j < 
		printf("3\n");
		//free(t[i]);
		printf("4\n");
		t[i] = malloc((len+1)*sizeof(double));
		printf("5\n");
		memcpy(t[i], tmpRow, (len+1)*sizeof(double));
		printf("6\n");
	}
	// so there is a problem here - need to malloc() the new data, and realloc() the old?
	//t = realloc(t, (len+1)*sizeof(double*));
*/

}

double **make_matrix(int NR, int NC){ // from lecture notes
	double **Array;
	int N, i, j;
	N = NC;

	Array = (double **)malloc((N+1)*sizeof(double *));
	Array[0]=(double*)malloc((N+1)*(N+1)*sizeof(double));
	for(i=1;i<=N;i++)Array[i]=Array[i-1]+N+1;

	// assigning values to Array, etc.
	for(i=0;i<=N;i++)for(j=0;j<=N;j++)Array[i][j]=0;

	return(Array);
}

void displayMatrix(double ** M, int len){
	int i, j;
	for(i = 0; i <= len; i++){
		for(j = 0; j <= len; j++){
			printf("%3g\t", M[i][j]);
		}
	printf("\n");
	}
}

