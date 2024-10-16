#include <stdio.h>
#include <mpi.h>


int main(int argc, char* argv[]){
    int id,taille,i,somme;
    MPI_Status statut;

    MPI_Init (&argc, &argv);
    MPI_Comm_rank (MPI_COMM_WORLD, &id);
    MPI_Comm_size (MPI_COMM_WORLD, &taille);

    i=id+1;

    if(id==taille-1){
        somme=i;
        MPI_Send(&somme,1,MPI_INT,id-1,0,MPI_COMM_WORLD);
    }
    else if(id == 0){
        MPI_Recv(&somme,1,MPI_INT,id+1,0,MPI_COMM_WORLD,&statut);
        somme+=i;
        printf("La reduction torique des valeurs donne %d\n", somme);
    }
    else{
        MPI_Recv(&somme,1,MPI_INT,id+1,0,MPI_COMM_WORLD,&statut);
        somme+=i;
        MPI_Send(&somme,1,MPI_INT,id-1,0,MPI_COMM_WORLD);
    }
    

    MPI_Finalize();

    return 0;

}