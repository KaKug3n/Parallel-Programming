#include <stdio.h>
#include <stdlib.h>

#include <omp.h>
#include <time.h>
#include <unistd.h>



double alea(unsigned int seed) {
    return ((double)rand_r(&seed)) / RAND_MAX;
}


int main(int argc, char *argv[])
{
    //seed = time(NULL);
    int nb = 999999999; /* par exemple */
    double dedans = 0,resultDedans;
    unsigned int seed;
    int i=0;
    double x,y;

    #pragma omp parallel \
                private(seed,i,x,y,dedans) shared(resultDedans)
    {
    seed=omp_get_thread_num()+time(NULL);

    #pragma omp for //schedule(static,5)
    for (i = 0; i < nb; i++) {
        x = alea(seed);
        y = alea(seed);
        if ( x*x + y*y < 1){
            dedans++;
        }
    }

    #pragma omp atomic
    resultDedans+= dedans;

    }

    printf("approximation obtenue : %f\n",(double)resultDedans / nb);
    printf("approximation obtenue x4: %f\n",((double)resultDedans / nb)*4);

    return 0;
}