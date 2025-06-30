#include <stdio.h>
#include <stdlib.h>
#include "arv234.h"
/*
    Como estamos falando de uma árvore 2 3 4:
        1. Ordem = 4 (quantidade máxima de filhos)
        2. 2 -> quantidade mninima de filhos
        3. 3 -> quantidade de chaves em cada nó
*/

#define T           2                // grau mínimo
#define MAX_FILHOS  (2*T)            // 4
#define MAX_CHAVES  (2*T - 1)        // 3
#define MIN_CHAVES  (T - 1)          // 1



struct arvore234{
    no *raiz;
    int altura;
    int qtdSplit;
    int totalBlocos;
    int qtdMerges;
};

/*
    struct no:
        Atributos:
            1. folha -> váriavel para indicar se o nó é uma folha ou não.
                a. 0 -> o nó atual é um não folha
                b. 1 -> o nó atual é um folha
            2. qtd_chaves -> representa a quantidade de chaves inseridas atualmente
            3. chaves -> vetor de inteiros para armazenar as chaves do nó
            4. filhos -> vetor de ponteiros do tipo no, para armazenar os filhos de cada chave
            5. pai -> ponteiro do tipo no, apontando para o pai do nó atual
*/
struct no {
    int folha;
    int qtd_chaves;
    int chaves[MAX_CHAVES];
    no *filhos[MAX_FILHOS];
    no *pai;
};

no *getRaiz(arv234 *arv) {
    return arv->raiz;
}

arv234 *alocaArvore(){
    arv234 *arv = (arv234*) malloc(sizeof(arv234));
    if (!arv)
        return NULL;

    arv->raiz = NULL;
    arv->altura = 0;
    arv->qtdSplit = 0;
    arv->totalBlocos = 0;
    arv->qtdMerges = 0;

    return arv;
}


no *alocaNo(){
    no *n = (no*) malloc(sizeof(no));
    if (!n)
        return NULL;

    n->folha = 1;
    n->qtd_chaves = 0;
    n->pai = NULL;
    for (int i=0 ; i < MAX_FILHOS; i++)
        n->filhos[i] = NULL;

    return n;
}


/*
    Para realizar a inserção vamos ter 3 casos distintos:
        1. Inserção em uma árvore vazia:
            a. Alocamos um nó para a raiz e realizamos a inserção
        2. Inserção em um nó não cheio
            a. Para inserir em um nó não cheio, verificamos se é uma folha ou não
            b. Em caso de insucesso, procuramos em qual filho deve ser inserido até chegar numa folha
            c. Verificamos se o nó está cheio, caso não esteja, só realizamos a inserção
            d. Em caso de nó cheio, vamos realizar o caso 3
        3. Inserção em nó cheio
            a. É preciso realizar um split no nó, onde o elemento central sobe para o pai, um novo nó
                é alocado, e depois realizamos a inserção
            b. É possível que, ao tentar passar o elemento central para o pai, este esteja cheio, então o split sobe recursivamente
                até que seja possível inserir sem realizar um split.
*/

// Primeira função de inserção
void inserir (arv234 *arv, int chave){
    if (!arv) return;

    // Primeiro caso -> Inserção em uma árvore vazia
    if (arv->raiz == NULL)
    {
        no* raiz = alocaNo();
        raiz->chaves[0] = chave;
        raiz->qtd_chaves = 1;

        arv->altura = 1;
        arv->raiz = raiz;
    }
    else
    {
        // Árvore não está vazia

        // Vamos verificar se a raiz está cheia
        if (arv->raiz->qtd_chaves == MAX_CHAVES)
        {
            // Raiz cheia, precisamos alocar uma nova raiz

            no *s = alocaNo();
            if (!s) return;

            s->folha = 0;
            s->qtd_chaves = 0;

            // Antiga raiz, vai virar filho da nova raiz s
            s->filhos[0] = arv->raiz;

            // Vamos dar split no filho
            splitFilho(arv, s, 0);

            // Nova raiz possui dois filhos
            // Decidir qual deles recebe a nova chave
            int i = 0;
            if (s->chaves[0] < chave)
                i++;

            // Vamos inserir a chave no filho de indice i
            insereNaoCheio(arv, s->filhos[i], chave);

            // Atualizar nova raiz
            arv->raiz->pai = s;
            arv->raiz = s;

            arv->altura++;
        }
        else
        {
            // Raiz não cheia, chamamos a função de inserção não cheio
            insereNaoCheio(arv, arv->raiz, chave);
        }
    }
}

