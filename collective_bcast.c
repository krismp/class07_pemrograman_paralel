#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int rank, val;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    printf("Proses rank: %d \r\n", rank);

    if (rank == 0)
        val = 100;

    MPI_Bcast(&val, 1, MPI_INT, 0, MPI_COMM_WORLD);
    printf("Rank %d, Total val = %d\r\n", rank, val);

    MPI_Finalize();
    return 0;
}