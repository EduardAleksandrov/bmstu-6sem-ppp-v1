version:
	mpirun --version

compile:
	mpicc hello_mpi.c -o hello_mpi.out

run: compile
	mpirun -np 4 hello_mpi.out

run_on_nodes: compile
	sbatch run.sh

