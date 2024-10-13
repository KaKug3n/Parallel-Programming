#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


//taille du pb
#define N 7

FILE * f;
int nb=0;

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

    int i;
        
    // t[0] flag et tab commence a t[1]
    int tableau[2*N+1];
    //memset oublie pas

    int tabPos[N+1];
    int maxPos[N+1];

    int etage=N;

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

    printf("START\n");

    //f=fopen("LANG_SEQ.log","w");

    #pragma omp parallel \
                        private(i,tableau,tabPos,etage) shared(nb,maxPos)
    {

        etage=N;

        #pragma omp for 
        for(i=1;i<=maxPos[N];i++){


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

        }

    }

    //printf("\nnb solution: %d\n",nb);

    fclose(f);
}