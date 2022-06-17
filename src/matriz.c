/*
 * matriz.c
 *
 *  Created on: 12 de jun. de 2022
 *      Author: uotlaf
 */

// Headers globais
#include <stdlib.h> // random()
#include <math.h>

// Headers locais
#include "matriz.h"
#include "stdio.h"
#include "primos.h"

int ehPrimo(int numero) {
	/*
	 * Verifica se o número é primo pelo método convencional
	 */
	if (numero < 3) {
		return FALSE;
	}
	for (int i = 2; i <= (numero / 2); i++) {
		if (numero % i == 0) {
			return FALSE;
		}
	}
	return TRUE;
}

int ehPrimoSL(int numero) {
	/*
	 * Verifica se o número é primo pelo método da raiz quadrada
	 */
	if (numero < 3 || (numero % 2 == 0 && numero > 2)) {
		return FALSE;
	}

	for (int i = 3; i <= sqrt(numero)+1; i++) {
		if (numero % i == 0) {
			return FALSE;
		}
	}
	return TRUE;
}

void* separarPrimosBloco(void* arg_pkt) {
	/*
	 * Bloco que vai ser usado por cada uma das threads
	 */
	argumento* arg = (argumento*)arg_pkt; 	  // Desempacota a struct com os argumentos que foram passados
	ll_primos* listainterna = llPrimoCriar(); // Lista interna que vai ser juntada com a lista geral;

	// Cronômetros
	tempo* cronSepararPrimo; // Tempo que a thread levou para separar todos os primos
	tempo* cronMutex; // Tempo que levou para a thread ganhar acesso ao mutex/ele ser liberado para esta thread

	// Formatação do nome dos cronômetros
	char* nomeCronSepararPrimo = (char*)malloc(sizeof(char)*CRON_THREAD_STRING_LIMIT);
	char* nomeCronMutex = (char*)malloc(sizeof(char)*CRON_THREAD_STRING_LIMIT);

	if (arg->n_thread < 100) {
		if (0 > sprintf(nomeCronSepararPrimo, "Thread %d separar primos", arg->n_thread)) {
			pthread_exit(NULL);
		}
		if (0 > sprintf(nomeCronMutex, "Thread %d liberar mutex", arg->n_thread)) {
				pthread_exit(NULL);
			}
	} else {
		if (0 > sprintf(nomeCronSepararPrimo, "Thread .. separar primos")) {
					pthread_exit(NULL);
		}
		if (0 > sprintf(nomeCronMutex, "Thread .. liberar mutex")) {
				pthread_exit(NULL);
			}
	}


	cronSepararPrimo = criarCronometro(nomeCronSepararPrimo);
	for (int i = arg->inicio; i <= arg->fim;i++) {
		if (ehPrimoSL(matriz[i])) {
			// Cria um primo e bota na lista interna
			primo* temp = malloc(sizeof(primo));
			temp->x = (long)i/(long)ORDEM_MATRIZ;
			temp->y = (long)i%(long)ORDEM_MATRIZ;
			temp->proximo = NULL;
#ifdef THREADDEBUG
			printf("[THREAD %d]Adicionando %d no controle\n", arg->n_thread, matriz[i]);
#endif
			addPrimoEmLista(listainterna, temp);
		}
	}
	pararCronometro(cronSepararPrimo);

#ifdef THREADDEBUG
	printf("[THREAD %d]Thread terminada - Juntando as listas\n", arg->n_thread);
#endif


	cronMutex = criarCronometro(nomeCronMutex);
	pthread_mutex_lock(&mutex);
	pararCronometro(cronMutex);

	juntarListas(lista_primos, listainterna);
	addCronometroALista(lista_tempos, cronSepararPrimo);
	addCronometroALista(lista_tempos, cronMutex);
	pthread_mutex_unlock(&mutex);

#ifdef THREADDEBUG
	printf("A thread %d acabou\n", arg->n_thread);
#endif
	pthread_exit(NULL);
}


void gerarMatrizSequencial() {
	/*
	 * Gera uma matriz sequencial com números entre 0 e RANDOM_MAX
	 */
	int atual = 0;
	for (int i = 0; i < ORDEM_MATRIZ; i++) {
		for (int j = 0; j < ORDEM_MATRIZ; j++) {
			if (atual > RANDOM_MAX_CAP) {
				atual = 0;
			}
			matriz[i * ORDEM_MATRIZ + j] = atual;
			atual++;
		}
	}
}

void gerarMatrizAleatoria() {
	/*
	 * Gera uma matriz com números aleatórios entre 0 e RANDOM_MAX
	 */
	srandom(SEED); // Bota a SEED no gerador
	for (int i = 0; i < ORDEM_MATRIZ; i++) {
		for (int j = 0; j < ORDEM_MATRIZ; j++) {
			matriz[i * ORDEM_MATRIZ + j] = (int)random() % RANDOM_MAX_CAP;
		}
	}
}

void separarPrimos() {
	/*
	 * Separa a matriz em blocos e manda cada bloco pra uma thread
	 */


	// Cria os argumentos e as threads
	for (int i = 0; i < THREADS; i++) {
		argumento* arg = (argumento*)malloc(sizeof(argumento));
		arg->inicio = i*TAMANHO_BLOCO;
		arg->fim = ((i+1)*TAMANHO_BLOCO)-1;
		arg->n_thread = i;
#ifdef DEBUG
		printf("Iniciando thread %d entre %d e %d\n", i, arg->inicio, arg->fim);
#endif
		pthread_create(&(thread[i]), NULL, separarPrimosBloco, (void*)arg);
	}


	for (int i = 0; i < THREADS; i++) {
		pthread_join(thread[i], NULL);
#ifdef DEBUG
		printf("Thread %d terminada\n", i);
#endif
	}

	if (RESTO > 0) {
#ifdef DEBUG
		printf("O resto é maior que 0[%d]: Criando uma thread pra completar\n", RESTO);
#endif
		// Obtendo o novo tamanho do bloco - O que restou da iteração anterior
		argumento *arg = (argumento*) malloc(sizeof(argumento));
		arg->inicio = (long)THREADS*(long)TAMANHO_BLOCO;
		arg->fim = (long)THREADS*(long)TAMANHO_BLOCO+(RESTO-1);
		arg->n_thread = 0;
#ifdef DEBUG
		printf("Iniciando thread entre %d e %d\n", arg->inicio, arg->fim);
#endif
		pthread_create(&thread[0], NULL, separarPrimosBloco, (void*)arg);
		pthread_join(thread[0], NULL);
	}
}
