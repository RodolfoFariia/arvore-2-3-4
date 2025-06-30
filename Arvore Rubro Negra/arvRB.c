//
// Created by rodolfo on 30/06/25.
//
#include <stdio.h>
#include <stdlib.h>
#include "arvRB.h"

// Definindo struct da árvore rubro negra
// sentinelaRaiz->dir irá apontar para a raiz da árvore
struct arvoreRB{
    noRB *sentinelaRaiz;
    noRB *sentinelaFolha;
};


// Definindo struct do nó
struct no {
    noRB *pai;
    noRB *dir;
    noRB *esq;
    char cor; // P - preto // V - vermelho
    int chave;
    int alturaPreto;
};


arvRb *rb_alocaArvore(){
    arvRb *arv = (arvRb*) malloc(sizeof(arvRb));
    if (!arv) return NULL;

    // alocando nó sentinela raiz
    noRB *raiz = (noRB*) malloc(sizeof(noRB));
    if (!raiz){
        free(arv);
        return NULL;
    }

    // alocando nó sentinela folha
    noRB *folha = (noRB*) malloc(sizeof(noRB));
    if (!folha){
        free(arv);
        free(folha);
        return NULL;
    }


    raiz->pai = raiz->dir = raiz->esq = folha;
    raiz->chave = 1000;
    raiz->cor = 'P';

    folha->pai = folha->dir = folha->esq = folha;
    folha->chave = -1000;
    folha->cor = 'P';

    // inicializando atributos da arvore
    arv->sentinelaFolha = folha;
    arv->sentinelaRaiz = raiz;
    arv->sentinelaRaiz->dir = arv->sentinelaFolha;

    return arv;
}


noRB *rb_alocaNo(arvRb *arv, int chave){
    noRB *novoNo = (noRB*) malloc(sizeof(noRB));
    if (!novoNo) return NULL;

    // inicializando atributos do nó
    novoNo->pai = novoNo->dir = novoNo->esq = arv->sentinelaFolha;
    novoNo->chave = chave;
    novoNo->cor = 'V';
    novoNo->alturaPreto = 0;
    return novoNo;
}

noRB *rb_getRaiz(arvRb *arv){
    return arv->sentinelaRaiz->dir;
}

void rb_percorrePreOrdem(arvRb *arv, noRB *n) {
    if (n == arv->sentinelaFolha) {
        return;
    }

    printf("Chave: %d, Cor: %c\n", n->chave, n->cor);
    printf("  Esquerda: ");
    if (n->esq == arv->sentinelaFolha) printf("FOLHA\n");
    else printf("%d (%c)\n", n->esq->chave, n->esq->cor);

    printf("  Direita: ");
    if (n->dir == arv->sentinelaFolha) printf("FOLHA\n");
    else printf("%d (%c)\n", n->dir->chave, n->dir->cor);

    printf("---\n");

    rb_percorrePreOrdem(arv, n->esq);
    rb_percorrePreOrdem(arv, n->dir);
}


void rb_insereNo(arvRb *arv, noRB *novoNo){
    // verificando validade da árvore e do nó
    if (!arv || !novoNo) return;

    noRB *aux = arv->sentinelaRaiz->dir;
    noRB *pai = arv->sentinelaRaiz;

    while (aux != arv->sentinelaFolha)
    {
        pai = aux;
        if (aux->chave > novoNo->chave)
        {
            aux = aux->esq;
        }
        else
        {
            aux = aux->dir;
        }
    }

    if (pai == arv->sentinelaRaiz || pai->chave < novoNo->chave)
    {
        pai->dir = novoNo;
    }
    else
    {
        pai->esq = novoNo;
    }

    novoNo->pai = pai;

    rb_balanceamentoInsercao(arv, novoNo);

    arv->sentinelaRaiz->dir->cor = 'P';
}


