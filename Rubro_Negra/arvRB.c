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
    raiz->pai = raiz->dir = raiz->esq = arv->sentinelaFolha; 
    raiz->chave = 1000;
    raiz->cor = 'P';


    // alocando nó sentinela folha
    no *folha = (no*) malloc(sizeof(no));
    if (!folha){
        free(arv);
        free(folha);
        return NULL;
    }
    folha->pai = folha->dir = folha->esq = arv->sentinelaFolha; 
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
    novoNo->pai = novoNo->dir = novoNo->esq = arv->sentinelaFolha;
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


void insereNo(arvRb *arv, no *novoNo){
    // verificando validade da árvore e do nó
    if (!arv || !novoNo) return;

    no *aux = arv->sentinelaRaiz->dir;
    no *pai = arv->sentinelaRaiz;

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

    balanceamentoInsercao(arv, novoNo);

    arv->sentinelaRaiz->cor = 'P';
}


int removeNo(arvRb *arv, int chave){
    // Validando árvore
    if (!arv) return -1;

    // Variaveis auxiliares
    no *aux = arv->sentinelaRaiz->dir;
    no *pai = arv->sentinelaRaiz;

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
        no *predecessor = aux->esq;

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
        no *filho;
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
            balanceamentoRemocao(arv, filho, pai);
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
        balanceamentoRemocao(arv, arv->sentinelaFolha, arv->sentinelaFolha->pai);
    }
    arv->sentinelaFolha->pai = NULL;
    free(aux);

    return 0;

}


void balanceamentoInsercao(arvRb *arv, no *novoNo){
    // verificando validade da árvore e do nó
    if (!arv || !novoNo) return;

    no *pai = novoNo->pai;
    no *avo, *tio;

    while (pai != arv->sentinelaRaiz && pai->cor == 'V')
    {
        avo = pai->pai;

        if (pai = avo->esq)
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
                    rotacaoEsquerda(arv, novoNo);
                    pai = novoNo->pai;
                    avo = pai->pai;
                }

                pai->cor = 'P';
                avo->cor = 'V';
                rotacaoDireita(arv, avo);
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
                    rotacaoDireita(arv, novoNo);
                    pai = novoNo->pai;
                    avo = pai->pai;
                }

                pai->cor = 'P';
                avo->cor = 'V';
                rotacaoEsquerda(arv, avo);
            }
        }
        
    }

}

void balanceamentoRemocao(arvRb *arv, no *noSucessor, no *noPai){
    
    no *irmao;

    while (noSucessor != arv->sentinelaRaiz->dir && noSucessor == 'P'){

        if (noSucessor == noPai->esq){
            // está a esquerda do pai

            irmao = noPai->dir;

            if (irmao->cor == 'V'){
                irmao->cor = 'P';
                noPai->cor = 'V';
                rotacaoEsquerda(arv, noPai);
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
                    rotacaoDireita(arv, irmao);
                    irmao = noPai->dir;
                }

                irmao->cor = noPai->cor;
                noPai->cor = 'P';
                irmao->dir->cor = 'P';
                rotacaoEsquerda(arv, noPai);

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
                rotacaoDireita(arv, noPai);
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
                    rotacaoEsquerda(arv, irmao);
                    irmao = noPai->esq;
                }

                irmao->cor = noPai->cor;
                noPai->cor = 'P';
                irmao->esq->cor = 'P';
                rotacaoDireita(arv, noPai);

                // fazendo com que saia do balanceamento
                noSucessor = arv->sentinelaRaiz->dir;
        }
    }
    noSucessor->cor = 'P';
}
