#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int numnodes;
int main(int argc, char *argv[])
{
    int rank;
    int *back_array;
    int i, data;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numnodes);

    // Siapkan data untuk proses MPI gather-to-all
    data = rank + 1;
    printf("Rank= %d, Data= %d \r\n", rank, data);

    // MPI barrier supaya memastikan persiapan datanya
    // mencapai posisi yang sama sebelum eksekusi MPI gather-to-all
    MPI_Barrier(MPI_COMM_WORLD);
    back_array = (int *)malloc(numnodes * sizeof(int));

    // selanjutnya kita eksekusi MPI gather-to-all dan memanggil MPI_Barrier
    // Untuk memastikan proses sudah menerima data.
    MPI_Allgather(&data, 1, MPI_INT,
                  back_array, 1, MPI_INT,
                  MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);

    // Lalu tampilkan di layar hasilnya
    printf("Gather>> ");
    for (i = 0; i < numnodes; i++)
        printf("%d ", back_array[i]);
    printf("\r\n");

    MPI_Finalize();
    return 0;
}