#include <stdio.h>
#include <stdlib.h>
#include "arv234.h"
/*
    Como estamos falando de uma árvore 2 3 4:
        1. Ordem = 4 (quantidade máxima de filhos)
        2. 2 -> quantidade mninima de filhos
        3. 3 -> quantidade de chaves em cada nó
*/

#define ORDEM 4
#define MAX_CHAVES (ORDEM-1)  // 3
#define MIN_CHAVES  (ORDEM - 2) // 2    
#define MAX_FILHOS ORDEM      // 4



struct arvore234{
    no *raiz;
};

/*
    struct no:
        Atributos:
            1. folha -> váriavel para indicar se o nó é uma folha ou não.
                a. 0 -> o nó atual é folha
                b. 1 -> o nó atual é um não folha
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

