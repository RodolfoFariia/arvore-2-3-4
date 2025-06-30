#ifndef ARV234_ARV234_H
#define ARV234_ARV234_H

typedef struct arvore234 arv234;
typedef struct no no;

// Funçao para alocar uma árvore vazia
arv234 *alocaArvore();

// Função para alocar um novo nó vazio
no *alocaNo();

// --------- FUNÇÕES PARA INSERÇÃO ---------

// Função principal de inserção
void inserir (arv234 *arv, int chave);

// Função para inserir em um nó não cheio
// nó x representa o nó onde a chave deve ser inserida
void insereNaoCheio(arv234 *arv,no *x, int chave);

// Função para realizar um split no filho
// pai->filhos[i] está completamente cheio e devemos fazer o split nele
void splitFilho(arv234 *arv,no *pai, int i);


#endif