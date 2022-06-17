/*
 * estruturas.c
 *
 *  Created on: 12 de jun. de 2022
 *      Author: uotlaf
 */


#include <stdlib.h>
#include "primos.h"


ll_primos* llPrimoCriar() {
    ll_primos *resultado = malloc(sizeof(ll_primos));
    if (resultado == NULL) {
        return NULL;
    }

    resultado->quantidade = 0;
    return resultado;
}

primo* proximoPrimo(primo* act_primo) {
    if (act_primo == NULL) {
        return NULL;
    }
    if (act_primo->proximo != NULL) {
        return act_primo->proximo;
    }
    return NULL;
}

/*
    Adiciona obj_primo dentro de controle. Retorna o índice de obj_primo dentro da lista
    Ou retorna -1 no caso de erro
*/
int addPrimoEmLista(ll_primos* lista, primo* obj_primo) {
    if (lista == NULL || obj_primo == NULL) {
        return -1;
    }

    // Adiciona o primo na primeira posição se não tem nenhum primo no controle
    if (lista->quantidade == 0) { // controle->primo == NULL
        lista->pinicial = obj_primo;
        lista->pfinal = obj_primo;
        lista->quantidade ++;
        return 0;
    }

    // Se o controle não estiver vazio
    primo* primo_atual = lista->pfinal;

    primo_atual->proximo = obj_primo;
    lista->quantidade++;
    lista->pfinal = obj_primo;
    return lista->quantidade;
}


int juntarListas(ll_primos* lista_geral, ll_primos* lista_add) {
	if (lista_geral == NULL || lista_add == NULL || lista_add->quantidade == 0) {
		return -1;
	}

	// Funde as duas listas se o controle geral da primeira estiver vazio
	if (lista_geral->quantidade == 0) {
		lista_geral->pfinal     = lista_add->pfinal;
		lista_geral->pinicial   = lista_add->pinicial;
		lista_geral->quantidade = lista_add->quantidade;
		free(lista_add);
		return 0;
	}

	// Adiciona o início da primeira lista no final da segunda
	lista_geral->pfinal->proximo = lista_add->pinicial;
	lista_geral->pfinal = lista_add->pfinal;
	lista_geral->quantidade += lista_add->quantidade;

	free(lista_add);
	return 0;
}
