#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 100000000

int main(int argc, char* argv[])
{
    int *a;
    a = (int*) malloc(SIZE *sizeof(int));
    for(int i = 0; i < SIZE; i++)
        a[i] = rand()%101 -30;

    double time = omp_get_wtime();
    long int sum =0;
    for(int i = 0; i < SIZE; i++)
        sum += a[i];

    time = omp_get_wtime() - time;

    printf("seq  sum = %15ld time = %15.12lf\n", sum, time);
//---
    time = omp_get_wtime();
    sum = 0;

    #pragma omp parallel for default(none) shared(sum, a)
    for(int i = 0; i < SIZE; i++)
        sum += a[i];

    time = omp_get_wtime() - time;
    printf("par1  sum = %15ld time = %15.12lf\n", sum, time);
//---
    time = omp_get_wtime();
    sum = 0;

    #pragma omp parallel default(none) shared(sum, a) num_threads(4)
    {
        int mt = omp_get_thread_num();
        long int s1 = 0;

        #pragma omp for
        for(int i = 0; i < SIZE; i++)
        {
            s1 += a[i];
        }

        #pragma omp atomic
        sum +=s1;

        printf("thread = %d s1 = %15ld\n", mt, s1);

    }
    time = omp_get_wtime() - time;
    printf("par2  sum = %15ld time = %15.12lf\n", sum, time);

    return 0;
}