/*
 * estruturas.h
 *
 *  Created on: 12 de jun. de 2022
 *      Author: uotlaf
 */

#ifndef INCLUDE_PRIMOS_H_
#define INCLUDE_PRIMOS_H_
#include <math.h>
#include <stdlib.h>
#include "handlers/debug.h"

// Struct que vai contar a quantidade de números primos que foram encontrados

/*
    Os primos são implementados em uma lista + struct de controle
    ll_primos -> primo1 -> primo2 -> primo3 -> primo4
*/

typedef struct primo
{
    long x, y;
    struct primo *proximo;
} primo;

typedef struct ll_primos
{
    int quantidade;
    primo *pinicial, *pfinal; // Ponteiro para facilitar juntar 2 listas
} ll_primos;	 // Lista ligada com todos os primos

primo* primoCriar(int x, int y);
ll_primos* llPrimoCriar();
primo* proximoPrimo(primo* act_primo);

int addPrimoEmLista(ll_primos* lista, primo* obj_primo);

int juntarListas(ll_primos* lista_geral, ll_primos* lista_add);

int ehPrimoSL(int numero);

#endif /* INCLUDE_PRIMOS_H_ */
