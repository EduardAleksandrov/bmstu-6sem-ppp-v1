#include <stdio.h>
#include <mpi.h>

int main(int argc, char ** argv) {
    int myrank, nprocs, len;
    char name[MPI_MAX_PROCESSOR_NAME];

    // Инициализация подсистемы MPI
    MPI_Init(&argc, &argv);

    // Получить размер коммуникатора MPI_COMM_WORLD (общее число процессов в рамках задачи)
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    // Получить номер текущего процесса в рамках коммуникатора MPI_COMM_WORLD
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Get_processor_name(name, &len);

    printf("Hello from host %s[%d] %d of %d\n", name, len, myrank, nprocs);

    // Освобождение подсистемы MPI
    MPI_Finalize();

    return 0;
}
