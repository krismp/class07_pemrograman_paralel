#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int N = 5;
    int *in, *out;
    int i, rank, size;
    float num;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    in = (int *)malloc(N * sizeof(int));
    out = (int *)malloc(N * sizeof(int));

    printf("Rank %d in= ", rank);
    srand(rank);
    for (i = 0; i < N; i++)
    {
        num = (float)rand() / RAND_MAX;
        in[i] = (int)(10.0 * num) + 1;
        printf("%d ", in[i]);
    }
    printf("\r\n");

    MPI_Allreduce(in, out, N, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    printf("Rank %d out= ", rank);
    for (i = 0; i < N; i++)
    {
        printf("%d ", out[i]);
    }
    printf("\r\n");

    MPI_Finalize();
    return 0;
}