#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size;
    int local_value, global_sum;

    // Инициализация MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Каждый процесс задает свое локальное значение
    local_value = rank + 1; // Например, процесс 0 имеет значение 1, процесс 1 - 2 и т.д.

    // Выполнение операции редукции: суммирование локальных значений
    MPI_Reduce(&local_value, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Процесс 0 выводит результат
    if (rank == 0) {
        printf("Сумма всех локальных значений: %d\n", global_sum);
    }

    // Завершение работы MPI
    MPI_Finalize();
    return 0;
}