#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "lecteur_redacteur.h"
#include <assert.h>

void initialiser_lecteur_redacteur(lecteur_redacteur_t *lr){
	pthread_mutex_init(&lr->m, NULL);
	lr->isWriting = 0;
	lr->nbLectAttente = 0;
	lr->nbLectBase = 0;
	pthread_cond_init(&lr->clect, NULL);
	pthread_cond_init(&lr->ccrire, NULL);
}

void debut_lecture(lecteur_redacteur_t *lr){
	pthread_mutex_lock(&lr->m);
	lr->nbLectAttente++;
	while(lr->isWriting){
		pthread_cond_wait(&lr->clect, &lr->m);
	}
	lr->nbLectAttente--;
	lr->nbLectBase++;
	pthread_mutex_unlock(&lr->m);
}

void fin_lecture(lecteur_redacteur_t *lr){
	pthread_mutex_lock(&lr->m);
	lr->nbLectBase--;
	assert(lr->nbLectBase >= 0);
	if(lr->nbLectBase == 0){
		pthread_cond_signal(&lr->ccrire);
	}
	pthread_mutex_unlock(&lr->m);
}

void debut_redaction(lecteur_redacteur_t *lr){
	pthread_mutex_lock(&lr->m);
	while(lr->nbLectAttente || lr->isWriting || lr->nbLectBase){
		pthread_cond_wait(&lr->ccrire, &lr->m);
	}
	lr->isWriting = 1;
	pthread_mutex_unlock(&lr->m);
}

void fin_redaction(lecteur_redacteur_t *lr){
	pthread_mutex_lock(&lr->m);
	lr->isWriting = 0;
	if(lr->nbLectAttente){
		pthread_cond_broadcast(&lr->clect);
	}
	else{
		pthread_cond_signal(&lr->ccrire);
	}
	
	
	pthread_mutex_unlock(&lr->m);
}

void detruire_lecteur_redacteur(lecteur_redacteur_t *lr){
	pthread_mutex_destroy(&lr->m);
	pthread_cond_destroy(&lr->ccrire);
	pthread_cond_destroy(&lr->clect);
}