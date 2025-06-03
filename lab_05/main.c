#include <stdio.h>
#include <stdlib.h>
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

    int b[10];
    int a1[40*4];

    if(myrank == 2)
    {
        int a[10*nprocs*4];
        for(int i = 0; i < 10*nprocs*4; i++)
            a[i]=rand()%101;
        for(int i = 0; i < 10; i++)
            b[i]=rand()%201;
        
        MPI_Scatter( a, 10*4, MPI_INT,
                     a1, 10*4, MPI_INT,
                     2, MPI_COMM_WORLD );
    } else {
        MPI_Scatter( NULL, 10*4, MPI_INT,
                     a1, 10*4, MPI_INT,
                     2, MPI_COMM_WORLD );
    }

    MPI_Bcast( b, 10, MPI_INT, 2, MPI_COMM_WORLD );

    printf("[%2d] B=", myrank);
    for(int i = 0; i < 10; i++)
        printf("%6d", b[i]);
    printf(" [%2d] \n", myrank);

    int c[4];
    for(int i=0; i<4; i++)
    {
        int tmp = 0;
        for(int j=0; j<10; j++)
            tmp += b[j]*a1[i*10 + j];
        c[i] = tmp;
    }

    printf("[%2d] C=", myrank);
    for(int i = 0; i < 4; i++)
        printf("%6d", c[i]);
    printf(" [%2d] \n", myrank);

    if(myrank == 2)
    {
        int c0[4*nprocs];

        MPI_Gather( c, 4, MPI_INT,
                    c0, 4, MPI_INT,
                    2, MPI_COMM_WORLD );
        
        printf("[%2d] C0=", myrank);
        for(int i = 0; i < 4*nprocs; i++)
            printf("%6d[%2d]", c0[i], i);
        printf(" [%2d] \n", myrank);
    } else {
        MPI_Gather( c, 4, MPI_INT,
                    NULL, 4, MPI_INT,
                    2, MPI_COMM_WORLD );
    }


    // Освобождение подсистемы MPI
    MPI_Finalize();

    return 0;
}