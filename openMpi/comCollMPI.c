#include <stdio.h>
#include <mpi.h>
#include <stdlib.h> 
#include <time.h>


int main(int argc, char* argv[]){

    int id,taille;

    float tab[5];

    float x;
    float xmax;

    int nb=0;
    int nbmax;
    int nbTot;

    MPI_Status statut;

    MPI_Init (&argc, &argv);
    MPI_Comm_rank (MPI_COMM_WORLD, &id);
    MPI_Comm_size (MPI_COMM_WORLD, &taille);

     srand( id+time(NULL) );
     for(int i=0;i<5;i++){
        tab[i]=(float)(rand()%20);
     }

     if(id==0){
        x=(float)(rand()%20);
     }
     MPI_Bcast(&x,1,MPI_FLOAT,0,MPI_COMM_WORLD);

     for(int i=0;i<5;i++){
        if(tab[i]>x){
            nb++;
        }
     }

     printf("%d processus\ntab: | %f %f %f %f %f |\nnb total: %d\n\n",id,tab[0],tab[1],tab[2],tab[3],tab[4],nb);
     fflush(stdout);

     MPI_Reduce(&nb, &nbmax, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
     MPI_Reduce(&nb, &nbTot, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

     MPI_Barrier(MPI_COMM_WORLD);

     if(id==0){
        printf("Le nbmax est de %d\n", nbmax);
        printf("Le nb total est de %d\n", nbTot);
     }

    MPI_Finalize();

    return 0;

}