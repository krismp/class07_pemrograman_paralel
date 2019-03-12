#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int numnodes;
int main(int argc, char *argv[])
{
    int rank, i;
    int *data_send, *data_recv;
    float num;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numnodes);

    data_send = (int *)malloc(sizeof(int) * numnodes);
    data_recv = (int *)malloc(sizeof(int) * numnodes);

    srand(rank);
    for (i = 0; i < numnodes; i++)
    {
        num = (float)rand() / RAND_MAX;
        data_send[i] = (int)(10.0 * num) + 1;
    }

    printf("Rank= %d Data dikirim  =", rank);
    for (i = 0; i < numnodes; i++)
        printf("%d ", data_send[i]);
    printf("\r\n");

    MPI_Alltoall(data_send, 1, MPI_INT,
                 data_recv, 1, MPI_INT,
                 MPI_COMM_WORLD);

    printf("Rank= %d Data diterima =", rank);
    for (i = 0; i < numnodes; i++)
        printf("%d ", data_recv[i]);
    printf("\r\n");

    MPI_Finalize();
    return 0;
}