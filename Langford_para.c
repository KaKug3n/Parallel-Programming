#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>


//taille du pb
#define N 16
#define tailleTache N/2

FILE * f;
long long nb=0;

void recursLangford(int tableau[2*N+1],int maxPos[N+1],int tabPos[N+1],int etage){
    if(etage==0){

        //verification qu il n y a pas de 0 
        for(int i=1;i<=2*N;i++){
            if(tableau[i]==0){
                return;
            }
        }

        #pragma omp atomic
        nb++;
    }
    else{
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

void Lanford(int maxPos[N+1],int tache){
    int tabTache[tailleTache];

    int temp = tache;
    for (int j = 0; j < tailleTache; j++) {
        tabTache[j] = temp % (maxPos[N-j] + 1);
        temp /= (maxPos[N-j] + 1);
    }

    //construction du tableau a partir de la tache
    int tableau[2*N+1];
    memset(tableau,0,sizeof(int)*(2*N+1));
    int tabPos[N+1];
    for(int i=0;i<tailleTache;i++){
        if(tableau[tabTache[i]+1]==0 && tableau[tabTache[i]+(N-i)+2]==0){

            tableau[tabTache[i]+1]=N-i;
            tableau[tabTache[i]+(N-i)+2]=N-i;
            tabPos[N-i]=tabTache[i];
        }
        else{
            //erreur
            return;
        }
    }

    //Resolution du pb de Langford
    recursLangford(tableau,maxPos,tabPos,N-(tailleTache));
}


int main(){

    int nbTMax=1;

    int tabPos[N+1];

    int maxPos[N+1];

    //tester la sym pour s'arrêter avant
    for(int i=1;i<=N;i++){
        maxPos[i]=2*N-1-i;

        tabPos[i]=0;
    }

    if(N%2==1){
        maxPos[N]=(N-1)/2-1;
    }
    else{
        maxPos[N-1]=N/2-1;
    }
    //affichage de maxPos  
    printf("maxPos: ");
    for(int i=1;i<=N;i++){
        printf("%d ",maxPos[i]);
    }
    printf("\n");

    // Calcul du nombre de tâches complètes
    for (int i = 0; i < tailleTache; i++) {
        nbTMax *= (maxPos[N - i] + 1);
    }
    printf("nb tache: %d\n",nbTMax);

    //Lancement des tâches
    #pragma omp parallel for
    for(int i=0;i<nbTMax;i++){
        Lanford(maxPos,i);
    }

    printf("Nombre de solutions : %lld\n",nb);
}