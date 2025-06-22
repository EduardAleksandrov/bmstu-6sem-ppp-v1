version:
	echo |cpp -fopenmp -dM |grep -i open

compile:
	gcc -O2 -fopenmp main.c -o main.out 

run: compile
	./main.out

run_threads: compile
	OMP_NUM_THREADS=4 ./main.out

