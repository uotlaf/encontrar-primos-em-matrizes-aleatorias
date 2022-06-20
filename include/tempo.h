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

// Controlador de tempo de cada parte do programa
typedef struct cronometro
{
	struct timeval tvinicial, tvfinal; // Timeval que vai ser convertido pra long
} cronometro;


// Conversões
#define timevalParaLong(timev) (timev.tv_sec*1000000 + timev.tv_usec)
#define cronParaLong(cron)     (timevalParaLong(cron->tvfinal) - timevalParaLong(cron->tvinicial))
long cronParaSec(cronometro* cron);
long cronParaMSec(cronometro* cron);
long cronParaUSec(cronometro* cron);



cronometro* criarCronometro();
void pararCronometro(cronometro* cron);

#endif /* INCLUDE_TEMPO_H_ */
