/*
 * thread.h
 *
 *  Created on: 18 de jun. de 2022
 *      Author: uotlaf
 */

#ifndef INCLUDE_HANDLERS_THREAD_H_
#define INCLUDE_HANDLERS_THREAD_H_

#include <stdlib.h>
#include <pthread.h>
#include "primos.h"
#include "tempo.h"
#include "matriz.h"

typedef struct argumento
{
	long inicio;
	long fim;
	int n_thread;
} argumento;

extern int matriz[];
extern ll_primos* lista_primos;
extern pthread_mutex_t mutex;
extern pthread_t threadlist[THREADS];

void threadHandler();
void* thread(void* arg_pkt);


#endif /* INCLUDE_HANDLERS_THREAD_H_ */
