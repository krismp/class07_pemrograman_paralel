#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int numnodes;
int main(int argc, char *argv[])
{
    int rank;
    int *myray, *send_array, *back_array;
    int count;
    int size, i, total;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numnodes);

    // Siapkan data untuk proses scatter di mana jumlah data adalah 10*jumlah proses
    count = 10;
    size = count * numnodes;
    myray = (int *)malloc(count * sizeof(int));
    send_array = (int *)malloc(size * sizeof(int));
    back_array = (int *)malloc(numnodes * sizeof(int));

    if (rank == 0)
    {
        for (i = 0; i < size; i++)
            send_array[i] = i;
    }

    // Selanjutnya dilakukan proses MPI scatter pada rank 0
    MPI_Scatter(send_array, count, MPI_INT,
                myray, count, MPI_INT,
                0, MPI_COMM_WORLD);

    // Data yg di terima di jumlahkan lalu tampilkan di layar
    total = 0;
    for (i = 0; i < count; i++)
        total = total + myray[i];

    printf("Rank= %d Total= %d \r\n", rank, total);

    // Selanjutnya, nilai total akan menjadi input data pada proses MPI gather
    MPI_Gather(&total, 1, MPI_INT,
               back_array, 1, MPI_INT,
               0, MPI_COMM_WORLD);

    // Di sini penerima data ada pada rank 0, sehingga kita melakukan proses
    // penjumlahan semua data yg diterima pada rank 0
    if (rank == 0)
    {
        total = 0;
        for (i = 0; i < numnodes; i++)
            total = total + back_array[i];

        printf("Total dari proses= %d \r\n ", total);
    }

    MPI_Finalize();
    return 0;
}