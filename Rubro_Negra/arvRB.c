#include <stdio.h>
#include <stdlib.h>
#include "arvRB.h"

// Definindo struct da árvore rubro negra
struct arvoreRB{
    no *sentinelaRaiz;
    no *sentinelaFolha;
};


// Definindo struct do nó
struct no {
    no *pai;
    no *dir;
    no *esq;
    char cor;
    int chave;
    int alturaPreto;
};

