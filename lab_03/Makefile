	
compile:
	mpicc main1.c -o main1.out
	mpicc main2.c -o main2.out
	mpicc main3.c -o main3.out
	mpicc main4.c -o main4.out

run1: compile
	mpirun -np 8 main1.out

run2: compile
	mpirun -np 8 main2.out

run3: compile
	mpirun -np 8 main3.out

run4: compile
	mpirun -np 8 main4.out

run_on_nodes: compile
	sbatch run.sh