int rb_removeNo(arvRb *arv, int chave){
    // Validando árvore
    if (!arv) return -1;

    // Variaveis auxiliares
    noRB *aux = arv->sentinelaRaiz->dir;
    noRB *pai = arv->sentinelaRaiz;

    while (aux != arv->sentinelaFolha && aux->chave != chave)
    {
        pai = aux;
        if (aux->chave > chave)
        {
            aux = aux->esq;
        }
        else
        {
            aux = aux->dir;
        }
    }

    // Não encontrou o elemento dentro da arvore
    if(aux == arv->sentinelaFolha) return 1;

    char corOriginal = aux->cor;
    int chaveRemovida = aux->chave;

    // remoção de nó com grau 2a
    if (aux->dir != arv->sentinelaFolha && aux->esq != arv->sentinelaFolha){

        // encontrando o predecessor
        noRB *predecessor = aux->esq;

        while (predecessor->dir != arv->sentinelaFolha){
            predecessor = predecessor->dir;
        }


        // realizando cópia dos elementos
        corOriginal = predecessor->cor;
        aux->chave = predecessor->chave;

        // atualizando auxiliares
        aux = predecessor;
        pai = predecessor->pai;
    }

    // remoção de nó com grau 1
     if (aux->dir != arv->sentinelaFolha || aux->esq != arv->sentinelaFolha){

        // verificando se filho esta a direita ou a esqueda
        noRB *filho;
        if (aux->dir != arv->sentinelaFolha)
            filho = aux->dir;
        else
            filho = aux->esq;

        // atualizando ponteiro do pai
        if (aux == arv->sentinelaRaiz->dir)
        {
            arv->sentinelaRaiz->dir = filho;
        }
        else
        {
            if (pai->esq == aux)
                pai->esq = filho;
            else
                pai->dir = filho;
        }

        filho->pai = pai;
        chaveRemovida = aux->chave;

        if (corOriginal == 'P'){
            rb_balanceamentoRemocao(arv, filho, pai);
        }

        free(aux);
        return 1;

     }


    // remoção de nó com grau 0
    if (aux == arv->sentinelaRaiz->dir){
        arv->sentinelaRaiz->dir = arv->sentinelaFolha;
    }
    else
    {
        if (pai->esq == aux)
                pai->esq = arv->sentinelaFolha;
            else
                pai->dir = arv->sentinelaFolha;
    }

    arv->sentinelaFolha->pai = pai;
    if (corOriginal == 'P'){
        rb_balanceamentoRemocao(arv, arv->sentinelaFolha, arv->sentinelaFolha->pai);
    }
    arv->sentinelaFolha->pai = NULL;
    free(aux);

    return 0;

}


void rb_balanceamentoInsercao(arvRb *arv, noRB *novoNo){
    // verificando validade da árvore e do nó
    if (!arv || !novoNo) return;

    noRB *pai = novoNo->pai;
    noRB *avo, *tio;

    while (pai != arv->sentinelaRaiz && pai->cor == 'V')
    {
        avo = pai->pai;

        if (pai == avo->esq)
        {
            // está a esquerda do avo

            tio = avo->dir;

            if (tio->cor == 'V')
            {
                pai->cor = 'P';
                tio->cor = 'P';
                avo->cor = 'V';
                novoNo = avo;
                pai = novoNo->pai;
            }
            else
            {
                // tio é preto

                if (pai->dir == novoNo)
                {
                    novoNo = pai;
                    rb_rotacaoEsquerda(arv, novoNo);
                    pai = novoNo->pai;
                    avo = pai->pai;
                }

                pai->cor = 'P';
                avo->cor = 'V';
                rb_rotacaoDireita(arv, avo);
            }
        }
        else
        {
            // está a direita do avó

            tio = avo->esq;

            // Caso 1
            if (tio->cor == 'V')
            {
                pai->cor = 'P';
                tio->cor = 'P';
                avo->cor = 'V';
                novoNo = avo;
                pai = novoNo->pai;
            }
            else
            {
                // tio é preto

                // Caso 2
                if (pai->esq == novoNo)
                {
                    novoNo = pai;
                    rb_rotacaoDireita(arv, novoNo);
                    pai = novoNo->pai;
                    avo = pai->pai;
                }

                pai->cor = 'P';
                avo->cor = 'V';
                rb_rotacaoEsquerda(arv, avo);
            }
        }

    }

}

