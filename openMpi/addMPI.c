#include <stdio.h>
#include <mpi.h>


int main(int argc, char* argv[]){
    int id,taille,i,somme;

    MPI_Init (&argc, &argv);
    MPI_Comm_rank (MPI_COMM_WORLD, &id);
    MPI_Comm_size (MPI_COMM_WORLD, &taille);

    i=id+1;

    MPI_Reduce(&i, &somme, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (id == 0)
        printf("La reduction des valeurs donne %d\n", somme);

    MPI_Finalize();

    return 0;

}