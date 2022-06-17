/*
 * tempo.h
 *
 *  Created on: 16 de jun. de 2022
 *      Author: uotlaf
 */

#ifndef INCLUDE_TEMPO_H_
#define INCLUDE_TEMPO_H_
#include "sys/time.h"
#include <stdio.h>

// Controlador de tempo de cada parte do programa
typedef struct tempo
{
	long tinicial, tfinal;
	struct timeval tvinicial, tvfinal; // Timeval que vai ser convertido pra long
	char* identificador; // String que define qual seção do programa esse tempo está
	struct tempo* proximo; // Próximo cronômetro na lista
} tempo;

tempo* criarCronometro(char* identificador);
long timevalParaLong(struct timeval tv);
void pararCronometro(tempo* cronometro);
void addCronometroALista(tempo* lista, tempo* cronometro);

void relatorioCSV(char* localizacao, tempo* lista_de_cronometros);

#endif /* INCLUDE_TEMPO_H_ */
