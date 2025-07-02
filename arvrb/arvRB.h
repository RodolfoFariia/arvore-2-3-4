/******************************************************************************
*                                                                            *
 *         ÁRVORES 2-3-4 E SUA EQUIVALÊNCIA COM ÁRVORES RUBRO-NEGRAS          *
 *                                                                            *
 *       Algoritmos e Estrutura de Dados II – Ciência da Computação – UNIFEI  *
 *       Professora: Vanessa Cristina Oliveira de Souza                       *
 *                                                                            *
 *       Trabalho desenvolvido por:                                           *
 *           Rodolfo Henrique Faria              – 2024008886                 *
 *           Rafael Santos Pinto Batista Leite   – 2024004564                 *
 *                                                                            *
 ******************************************************************************/

#ifndef ARVRB_H
#define ARVRB_H

// Renomeação de structs
typedef struct arvoreRB arvRb;
typedef struct noRB noRB;

// Definição da estrutura da Árvore Rubro-Negra
// sentinelaRaiz->dir aponta para o nó raiz da árvore
struct arvoreRB {
    noRB *sentinelaRaiz;
    noRB *sentinelaFolha;
};

// Definição da estrutura de um nó da Árvore Rubro-Negra
struct noRB {
    noRB *pai;
    noRB *dir;
    noRB *esq;
    char cor;        // 'P' = preto, 'V' = vermelho
    int chave;
    int alturaPreto; // Conta o número de nós pretos no caminho até as folhas
};

// Aloca e inicializa uma nova Árvore Rubro-Negra
arvRb *rb_alocaArvore();

// Cria e inicializa um novo nó com a chave informada
noRB *rb_alocaNo(arvRb *arv, int chave);

// Insere iterativamente um nó na Árvore Rubro-Negra
void rb_insereNo(arvRb *arv, noRB *novoNo);

// Remove um nó pela chave
// Retorno:  0 = sucesso
//            1 = chave não encontrada
//           -1 = erro durante a remoção
int rb_removeNo(arvRb *arv, int chave);

// Percorre a árvore em pré-ordem, a partir do nó n
void rb_percorrePreOrdem(arvRb *arv, noRB *n);

// Retorna a raiz da árvore (sentinelaRaiz->dir)
noRB *rb_getRaiz(arvRb *arv);

// ===== Funções de balanceamento da Árvore Rubro-Negra =====

// Ajusta o balanceamento após inserção de novo nó
void rb_balanceamentoInsercao(arvRb *arv, noRB *novoNo);

// Ajusta o balanceamento após remoção de nó
void rb_balanceamentoRemocao(arvRb *arv, noRB *noSucessor, noRB *noPai);

// Rotaciona o subárvore para a esquerda a partir de noDesbalanceado
void rb_rotacaoEsquerda(arvRb *arv, noRB *noDesbalanceado);

// Rotaciona o subárvore para a direita a partir de noDesbalanceado
void rb_rotacaoDireita(arvRb *arv, noRB *noDesbalanceado);


// ===== Funções auxiliares para conversão entre estruturas =====

// Define a raiz da árvore (sentinelaRaiz->dir)
void rb_setRaiz(arvRb *arv, noRB *novaRaiz);

// Altera a cor de um nó ('P' ou 'V')
void rb_setCor(noRB *no, char cor);

#endif // ARVRB_H
