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

// ORDEM_MATRIZ é definido no Makefile
#define TAMANHO_MATRIZ (ORDEM_MATRIZ*ORDEM_MATRIZ) // @suppress("Symbol is not resolved")
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_t thread[THREADS]; // @suppress("Symbol is not resolved")

// Vars globais
int matriz[TAMANHO_MATRIZ];
ll_primos* lista_primos; // Lista de primos do programa
tempo* lista_tempos; 	  // Lista de cronometros e cronômetro principal do programa;

// Cronômetros principais
tempo* cronGerarMatriz;   // Tempo que demora para uma matriz ser criada
tempo* cronSepararPrimos; // Tempo que demora para separar todos os primos de uma matriz

int main() {
	// Pré-checks
	if (THREADS > (TAMANHO_MATRIZ)) { // @suppress("Symbol is not resolved")
		printf("ERRO: %d threads é maior que o número de elementos na matriz(%d)\n", THREADS, TAMANHO_MATRIZ);
		return 1;
	}

	if (THREADS%(TAMANHO_MATRIZ) != 0) { // @suppress("Symbol is not resolved")
		printf("AVISO: Número de threads(%d) incompatível com tamanho da matriz(%d)\n", THREADS, TAMANHO_MATRIZ);
	}

	// Inicia o cronômetro do programa inteiro
	lista_tempos = criarCronometro("Main");


	// Geração da matriz
	cronGerarMatriz = criarCronometro("Gerar matriz");

	#if CONF_USAR_MATRIZ_ALEATORIA == 0
	gerarMatrizSequencial();
#else
	gerarMatrizAleatoria();
#endif

	pararCronometro(cronGerarMatriz);
	addCronometroALista(lista_tempos, cronGerarMatriz);

	printf("Primeiro número: %d\n", matriz[0]);



	// Interface de controle dos primos
	lista_primos = llPrimoCriar();
	if (lista_primos == NULL) {
		printf("Controle não foi alocado com sucesso");
		return 1;
	}

	// Programa principal
	cronSepararPrimos = criarCronometro("Separar Primos");

	separarPrimos();

	pararCronometro(cronSepararPrimos);
	addCronometroALista(lista_tempos, cronSepararPrimos);

	printf("Foram encontrados %d primos\n", lista_primos->quantidade);


	// Termina o cronômetro do programa inteiro
	pararCronometro(lista_tempos);

	printf("Criando relarório\n");
	relatorioCSV("./relatorio.csv", lista_tempos);
	printf("Relatório criado com sucesso\n");
	return 0;
}
