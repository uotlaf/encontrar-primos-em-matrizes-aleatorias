/*
 * tempo.h
 *
 *  Created on: 16 de jun. de 2022
 *      Author: uotlaf
 */

#ifndef INCLUDE_TEMPO_H_
#define INCLUDE_TEMPO_H_
#include "sys/time.h"
#include "handlers/debug.h"
#include <stdlib.h>

// Conversões
#define timevalParaLong(timev) (timev.tv_sec*1000000 + timev.tv_usec)
#define cronParaLong(cron)     (timevalParaLong(cron->tvfinal) - timevalParaLong(cron->tvinicial))
#define cronParaSec(cron)      (cronParaLong(cron)/1000000)
#define cronParaMSec(cron)     (cronParaLong(cron)%1000000/1000)
#define cronParaUSec(cron)     (cronParaLong(cron)%(cronParaLong(cron)/1000))

// Controlador de tempo de cada parte do programa
typedef struct cronometro
{
	struct timeval tvinicial, tvfinal; // Timeval que vai ser convertido pra long
} cronometro;

cronometro* criarCronometro();
void pararCronometro(cronometro* cron);

#endif /* INCLUDE_TEMPO_H_ */
