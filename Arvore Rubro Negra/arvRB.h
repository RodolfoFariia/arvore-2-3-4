
#ifndef ARVRB_ARVRB_H
#define ARVRB_ARVRB_H

// renomeando structs
typedef struct arvoreRB arvRb;
typedef struct no noRB;


// Função para alocar uma árvore rubro negra
arvRb *rb_alocaArvore();

// Função que aloca um novo nó
noRB *rb_alocaNo(arvRb *arv, int chave);

// Função iterativa para inserir um novo nó na estrutura da árvore
void rb_insereNo(arvRb *arv, noRB *novoNo);

// Função para remover um nó da arvore pela sua chave
// Retornos da função
// 0 - indica sucesso na remoção 
// 1 - indica que o elemento a ser removido não foi encontrado na árvore
// -1 - indica erro durante o processo do remoção
int rb_removeNo(arvRb *arv, int chave);


// Percorre em pré-ordem
void rb_percorrePreOrdem(arvRb *arv, noRB *n);

// Função auxiliar para retornar a raiz da árvore
noRB *rb_getRaiz(arvRb *arv);

// Funções de Balanceamento da Rubro Negra

// Função para corrigir o balanceamento após inserir um novo nó
void rb_balanceamentoInsercao(arvRb *arv, noRB *novoNo);

// Função para corrigir o balanceamento após remover um novo nó
void rb_balanceamentoRemocao(arvRb *arv, noRB *noSucessor, noRB *noPai);

// rotacionar um nó a esquerda
void rb_rotacaoEsquerda(arvRb *arv, noRB *noDesbalanceado);

// rotacionar um nó a direita
void rb_rotacaoDireita(arvRb *arv, noRB *noDesbalanceado);


#endif