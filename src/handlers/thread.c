/*
 * threadHandler.c
 *
 *  Created on: 18 de jun. de 2022
 *      Author: uotlaf
 */

#include "handlers/thread.h"

void* thread(void* arg_pkt) {
	/*
	 * Bloco que vai ser usado por cada uma das threads
	 */
	argumento* arg = (argumento*)arg_pkt; 	  // Desempacota a struct com os argumentos que foram passados
	ll_primos* listainterna = llPrimoCriar(); // Lista interna que vai ser juntada com a lista geral;

	debugThread("Iniciada\n");

	for (int i = arg->inicio; i <= arg->fim;i++) {
		if (ehPrimoSL(matriz[i])) {
			// Cria um primo e bota na lista interna
			primo* temp = malloc(sizeof(primo));
			temp->x = (long)i/(long)ORDEM_MATRIZ;
			temp->y = (long)i%(long)ORDEM_MATRIZ;
			temp->proximo = NULL;
			addPrimoEmLista(listainterna, temp);
		}
	}

#ifdef THREADDEBUG
	printf("[THREAD %d]Thread terminada - Juntando as listas\n", arg->n_thread);
#endif

	debugThread("Esperando por liberação do mutex\n");
	pthread_mutex_lock(&mutex);
	debugThread("Mutex liberado\n");
	juntarListas(lista_primos, listainterna);
	pthread_mutex_unlock(&mutex);

	debugThread("Terminada\n");
	pthread_exit(NULL);
}

void threadHandler() {
	/*
	 * Separa a matriz em blocos e manda cada bloco pra uma thread
	 */

	// Cria os argumentos e as threads
	for (int i = 0; i < THREADS; i++) {
		argumento* arg = (argumento*)malloc(sizeof(argumento));
		arg->inicio = i*TAMANHO_BLOCO;
		arg->fim = ((i+1)*TAMANHO_BLOCO)-1;
		arg->n_thread = i;
		debugThread("Iniciando\n");
		pthread_create(&(threadlist[i]), NULL, thread, (void*)arg);
	}


	for (int i = 0; i < THREADS; i++) {
		pthread_join(threadlist[i], NULL);
	}

	if (RESTO > 0) {
		debug("O resto é maior que 0; Criando uma thread para o resto\n");
		// Obtendo o novo tamanho do bloco - O que restou da iteração anterior
		argumento *arg = (argumento*) malloc(sizeof(argumento));
		arg->inicio = (long)THREADS*(long)TAMANHO_BLOCO;
		arg->fim = (long)THREADS*(long)TAMANHO_BLOCO+(RESTO-1);
		arg->n_thread = 0;
		pthread_create(&threadlist[0], NULL, thread, (void*)arg);
		pthread_join(threadlist[0], NULL);
	}

	debug("Terminado\n");
}
