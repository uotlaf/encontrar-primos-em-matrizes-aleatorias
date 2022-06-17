/*
 * matriz.h
 *
 *  Created on: 12 de jun. de 2022
 *      Author: uotlaf
 */

#ifndef INCLUDE_MATRIZ_H_
#define INCLUDE_MATRIZ_H_

#include <pthread.h>

#include "primos.h"
#include "tempo.h"



#define TAMANHO_MATRIZ (ORDEM_MATRIZ*ORDEM_MATRIZ)
#define TAMANHO_BLOCO (TAMANHO_MATRIZ)/THREADS
#define CRON_THREAD_STRING_LIMIT 30

#if THREADS > 1
#define RESTO (TAMANHO_MATRIZ)%THREADS
#else
#define RESTO 0
#endif

// Variáveis pegas da main
extern int matriz[];
extern ll_primos* lista_primos;
extern tempo* lista_tempos;

extern pthread_mutex_t mutex;
extern pthread_t thread[THREADS];


typedef struct argumento
{
	long inicio;
	long fim;
	int n_thread;
} argumento;

int ehPrimo(int numero);
void gerarMatrizSequencial();
void gerarMatrizAleatoria();

void separarPrimos();
#endif /* INCLUDE_MATRIZ_H_ */
