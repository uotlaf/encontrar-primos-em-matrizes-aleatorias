/*
 * matriz.h
 *
 *  Created on: 12 de jun. de 2022
 *      Author: uotlaf
 */

#ifndef INCLUDE_MATRIZ_H_
#define INCLUDE_MATRIZ_H_

#include <pthread.h>
#include <stdlib.h> // random()
#include "primos.h"
#include "tempo.h"

#define TAMANHO_MATRIZ (ORDEM_MATRIZ*ORDEM_MATRIZ)
#define TAMANHO_BLOCO (TAMANHO_MATRIZ)/THREADS
#define RESTO (TAMANHO_MATRIZ)%THREADS


// Variáveis pegas da main
extern int matriz[];


void gerarMatrizSequencial();
void gerarMatrizAleatoria();

#endif /* INCLUDE_MATRIZ_H_ */
