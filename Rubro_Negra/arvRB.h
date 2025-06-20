
#ifndef ARVRB_ARVRB_H
#define ARVRB_ARVRB_H

// renomeando structs
typedef struct arvoreRB arvRb;
typedef struct no no;


// Função para alocar uma árvore rubro negra
arvRb *alocaArvore();

// Função que aloca um novo nó
no *alocaNo(arvRb *arv, int chave);

// Função iterativa para inserir um novo nó na estrutura da árvore
void insereNo(arvRb *arv, no *novoNo);

// Função para remover um nó da arvore pela sua chave
// Retornos da função
// 0 - indica sucesso na remoção 
// 1 - indica que o elemento a ser removido não foi encontrado na árvore
// -1 - indica erro durante o processo do remoção
int removeNo(arvRb *arv, int chave);


// Percorre em pré-ordem
void percorrePreOrdem(arvRb *arv, no *n);

// Função auxiliar para retornar a raiz da árvore
no *getRaiz(arvRb *arv);

// Funções de Balanceamento da Rubro Negra

// Função para corrigir o balanceamento após inserir um novo nó
void balanceamentoInsercao(arvRb *arv, no *novoNo);

// Função para corrigir o balanceamento após remover um novo nó
void balanceamentoRemocao(arvRb *arv, no *noSucessor, no *noPai);

// rotacionar um nó a esquerda
void rotacaoEsquerda(arvRb *arv, no *noDesbalanceado);

// rotacionar um nó a direita
void rotacaoDireita(arvRb *arv, no *noDesbalanceado);


#endif