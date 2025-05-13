#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Define a 2D array (4 rows, 3 columns)
    int array[4][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
        {10, 11, 12}
    };

    // Create a derived data type for the second column of the array
    MPI_Datatype column_type;
    MPI_Type_vector(4, 1, 3, MPI_INT, &column_type);
    MPI_Type_commit(&column_type);

    if (rank == 0) {
        // Process 0 sends the second column to Process 1
        MPI_Send(&array[0][1], 1, column_type, 1, 0, MPI_COMM_WORLD);
        printf("Process 0 sent the second column.\n");
    } else if (rank == 1) {
        int received_data[4]; // Buffer to receive the second column
        // Process 1 receives the second column
        MPI_Recv(received_data, 4, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1 received the second column: ");
        for (int i = 0; i < 4; i++) {
            printf("%d ", received_data[i]);
        }
        printf("\n");
    }

    // Free the derived data type
    MPI_Type_free(&column_type);

    MPI_Finalize();
    return 0;
}