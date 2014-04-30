double* SFactors(int);
double **make_matrix(int,int);
double **matrix_multiply(double **, double **, int, int, int, int);
double *mv_multiply(double **M, double *V, int m, int n, int k);
void displayMatrix(double **, int);
int FastSN(double *x, double *y, double *w, double *S, int N, int skip);
int FastTN(double *x, double *y, double *w, double *S, int N, int skip);
int FastUN(double *x, double *y, double *w, double *S, int N, int skip);
int SlowSN(double *x, double *y, double *w, double *S, int N, int skip);
int SlowTN(double *x, double *y, double *w, double *S, int N, int skip);
int SlowUN(double *x, double *y, double *w, double *S, int N, int skip);
void displayVector(double *, int);
void displayXYW(double *x, double *y, double *w, int N);
double signof(int n);
double timer(int);
int defineQ4(double *rho, int N);
int writeVector(double *V, int N, char *path);
int calcPsiBad(double *rho, double *psi, int N);
int calcPsiGood(double *rho, double *psi, int N);
int defineQ5(double **rho, int N);
int calcPsiGood2D(double **rho, double **psi, int N);
int writeMatrix(double **M, int len, char *path);
double ***make_tensor(int N1, int N2, int N3);
double amax(double *M, int len);
int argamax(double *M, int len);
double amax2D(double **M, int len);
double *argamax2D(double **M, int len, double pos[2]);
double amax3D(double ***M, int len);
double *argamax3D(double ***M, int len, double pos[3]);
int xMax2D(double **M, int len);
int yMax2d(double **M, int len);
int xMax3D(double ***M, int len);
int yMax3D(double ***M, int len);
int zMax3D(double ***M, int len);
