#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct{
	pthread_mutex_t m;
	int isWriting;
	int nbLect;

}lecteur_redacteur_t;

void initialiser_lecteur_redacteur(lecteur_redacteur_t *lr);

void debut_lecture(lecteur_redacteur_t *lr);

void fin_lecture(lecteur_redacteur_t *lr);

void debut_redaction(lecteur_redacteur_t *lr);

void fin_redaction(lecteur_redacteur_t *lr);

void detruire_lecteur_redacteur(lecteur_redacteur_t *lr);