#include <stdio.h>
#include <stdlib.h>

FILE * f;
int nb=0;

void recursLangford(int* tableau,int* maxPos,int* tabPos,int etage,int N){
    if(etage==0){

        //printf("solution:\n| ");
        nb++;
        /*
        //Enregistrement
        for(int i=1;i<=N*2;i++){
            fprintf(f,"%d" ,tableau[i]);
            //printf("%d ",tableau[i]);
        }
            fprintf(f,"\n");
            //printf("|\n");
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
                recursLangford(tableau,maxPos,tabPos,etage-1,N);

                //Backtracking
                tableau[tabPos[etage]]=0;
                tableau[tabPos[etage]+etage+1]=0;
                tabPos[etage]=0;

            }
        }

    }

}


int main(){

    //taille du pb
    int N=15;
        
    // t[0] flag et tab commence a t[1]
    int *tableau=malloc(sizeof(int)*(2*N+1));
    //memset oublie pas

    int *tabPos=malloc(sizeof(int)*(N+1));

    int *maxPos=malloc(sizeof(int)*(N+1));


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

    f=fopen("LANG_SEQ.log","w");



    for(int i=1;i<=maxPos[etage];i++){

        //Assignation
        tableau[i]=etage;
        tableau[i+etage+1]=etage;
        
        //MAJ tabPos
        tabPos[etage]=i;

        //Test sur suivant
        recursLangford(tableau,maxPos,tabPos,etage-1,N);

        //Backtracking
        tableau[tabPos[etage]]=0;
        tableau[tabPos[etage]+etage+1]=0;

    }

    printf("\nnb solution: %d\n",nb);

    fclose(f);

    free(tableau);
    free(tabPos);
    free(maxPos);
}