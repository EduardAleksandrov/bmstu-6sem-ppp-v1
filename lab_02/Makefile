	
compile:
	mpicc main.c -o main.out

run: compile
	mpirun -np 8 main.out

run_on_nodes: compile
	sbatch run.sh
