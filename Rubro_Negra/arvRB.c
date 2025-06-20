#include <stdio.h>
#include <stdlib.h>
#include "arvRB.h"

// Definindo struct da árvore rubro negra
// sentinelaRaiz->dir irá apontar para a raiz da árvore
struct arvoreRB{
    no *sentinelaRaiz;
    no *sentinelaFolha;
};


// Definindo struct do nó
struct no {
    no *pai;
    no *dir;
    no *esq;
    char cor; // P - preto // V - vermelho
    int chave;
    int alturaPreto;
};


arvRb *alocaArvore(){
    arvRb *arv = (arvRb*) malloc(sizeof(arvRb));
    if (!arv) return NULL;

    // alocando nó sentinela raiz
    no *raiz = (no*) malloc(sizeof(no));
    if (!raiz){
        free(arv);
        return NULL;
    }
    raiz->pai = raiz->dir = raiz->esq = NULL; 
    raiz->chave = 1000;
    raiz->cor = 'P';


    // alocando nó sentinela folha
    no *folha = (no*) malloc(sizeof(no));
    if (!folha){
        free(arv);
        free(folha);
        return NULL;
    }
    folha->pai = folha->dir = folha->esq = NULL; 
    folha->chave = -1000;
    folha->cor = 'P';

    // inicializando atributos da arvore
    arv->sentinelaFolha = folha;
    arv->sentinelaRaiz = raiz;

    return arv;
}


no *alocaNo(arvRb *arv, int chave){
    no *novoNo = (no*) malloc(sizeof(no));
    if (!novoNo) return NULL;

    // inicializando atributos do nó
    novoNo->pai = novoNo->dir = novoNo->esq = NULL;
    novoNo->chave = chave;
    novoNo->cor = 'V';
    novoNo->alturaPreto = 0;

    return novoNo;
}

no *getRaiz(arvRb *arv){
    return arv->sentinelaRaiz->dir;
}

void percorrePreOrdem(arvRb *arv, no *n){
    // caso base da recursão
    if (n == arv->sentinelaFolha)
        return;
    
    printf("%d -- %s\n", n->chave, n->cor);
    percorrePreOrdem(arv, n->esq);
    percorrePreOrdem(arv, n->dir);
}
