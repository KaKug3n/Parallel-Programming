#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


//taille du pb
#define N 7

FILE * f;
int nb=0;



int maxPos[N+1];


void recursLangford(int tableau[2*N+1],int maxPos[N+1],int tabPos[N+1],int etage){
    if(etage==0){
        //Solution
        
        #pragma omp atomic
        nb++;

        //Enregistrement

        /* WIP
        for(int i=1;i<=N*2;i++){
            fprintf(f,"%d" ,tableau[i]);
        }
            fprintf(f,"\n");
        */
    }
    else if(etage<=N){

        for(int i=1;i<=maxPos[etage];i++){

            if(tableau[i]==0 && tableau[i+etage+1]==0){

                //Assignation
                tableau[i]=etage;
                tableau[i+etage+1]=etage;
                
                //MAJ tabPos
                tabPos[etage]=i;

                //Test sur suivant
                recursLangford(tableau,maxPos,tabPos,etage-1);

                //Backtracking
                tableau[tabPos[etage]]=0;
                tableau[tabPos[etage]+etage+1]=0;
                tabPos[etage]=0;

            }
        }
    }

}


int main(){

    int nbTMax=1;

    int tableau[2*N+1];

    int tabPos[N+1];

    int maxPos[N+1];

    //tester la sym pour s'arrêter avant
    for(int i=1;i<=N;i++){
        maxPos[i]=2*N-1-i;

        tabPos[i]=0;

        tableau[i]=0;
        tableau[i+N]=0;
    }

        if(N%2==1){
        maxPos[N]=(N-1)/2;
    }
    else{
        maxPos[N-1]=N/2;
    }

    //Calcul du nombre de tâche complête
    int nbTMax=1;
    for(int i=1;i<N+1;i++){
        nbTMax=nbTMax*maxPos[i];
    }

    int **tabTacheMax;
    tabTacheMax=malloc(sizeof(int)*nbTMax);
    for(int i=1;i<nbTMax;i++){
        tabTacheMax[i]=malloc(sizeof(int)*(N/2));
    }

    for(int i=1;i<nbTMax;i++){
        for(int y=0;y<N/2;y++){
            for(int z=1;z<maxPos[y];z++){
                //ici algo pour éliminé les taches de trop
                
                tabTacheMax[i][y]=z;
            }
        }

    }





}