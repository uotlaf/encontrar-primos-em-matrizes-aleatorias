/*
 * visualizacao.c
 *
 *  Created on: 12 de jun. de 2022
 *      Author: uotlaf
 */


#include "visualizacao.h"
#include <stdio.h>

// PROIBIDO MOSTRAR PARA ANSELMO

void visualizarMatrizEmCoordenada() {
    printf(" - Matriz final: -\n");
    for (int i = 0; i < ORDEM_MATRIZ; i++) {
        for (int j = 0; j < ORDEM_MATRIZ; j++) {
            printf("[%d, %d] ", i, j);
        }
        printf("\n");
    }
}

void visualizarMatrizEmValores() {
    printf(" - Matriz final: -\n");
    for (int i = 0; i < ORDEM_MATRIZ; i++) {
        for (int j = 0; j < ORDEM_MATRIZ; j++) {
            if (matriz[i*ORDEM_MATRIZ+j] < 10) {
                printf("[ %d] ", matriz[i*ORDEM_MATRIZ+j]);
            } else {
                printf("[%d] ", matriz[i*ORDEM_MATRIZ+j]);
            }
        }
        printf("\n");
    }
}

void visualizarMatrizSoPrimos(controle_primos* controle) {
    if (controle == NULL) {
        printf("Controle não existe");
        return;
    }

    printf(" - Primos encontrados: \n");
    primo* primoAtual = controle->primoinicial;
    if (primoAtual == NULL) {
        printf("Nenhum primo encontrado");
    }

    for (int i = 0; i < ORDEM_MATRIZ; i++) {
        for (int j = 0; j < ORDEM_MATRIZ; j++) {
            if (primoAtual != NULL) {
                if (primoAtual->x == i && primoAtual->y == j) {
                    if (matriz[i * ORDEM_MATRIZ + j] < 10) {
                        printf("[ %d] ", matriz[i*ORDEM_MATRIZ + j]);
                    } else {
                        printf("[%d] ", matriz[i*ORDEM_MATRIZ + j]);
                    }
                } else {
                    printf("[  ] ");
                }
                if (primoAtual->x == i && primoAtual->y == j) {
                    primoAtual = proximoPrimo(primoAtual);
                }
            } else {
            	printf("[  ] ");
            }

        }
        printf("\n");
    }
}
