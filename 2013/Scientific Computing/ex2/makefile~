all:
	gcc q1.c McGrath.h -lm -o q1
	gcc q2.c McGrath.h -lm -o q2
	gcc q3.c McGrath.h -lm -o q3
	gcc test.c -lm -o test

mc:
	gcc q1.c McGrath.h -lm -o q1 -fopenmp
	gcc q2.c McGrath.h -lm -o q2 -fopenmp
	gcc q3.c McGrath.h -lm -o q3 -fopenmp
	gcc test.c -lm -o test -fopenmp

mcdb:
	gcc q1.c McGrath.h -lm -o q1 -fopenmp -g
	gcc q2.c McGrath.h -lm -o q2 -fopenmp -g
	gcc q3.c McGrath.h -lm -o q3 -fopenmp -g
	gcc test.c -lm -o test -fopenmp -g

opt:
	icc q1.c McGrath.h -lm -o q1 -O3
	icc q2.c McGrath.h -lm -o q2 -O3
	icc q3.c McGrath.h -lm -o q3 -O3
	icc test.c -lm -o test -O3

mptest:
	gcc mptest.c -lm -o mp -fopenmp
