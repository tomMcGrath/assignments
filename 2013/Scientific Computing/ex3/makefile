all:
	gcc main.c functions.c McGrath.h -lm -o q1
	gcc q3.c functions.c McGrath.h -lm -o q3
	gcc q4.c functions.c McGrath.h -lm -o q4
	gcc q5.c functions.c  McGrath.h -lm -o q5
	gcc MQ.c functions.c McGrath.h -lm -o MQ

debug:
	gcc main.c functions.c McGrath.h -lm -o q1 -g
	gcc q3.c functions.c McGrath.h -lm -o q3 -g
	gcc q4.c function.c McGrath.h -lm -o q4 -g
	gcc q5.c functions.c  McGrath.h -lm -o q5 -g
	gcc MQ.c functions.c McGrath.h -lm  -o MQ -g

opt:
	icc main.c functions.c McGrath.h -lm -o q1 -O3
	icc q3.c functions.c McGrath.h -lm -o q3 -O3
	icc q4.c functions.c McGrath.h -lm -o q4 -O3
	icc q5.c functions.c  McGrath.h -lm -o q5 -O3
	icc MQ.c functions.c McGrath.h -lm -o MQ -O3

maxopt:
	icc main.c functions.c McGrath.h -lm -o q1 -O3 -xCORE-AVX2
	icc q4.c functions.c McGrath.h -lm -o q4 -O3 -xCORE-AVX2
	icc q5.c functions.c  McGrath.h -lm -o q5 -O3 -xCORE-AVX2
	icc MQ.c functions.c McGrath.h -lm -o MQ -O3 -xCORE-AVX2
