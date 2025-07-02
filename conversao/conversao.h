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
 * Conversão de Árvore 2-3-4 para Árvore Rubro-Negra
 * Arquivo: conversao.h
 * Declara as funções para converter nós e estruturar uma nova árvore RB
 ******************************************************************************/



#ifndef CONVERSAO_H
#define CONVERSAO_H

#include "../arv234/arv234.h"
#include "../arvrb/arvRB.h"


// Função para iniciar a conversão, alocando arvores e nós necessários
arvRb *converte234ParaRB(arv234 *arv234);

// Função que realiza a conversão de um nó da 234 para o equivalente na rubroNegra
noRB *converteNo(arvRb *arvoreRB, no *no234);


#endif //CONVERSAO_H
