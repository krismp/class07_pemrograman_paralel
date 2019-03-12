#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int numnodes, rank;
int main(int argc, char *argv[])
{
    int size, i;
    int *myray, *send_data, *back_data;
    int N, total, sum_total;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numnodes);

    N = 4;
    myray = (int *)malloc(N * sizeof(int));
    size = N * numnodes;
    send_data = (int *)malloc(size * sizeof(int));
    back_data = (int *)malloc(numnodes * sizeof(int));

    if (rank == 0)
    {
        for (i = 0; i < size; i++)
            send_data[i] = i;
    }

    MPI_Scatter(send_data, N, MPI_INT,
                myray, N, MPI_INT,
                0, MPI_COMM_WORLD);
    total = 0;
    for (i = 0; i < N; i++)
        total = total + myray[i];
    printf("rank= %d data= %d\r\n", rank, total);

    MPI_Reduce(&total, &sum_total, 1, MPI_INT,
               MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        printf("Jumlah total data = %d \r\n", sum_total);
    }

    MPI_Finalize();
    return 0;
}