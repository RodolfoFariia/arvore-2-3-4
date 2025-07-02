/******************************************************************************
*                                                                            *
 *         ÁRVORES 2-3-4 E SUA EQUIVALÊNCIA COM ÁRVORES RUBRO-NEGRAS          *
 *                                                                            *
 *       Algoritmos e Estrutura de Dados II – Ciência da Computação – UNIFEI  *
 *       Professora: Vanessa Cristina Oliveira de Souza                       *
 *                                                                            *
 *       Trabalho desenvolvido por:                                           *
 *           Rodolfo Henrique Faria              – 2024008886                 *
 *           Rafael Santos Pinto Batista Leite   – 2024004564                 *
 *                                                                            *
 ******************************************************************************/
/******************************************************************************
 * Experimentos realizados sobre a Árvore 2-3-4
 * Arquivo: experimentos.h
 * Declara as funções para realizar os testees de inserção e remoção
 ******************************************************************************/


#ifndef EXPERIMENTOS_H
#define EXPERIMENTOS_H

#include "../Arvore 2-3-4/arv234.h"
#include <stdio.h>

// --------------- PREENCHER VETOR ALEATÓRIO ---------------------
void preencheVetorAleatorioInsercao(int *vetor, int tam);
int preencheVetorAleatorioRemocao(int *vetorOriginal, int *vetorRemocao, int tamOriginal, int percentual);

// ----------------- TESTES DE INSERÇÃO -----------------------
arv234 *realizaTestesInsercao(FILE *arq, char *instancia, int tam, int id);
void inicializaTesteInsercao();

// ----------------- TESTES DE REMOÇÃO -----------------------
void realizaTesteRemocao(FILE *arq, char *instancia, int *vetorOriginal, int tamOriginal, int percentual, arv234 *arvore);
void inicializaTesteRemocao();

// ----------------- TESTE FINAL ----------------------------
void realizaTeste();

#endif //EXPERIMENTOS_H