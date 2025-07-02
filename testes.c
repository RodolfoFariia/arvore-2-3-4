//
// Created by rodolfo on 01/07/25.
//
#include <stdio.h>
#include <stdlib.h>
#include "arvrb/arvRB.h"
#include "arv234/arv234.h"
#include "conversao/conversao.h"

/* ------------------- TESTE DE CONVERSÃO 234 -> RB --------------------
int main() {
    // Cria e popula árvore 2-3-4
    arv234 *arv234 = alocaArvore();
    int valores[] = {30, 10, 20, 40, 50, 60, 70, 80, 90, 100, 15, 25, 35};
    int n = sizeof(valores) / sizeof(valores[0]);

    for (int i = 0; i < n; i++) {
        inserir(arv234, valores[i]);
    }

    // Mostra árvore 2-3-4
    printf("Arvore 2-3-4:\n");
    percorrePreOrdem(getRaiz(arv234), 0);
    printf("\n\n");

    // Converte para árvore rubro-negra
    arvRb *arvRB = converte234ParaRB(arv234);

    // Mostra árvore rubro-negra
    printf("Arvore rubro-negra convertida:\n");
    rb_percorrePreOrdem(arvRB, rb_getRaiz(arvRB));
    printf("\n");

    // Verifica propriedades da rubro-negra
    printf("\nVerificacoes finais:\n");
    noRB *raiz = rb_getRaiz(arvRB);
    printf("Raiz: %d (deve ser preta)\n", raiz->chave);

    if (raiz->esq != NULL) {
        printf("Filho esquerdo da raiz: %d\n", raiz->esq->chave);
    }

    if (raiz->dir != NULL) {
        printf("Filho direito da raiz: %d\n", raiz->dir->chave);
    }

    // Adicione mais verificações conforme necessário
    // Liberar memória (implementar essas funções)
    // liberaArvore234(arv234);
    // rb_liberaArvore(arvRB);

    return 0;
}
/*
 * --------------------- TESTE DE INSERÇÃO NA 234 ------------------------
int main() {
    arv234* arv = alocaArvore();

    // Caso 1: Inserção em árvore vazia
    inserir(arv, 10);

    // Caso 2: Inserções sem split
    inserir(arv, 20);
    inserir(arv, 30);

    // Caso 3: Primeiro split (raiz cheia)
    inserir(arv, 40);

    // Caso 4: Inserção em nó não-cheio
    inserir(arv, 5);

    // Caso 5: Split em nível intermediário
    inserir(arv, 15);
    inserir(arv, 25);
    inserir(arv, 35);  // Força split não na raiz

    // Caso 6: Split que propaga até a raiz
    inserir(arv, 45);
    inserir(arv, 55);
    inserir(arv, 65);
    inserir(arv, 75);  // Força split na raiz

    // Caso 7: Inserções após split da raiz
    inserir(arv, 85);
    inserir(arv, 95);

    // Imprimir estrutura para validação
    printf("Estrutura final da arvore:\n");
    percorrePreOrdem(getRaiz(arv), 0);

    return 0;
}

------------------ TESTE INSERÇÃO/REMOÇÃO NA RUBRO NEGRA ---------------------
int main() {
    arvRb *arv = rb_alocaArvore();
    if (!arv) return 1;

    // ----------------------------------
    // Fase 1: Inserções que testam todos os casos
    // ----------------------------------
    printf("======================\n");
    printf("FASE DE INSERÇÃO\n");
    printf("======================\n");

    // Caso 1: Tio vermelho (recoloring)
    noRB *n10 = rb_alocaNo(arv, 10);
    rb_insereNo(arv, n10);

    noRB *n5 = rb_alocaNo(arv, 5);
    rb_insereNo(arv, n5);

    noRB *n15 = rb_alocaNo(arv, 15);
    rb_insereNo(arv, n15);

    noRB *n3 = rb_alocaNo(arv, 3);  // Ativa recoloring (tio 15 vermelho)
    rb_insereNo(arv, n3);

    printf("Após inserções iniciais (Caso 1 - Recoloring):\n");
    rb_percorrePreOrdem(arv, rb_getRaiz(arv));

    // Caso 2/3: Tio preto + configuração triângulo
    noRB *n1 = rb_alocaNo(arv, 1);  // Ativa rotação direita-esquerda
    rb_insereNo(arv, n1);

    printf("\nApós inserção do 1 (Caso 2/3 - Triângulo):\n");
    rb_percorrePreOrdem(arv, rb_getRaiz(arv));

    // Caso 2/3: Tio preto + configuração linha
    noRB *n20 = rb_alocaNo(arv, 20); // Ativa rotação esquerda
    rb_insereNo(arv, n20);

    noRB *n25 = rb_alocaNo(arv, 25); // Ativa Caso 3 (linha)
    rb_insereNo(arv, n25);

    printf("\nApós inserção do 25 (Caso 3 - Linha):\n");
    rb_percorrePreOrdem(arv, rb_getRaiz(arv));

    // Inserção que causa múltiplos rebalanceamentos
    noRB *n2 = rb_alocaNo(arv, 2);
    rb_insereNo(arv, n2);

    noRB *n4 = rb_alocaNo(arv, 4);
    rb_insereNo(arv, n4);

    printf("\nApós inserções adicionais (múltiplos casos):\n");
    rb_percorrePreOrdem(arv, rb_getRaiz(arv));

    // ----------------------------------
    // Fase 2: Remoções que testam todos os casos
    // ----------------------------------
    printf("\n\n======================\n");
    printf("FASE DE REMOÇÃO\n");
    printf("======================\n");

    // Caso 1: Irmão vermelho
    rb_removeNo(arv, 1);
    printf("\nApós remover 1 (Caso 1 - Irmão vermelho):\n");
    rb_percorrePreOrdem(arv, rb_getRaiz(arv));

    // Caso 2: Irmão preto com sobrinhos pretos
    rb_removeNo(arv, 2);
    printf("\nApós remover 2 (Caso 2 - Sobrinhos pretos):\n");
    rb_percorrePreOrdem(arv, rb_getRaiz(arv));

    // Caso 3/4: Irmão preto com sobrinho vermelho
    rb_removeNo(arv, 3);
    printf("\nApós remover 3 (Caso 3/4 - Sobrinho vermelho):\n");
    rb_percorrePreOrdem(arv, rb_getRaiz(arv));

    // Remoção de nó com dois filhos
    rb_removeNo(arv, 10); // Raiz
    printf("\nApós remover 10 (nó com dois filhos):\n");
    rb_percorrePreOrdem(arv, rb_getRaiz(arv));

    // Remoção que causa múltiplos rebalanceamentos
    rb_removeNo(arv, 4);
    rb_removeNo(arv, 5);
    printf("\nApós remoções múltiplas:\n");
    rb_percorrePreOrdem(arv, rb_getRaiz(arv));

    // Remoção de último nó
    rb_removeNo(arv, 15);
    rb_removeNo(arv, 20);
    rb_removeNo(arv, 25);
    printf("\nApós remover todos os elementos:\n");
    rb_percorrePreOrdem(arv, rb_getRaiz(arv));

    // Liberar memória (implemente esta função!)
    // rb_desalocaArvore(arv);

    return 0;
}*/