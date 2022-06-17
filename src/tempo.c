/*
 * tempo.c
 *
 *  Created on: 16 de jun. de 2022
 *      Author: uotlaf
 */


#include "tempo.h"
#include <stdlib.h>

tempo* criarCronometro(char* identificador) {
	if (identificador == NULL) {
		return NULL;
	}

	tempo* cronometro = (tempo*)malloc(sizeof(tempo));
	if (cronometro == NULL) {
		return NULL;
	}

	cronometro->identificador = identificador;
	cronometro->proximo = NULL;

	gettimeofday(&cronometro->tvinicial, NULL); // Inicia o cronômetro
	return cronometro;
}

void pararCronometro(tempo* cronometro) {
	if (cronometro == NULL) {
		return;
	}
	gettimeofday(&cronometro->tvfinal, NULL);
}

long timevalParaLong(struct timeval timev) {
	return timev.tv_sec*1000000 + timev.tv_usec;
}

void addCronometroALista(tempo* lista, tempo* cronometro) {
	if (lista == NULL || cronometro == NULL) {
		return;
	}

	// Configura a cabeça da lista se não foi configurada ainda
	if (lista->tinicial == 0) {
		lista->tinicial = timevalParaLong(lista->tvinicial);
	}

	cronometro->tinicial = timevalParaLong(cronometro->tvinicial);
	cronometro->tfinal = timevalParaLong(cronometro->tvfinal);

	// Configura o tempo do cronômetro atual a partir do primeiro
	cronometro->tinicial = cronometro->tinicial - lista->tinicial;
	cronometro->tfinal = cronometro->tfinal - lista->tinicial;


	// Se a lista só tem 1 cronometro
	if (lista->proximo == NULL) {
		lista->proximo = cronometro;
		// Converte os timevals pra long
		return;
	}

	// Se a lista tem + de 1 cronometro
	tempo* proximo_tempo = lista->proximo;
	// Procura o último cronometro
	while (proximo_tempo->proximo != NULL) {
		proximo_tempo = proximo_tempo->proximo;
	}

	// Adiciona o cronometro no fim da lista
	proximo_tempo->proximo = cronometro;
}


void relatorioCSV(char* localizacao, tempo* lista_de_cronometros) {
	if (localizacao == NULL || lista_de_cronometros == NULL) {
		return;
	}

	FILE *pont_csv;
	pont_csv = fopen(localizacao, "w");

	// Configura a cabeça da lista
	if (lista_de_cronometros->tfinal == 0) {
		lista_de_cronometros->tfinal = timevalParaLong(lista_de_cronometros->tvfinal);
		lista_de_cronometros->tfinal = lista_de_cronometros->tfinal - lista_de_cronometros->tinicial;
		lista_de_cronometros->tinicial = 0;
	}

	if (pont_csv == NULL) {
		return;
	}

	fprintf(pont_csv, "CONFIG: %d threads, Ordem da matriz: %d\n", THREADS, ORDEM_MATRIZ);
	fprintf(pont_csv, "IDENTIFICADOR, TEMPOINICIAL, DURAÇÃO, TEMPOFINAL\n");

	tempo* cronAtual = lista_de_cronometros;

	while (cronAtual != NULL) {
		fprintf(pont_csv, "%s,%ld,%ld, %ld\n", cronAtual->identificador, cronAtual->tinicial, cronAtual->tfinal - cronAtual->tinicial, cronAtual->tfinal);
		cronAtual = cronAtual->proximo;
	}

	fclose(pont_csv);

}