void insereNaoCheio(arv234 *arv,no *x, int chave){
    if (!arv || !x) return;

    // indice do ultimo elemento cadastrado no no
    int i = x->qtd_chaves-1;

    // Vamos verificar se o nó é uma folha
    if (x->folha == 1){
        // Nó é uma folha

        // Vamos encontrar qual posição do nó o novo elemento deve ser inserido
        // Além de deslocar os elementos maiores
        while (i >= 0 && x->chaves[i] > chave){
            x->chaves[i+1] = x->chaves[i];
            i--;
        }

        x->chaves[i+1] = chave;
        x->qtd_chaves++;
    }
    else
    {
        // Nó não é uma folha, vamos ver em qual dos filhos ele vai ser inserido
        i = x->qtd_chaves-1;
        while (i >= 0 && x->chaves[i] > chave)
            i--;
        i++;

        // Vamos ver se o filho onde a chave deve ser inserida está cheio
        if (x->filhos[i]->qtd_chaves == MAX_CHAVES){
            // Vamos dar um split
            splitFilho(arv, x, i);

            // Após o split, temos dois filhos, vamos ver em qual inserir
            if (x->chaves[i] < chave)
                i++;
        }
        insereNaoCheio(arv, x->filhos[i], chave);
    }
}

void splitFilho(arv234 *arv, no *pai, int i) {
    if (!arv || !pai) return;

    // y é o filho cheio em pai->filhos[i]
    no *y = pai->filhos[i];
    int meio = MAX_CHAVES / 2;  // Índice da chave do meio (ex: 1 para 3 chaves)

    // 1. Criar novo nó z (irmão direito de y)
    no *z = alocaNo();
    if (!z) return;
    z->folha = y->folha;
    z->pai = pai;
    z->qtd_chaves = MAX_CHAVES - meio - 1;  // Chaves após o meio

    // 2. Copiar chaves maiores que o meio para z
    for (int j = 0; j < z->qtd_chaves; j++) {
        z->chaves[j] = y->chaves[j + meio + 1];
    }

    // 3. Copiar filhos se não for folha
    if (!y->folha) {
        for (int j = 0; j <= z->qtd_chaves; j++) {  // +1 para o último filho
            z->filhos[j] = y->filhos[j + meio + 1];
            if (z->filhos[j]) z->filhos[j]->pai = z;
        }
    }

    // 4. Reduzir chaves em y (mantém chaves antes do meio)
    y->qtd_chaves = meio;

    // 5. Abrir espaço para z nos filhos do pai
    for (int j = pai->qtd_chaves; j > i; j--) {
        pai->filhos[j + 1] = pai->filhos[j];
    }
    pai->filhos[i + 1] = z;

    // 6. Abrir espaço para a nova chave no pai
    for (int j = pai->qtd_chaves - 1; j >= i; j--) {
        pai->chaves[j + 1] = pai->chaves[j];
    }

    // 7. Subir a chave do meio para o pai
    pai->chaves[i] = y->chaves[meio];
    pai->qtd_chaves++;

    arv->qtdSplit++;
}


void percorrePreOrdem(no* n, int nivel) {
    if (n == NULL) return;

    printf("Nivel %d: [", nivel);
    for (int i = 0; i < n->qtd_chaves; i++) {
        printf("%d", n->chaves[i]);
        if (i < n->qtd_chaves - 1) printf(", ");
    }
    printf("]\n");

    if (!n->folha) {
        for (int i = 0; i <= n->qtd_chaves; i++) {
            percorrePreOrdem(n->filhos[i], nivel + 1);
        }
    }
}
