/*
 * main.c
 *
 *  Created on: 12 de jun. de 2022
 *      Author: uotlaf
 */
// Includes gerais
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Includes locais
#include "primos.h"
#include "matriz.h"
#include "tempo.h"
#include "visualizacao.h"
#include "handlers/thread.h"
#include "handlers/debug.h"

// ORDEM_MATRIZ é definido no Makefile

// Definir função de gerar matriz
#if CONF_USAR_MATRIZ_ALEATORIA
#define gerarMatriz() gerarMatrizAleatoria();
#else
#define gerarMatriz() gerarMatrizSequencial();
#endif

// Vars globais
int matriz[TAMANHO_MATRIZ];
ll_primos* lista_primos; // Lista de primos do programa

// Threads
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_t threadlist[THREADS];

int main() {
	// Pré-checks
	if (THREADS > (TAMANHO_MATRIZ)) {
		printf("ERRO: %d threads é maior que o número de elementos na matriz(%d)\n", THREADS, TAMANHO_MATRIZ);
		return 1;
	}

	if ((TAMANHO_MATRIZ)%THREADS != 0) { // @suppress("Symbol is not resolved")
		printf("AVISO: Número de threads(%d) incompatível com tamanho da matriz(%d)\n", THREADS, TAMANHO_MATRIZ);
	}

	printf("Iniciando com %d threads e ordem %d[%d objetos]\n", THREADS, ORDEM_MATRIZ, TAMANHO_MATRIZ);

	// Bota os números na matriz
	gerarMatriz();
	printf("Primeiro número: %d\n", matriz[0]);

	// Interface de controle dos primos
	lista_primos = llPrimoCriar();
	if (lista_primos == NULL) {
		error("Controle não foi alocado com sucesso\n");
		return 1;
	}

	cronometro* cronSepararPrimos = criarCronometro();
	threadHandler();
	pararCronometro(cronSepararPrimos);

	printf("Foram encontrados %d primos\n", lista_primos->quantidade);

	//printf("Demorou %ld msec\n", );
	printf("Demorou %lds:%ldms:%ldus\n",
			cronParaSec(cronSepararPrimos),
			cronParaMSec(cronSepararPrimos),
			cronParaUSec(cronSepararPrimos));

#if THREADS == 1 && IMPRIMIR_MATRIZ == 1
	visualizarMatrizEmCoordenada();
	visualizarMatrizEmValores();
	visualizarMatrizSoPrimos(lista_primos);
#endif
	return 0;
}
