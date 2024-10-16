/*
	Crible d'Eratosthene
	Pierre Delisle
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include <mpi.h>

#define MIN(a,b)  ((a)<(b)?(a):(b))

int main (int argc, char *argv[]) {
	int n;				/* Dernier nombre premier a verifier (2..n) */
	size_t taille;		/* Taille du tableau de nombres premiers a verifier */
	bool *marques;		/* Tableau permettant de marquer les nombres verifies */
	int ind_k;			/* Index du nb premier courant dans le tableau "marques" */
	int k;				/* Nombre premier courant */
	int compte;			/* Compteur de nombres premiers */
	int ind_debut;		/* Indicateur de debut de marquage*/

	int id,tailleProc;

	int val_max,val_min;
	
	if (argc != 2) {  	/* Verifie que un seul argument a ete fourni */
		printf ("Usage : %s n\n", argv[0]);
		exit(1);
	}
	n = atoi(argv[1]);

	MPI_Init (&argc, &argv);
    MPI_Comm_rank (MPI_COMM_WORLD, &id);
    MPI_Comm_size (MPI_COMM_WORLD, &tailleProc);

	val_min=id*(n/tailleProc);
	val_max=((id+1)*n/tailleProc)-1;

	taille = val_max-val_min+1;

	marques = malloc(sizeof(bool[taille]));

	for (size_t i = 0; i < taille; ++i)
		marques[i] = false;
	ind_k = 0;
	k = 2;
	
	do {
		ind_debut = k * k - 2; 							/* Indice du 1er nombre a marquer (k2)*/
		for (size_t i = ind_debut; i < taille; i+= k)	/* Pour tous les multiples du nb premier, */
			marques[i] = true;							/* on marque le nombre*/
		while (marques[++ind_k]);						/* On trouve l'indice de la prochaine case non marquee */
		k = ind_k + 2;									/* ce qui donne le nb premier du prochain tour */
	} while (k * k <= n);								/* On arrete si son carre est > que n */

	compte = 0;
	for (size_t i = 0; i < taille; ++i)
		if (!marques[i])
			compte++;

	printf("Il y a %d nombres premiers plus petits ou egaux a %d\n", compte, n);
	printf("Ces nombres sont : ");
	for (size_t i = 0; i < taille; ++i)
		if (!marques[i])
			printf("%zu ", i+2);
	printf("\n");

	free (marques);
	return EXIT_SUCCESS;
}
