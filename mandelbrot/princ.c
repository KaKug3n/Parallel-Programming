/* princ.c 
 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/timeb.h>

#include <time.h>

#include "mandelbrot.h"

int main(void){
	/* pour le temps */
	clock_t start, stop;
	double total, CPU_time;
	double te;

	initialise();  /* initialisation des parametres */

	start = clock();
	calculImage(); /* calcul de l'image */
	stop = clock();

	total = (double) (stop - start);
	CPU_time = total / CLOCKS_PER_SEC;
	printf("Temps 		: %f\n",  total);
	printf("Temps CPU	: %f\n",  CPU_time);

	sauvegarde();  /* creation de l'image au format tga */
	return 0;
}
