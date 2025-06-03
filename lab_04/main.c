#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define SIZE 1024

int main(int argc, char **argv) {
    int myrank, nprocs, len;
    char name[MPI_MAX_PROCESSOR_NAME];
    int *buf;
    MPI_Status st;
    double times[10];
    double data[10];

    buf = (int *) malloc(sizeof(int) * (SIZE * 1024 + 100));

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Get_processor_name(name, &len);

    printf("Hello from processor %s[%d] %d of %d\n", name, len, myrank, nprocs);

    if (myrank % 2 == 0) {
        if (myrank < nprocs - 1) {
            int i, cl, sz = SIZE;
            double time;
            MPI_Request re[2];
            MPI_Status st[2];
            int* buf0, *buf1;

            for (i = 0; i < SIZE * 1024; i++) {
                buf[i] = i + 10;
            }

            buf0 = buf;
            buf1 = (int*) malloc ( sizeof(int)*(SIZE*1024 + 100) );

            for (cl = 0; cl < 11; cl++) {
                time = MPI_Wtime();
                for (i = 0; i < 100; i++) {
                    MPI_Issend(buf0, sz, MPI_INT, myrank+1, 10, MPI_COMM_WORLD, &re[0]);
                    MPI_Irecv( buf1, sz+100, MPI_INT, myrank+1, 20, MPI_COMM_WORLD, &re[1]);
                    MPI_Waitall(2,re,st);
                    buf = buf0;
                    buf0=buf1;
                    buf1=buf;
                }
                time = MPI_Wtime() - time;
                printf(
                    "[%d] Time = %lf  Data = %9.0f KByte\n",
                    myrank,
                    time,
                    sz * sizeof(int) * 200.0 / 1024
                );
                printf(
                    "[%d] Bandwith[%d] = %lf MByte/sec\n",
                    myrank,
                    cl,
                    sz * sizeof(int) * 200 / (time * 1024 * 1024)
                );
                times[cl] = time;
                data[cl] = ((double) sz)*sizeof(int)*200.0/(1024.0*1024.0);
                sz *= 2;
            }
            free(buf0);
            free(buf1);
        }
        else {
            printf("[%d] Idle\n", myrank);
        }
    }
    else {
        int i, cl, sz = SIZE;
        
        MPI_Request re[2];
        MPI_Status st[2];
        int* buf0, *buf1;

        for (i = 0; i < SIZE * 1024; i++)
            buf[i] = i*10 + 100;

        buf0 = buf;
        buf1 = (int*) malloc ( sizeof(int)*(SIZE*1024 + 100) );

        for (cl = 0; cl < 11; cl++) {
            for (i = 0; i < 100; i++) {
                MPI_Issend(buf0, sz, MPI_INT, myrank-1, 20, MPI_COMM_WORLD, &re[0]);
                MPI_Irecv( buf1, sz+100, MPI_INT, myrank-1, 10, MPI_COMM_WORLD, &re[1]);
                MPI_Waitall(2,re,st);
                
                buf = buf0;
                buf0=buf1;
                buf1=buf;
            }
            sz *= 2;
        }
        free(buf0);
        free(buf1);
    }

    MPI_Finalize();
    
    return 0;
}