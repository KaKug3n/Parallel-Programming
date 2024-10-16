#include <stdio.h>
#include <mpi.h>


int main(int argc, char* argv[]){
    int id,taille;

    MPI_Init (&argc, &argv);
    MPI_Comm_rank (MPI_COMM_WORLD, &id);
    MPI_Comm_size (MPI_COMM_WORLD, &taille);

    printf( "Hello world du processus %d de %d\n", id, taille );

    MPI_Finalize();

    return 0;

}