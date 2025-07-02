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
 * Arquivo: conversao.c
 * Implementa as funções para converter nós e estruturar a nova árvore RB
 ******************************************************************************/

#include "conversao.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * converte234ParaRB:
 *   - Recebe uma árvore 2-3-4 e retorna uma árvore Rubro-Negra equivalente.
 *   - Se a árvore origem for NULL, retorna NULL.
 *   - Aloca uma nova árvore RB e converte recursivamente cada nó.
 */
arvRb *converte234ParaRB(arv234 *arv234Orig) {
    if (arv234Orig == NULL)
        return NULL;

    // Criar árvore RB vazia
    arvRb *novaArv = rb_alocaArvore();
    if (novaArv == NULL)
        return NULL;

    // Obter a raiz da árvore 2-3-4 e converter o subárvore
    no *raiz234 = getRaiz(arv234Orig);
    noRB *raizRB = converteNo(novaArv, raiz234);

    // Definir o nó convertido como raiz da nova árvore RB
    rb_setRaiz(novaArv, raizRB);
    return novaArv;
}

/**
 * converteNo:
 *   - Converte um nó de uma árvore 2-3-4 (no234) para um ou mais nós em RB.
 *   - Base: se no234 for NULL, retorna a sentinela de folhas da RB.
 *   - Dependendo de qtd_chaves (1, 2 ou 3), cria a estrutura de nós RB:
 *       * 1 chave => nó preto com duas subárvores filhas
 *       * 2 chaves => nó pai preto e filho esquerdo vermelho
 *       * 3 chaves => nó pai preto com filhos esquerdo e direito vermelhos
 */
noRB *converteNo(arvRb *arvoreRB, no *no234) {
    if (no234 == NULL) {
        // Sempre retorna a sentinela para ponteiros nulos
        return arvoreRB->sentinelaFolha;
    }

    noRB *novoNo = NULL;
    int numChaves = no234->qtd_chaves;

    // Caso: nó com 1 chave
    if (numChaves == 1) {
        // Criar nó preto com a única chave
        novoNo = rb_alocaNo(arvoreRB, no234->chaves[0]);
        rb_setCor(novoNo, 'P');

        // Converter recursivamente filhos esquerda e direita
        novoNo->esq = converteNo(arvoreRB, no234->filhos[0]);
        novoNo->dir = converteNo(arvoreRB, no234->filhos[1]);

        // Ajustar ponteiros de pai se não for sentinela
        if (novoNo->esq != arvoreRB->sentinelaFolha)
            novoNo->esq->pai = novoNo;
        if (novoNo->dir != arvoreRB->sentinelaFolha)
            novoNo->dir->pai = novoNo;

    // Caso: nó com 2 chaves
    } else if (numChaves == 2) {
        // Criar nó pai com chave central como preto
        noRB *noPai = rb_alocaNo(arvoreRB, no234->chaves[1]);
        rb_setCor(noPai, 'P');

        // Criar filho esquerdo vermelho com primeira chave
        noRB *noEsq = rb_alocaNo(arvoreRB, no234->chaves[0]);
        rb_setCor(noEsq, 'V');

        // Ligar estruturas: pai e filhos
        noPai->esq = noEsq;
        noEsq->pai = noPai;

        // Converter e ligar subárvore direita do pai
        noPai->dir = converteNo(arvoreRB, no234->filhos[2]);
        if (noPai->dir != arvoreRB->sentinelaFolha)
            noPai->dir->pai = noPai;

        // Converter subárvores do nó esquerdo
        noEsq->esq = converteNo(arvoreRB, no234->filhos[0]);
        noEsq->dir = converteNo(arvoreRB, no234->filhos[1]);
        if (noEsq->esq != arvoreRB->sentinelaFolha)
            noEsq->esq->pai = noEsq;
        if (noEsq->dir != arvoreRB->sentinelaFolha)
            noEsq->dir->pai = noEsq;

        novoNo = noPai;

    // Caso: nó com 3 chaves
    } else if (numChaves == 3) {
        // Criar nó pai preto com a chave do meio
        noRB *noPai = rb_alocaNo(arvoreRB, no234->chaves[1]);
        rb_setCor(noPai, 'P');

        // Criar filhos esquerdo e direito vermelhos
        noRB *noEsq = rb_alocaNo(arvoreRB, no234->chaves[0]);
        noRB *noDir = rb_alocaNo(arvoreRB, no234->chaves[2]);
        rb_setCor(noEsq, 'V');
        rb_setCor(noDir, 'V');

        // Ligar pai e filhos
        noPai->esq = noEsq;
        noPai->dir = noDir;
        noEsq->pai = noPai;
        noDir->pai = noPai;

        // Converter subárvores do filho esquerdo
        noEsq->esq = converteNo(arvoreRB, no234->filhos[0]);
        noEsq->dir = converteNo(arvoreRB, no234->filhos[1]);
        if (noEsq->esq != arvoreRB->sentinelaFolha)
            noEsq->esq->pai = noEsq;
        if (noEsq->dir != arvoreRB->sentinelaFolha)
            noEsq->dir->pai = noEsq;

        // Converter subárvores do filho direito
        noDir->esq = converteNo(arvoreRB, no234->filhos[2]);
        noDir->dir = converteNo(arvoreRB, no234->filhos[3]);
        if (noDir->esq != arvoreRB->sentinelaFolha)
            noDir->esq->pai = noDir;
        if (noDir->dir != arvoreRB->sentinelaFolha)
            noDir->dir->pai = noDir;

        novoNo = noPai;
    }

    return novoNo;
}
