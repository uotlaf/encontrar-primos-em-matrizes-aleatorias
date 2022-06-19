/*
 * tempo.c
 *
 *  Created on: 16 de jun. de 2022
 *      Author: uotlaf
 */


#include "tempo.h"

cronometro* criarCronometro() {
	cronometro* cron = (cronometro*)malloc(sizeof(cronometro));
	if (cron == NULL) {
		return NULL;
	}
	debug("Iniciando cronômetro\n");
	gettimeofday(&cron->tvinicial, NULL); // Inicia o cronômetro
	return cron;
}

void pararCronometro(cronometro* cron) {
	if (cron == NULL) {
		return;
	}
	gettimeofday(&cron->tvfinal, NULL);
	debug("Cronômetro terminado\n");
}