void rb_balanceamentoRemocao(arvRb *arv, noRB *noSucessor, noRB *noPai){

    noRB *irmao;

    while (noSucessor != arv->sentinelaRaiz->dir && noSucessor->cor == 'P'){

        if (noSucessor == noPai->esq){
            // está a esquerda do pai

            irmao = noPai->dir;

            if (irmao->cor == 'V'){
                irmao->cor = 'P';
                noPai->cor = 'V';
                rb_rotacaoEsquerda(arv, noPai);
                irmao = noPai->dir;
            }

            if (irmao->dir->cor == 'P' && irmao->esq->cor == 'P')
            {
                irmao->cor = 'V';
                noSucessor = noPai;
                noPai = noSucessor->pai;
            }
            else{
                if (irmao->dir->cor == 'P'){
                    irmao->esq->cor = 'P';
                    irmao->cor = 'V';
                    rb_rotacaoDireita(arv, irmao);
                    irmao = noPai->dir;
                }

                irmao->cor = noPai->cor;
                noPai->cor = 'P';
                irmao->dir->cor = 'P';
                rb_rotacaoEsquerda(arv, noPai);

                // fazendo com que saia do balanceamento
                noSucessor = arv->sentinelaRaiz->dir;
            }
        }
        else
        {
            // está a direita do pai

            irmao = noPai->esq;

            if (irmao->cor == 'V'){
                irmao->cor = 'P';
                noPai->cor = 'V';
                rb_rotacaoDireita(arv, noPai);
                irmao = noPai->esq;
            }

            if (irmao->dir->cor == 'P' && irmao->esq->cor == 'P')
            {
                irmao->cor = 'V';
                noSucessor = noPai;
                noPai = noSucessor->pai;
            }
            else{
                if (irmao->esq->cor == 'P'){
                    irmao->dir->cor = 'P';
                    irmao->cor = 'V';
                    rb_rotacaoEsquerda(arv, irmao);
                    irmao = noPai->esq;
                }

                irmao->cor = noPai->cor;
                noPai->cor = 'P';
                irmao->esq->cor = 'P';
                rb_rotacaoDireita(arv, noPai);

                // fazendo com que saia do balanceamento
                noSucessor = arv->sentinelaRaiz->dir;
            }
        }
    }
    noSucessor->cor = 'P';
}


void rb_rotacaoEsquerda(arvRb *arv, noRB *noDesbalanceado){
    noRB *aux = noDesbalanceado->dir;

    noDesbalanceado->dir = aux->esq;

    if (aux->esq != arv->sentinelaFolha){
        aux->esq->pai = noDesbalanceado;
    }

    aux->pai = noDesbalanceado->pai;

    if (noDesbalanceado->pai == arv->sentinelaRaiz){
        arv->sentinelaRaiz->dir = aux;
    }
    else if (noDesbalanceado == noDesbalanceado->pai->esq)
    {
        noDesbalanceado->pai->esq = aux;
    }
    else
    {
        noDesbalanceado->pai->dir = aux;
    }

    aux->esq = noDesbalanceado;
    noDesbalanceado->pai = aux;
}


void rb_rotacaoDireita(arvRb *arv, noRB *noDesbalanceado){
    noRB *aux = noDesbalanceado->esq;

    noDesbalanceado->esq = aux->dir;

    if (aux->dir != arv->sentinelaFolha){
        aux->dir->pai = noDesbalanceado;
    }

    aux->pai = noDesbalanceado->pai;

    if (noDesbalanceado->pai == arv->sentinelaRaiz){
        arv->sentinelaRaiz->dir = aux;
    }
    else if (noDesbalanceado == noDesbalanceado->pai->esq)
    {
        noDesbalanceado->pai->esq = aux;
    }
    else
    {
        noDesbalanceado->pai->dir = aux;
    }

    aux->dir = noDesbalanceado;
    noDesbalanceado->pai = aux;
}