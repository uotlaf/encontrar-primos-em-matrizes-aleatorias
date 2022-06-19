/*
 * matriz.c
 *
 *  Created on: 12 de jun. de 2022
 *      Author: uotlaf
 */


// Headers locais
#include "matriz.h"

void gerarMatrizSequencial() {
	/*
	 * Gera uma matriz sequencial com números entre 0 e RANDOM_MAX
	 */
	debug("Gerando matriz sequencial\n");
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
	debug("Matriz sequencial gerada com sucesso\n");
}

void gerarMatrizAleatoria() {
	/*
	 * Gera uma matriz com números aleatórios entre 0 e RANDOM_MAX
	 */
	debug("Gerando matriz aleatória\n");
	srandom(SEED); // Bota a SEED no gerador
	for (int i = 0; i < ORDEM_MATRIZ; i++) {
		for (int j = 0; j < ORDEM_MATRIZ; j++) {
			matriz[i * ORDEM_MATRIZ + j] = (int)random() % RANDOM_MAX_CAP;
		}
	}
	debug("Matriz aleatória gerada com sucesso\n");
}

