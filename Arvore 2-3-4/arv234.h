/******************************************************************************
 *                                                                            *
 *     ÁRVORES 2-3-4 E SUA EQUIVALÊNCIA COM ÁRVORES RUBRO-NEGRAS             *
 *                                                                            *
 *   Algoritmos e Estrutura de Dados II – Ciência da Computação – UNIFEI      *
 *   Professora: Vanessa Cristina Oliveira de Souza                          *
 *                                                                            *
 *   Trabalho desenvolvido por:                                               *
 *       Rodolfo Henrique Faria              – 2024008886                     *
 *       Rafael Santos Pinto Batista Leite   – 2024004564                     *
 *                                                                            *
 ******************************************************************************/

#ifndef ARV234_H
#define ARV234_H

#define T           2                // Grau mínimo
#define MAX_FILHOS  (2 * T)          // 4
#define MAX_CHAVES  (2 * T - 1)      // 3
#define MIN_CHAVES  (T - 1)          // 1

// Renomeação de structs
typedef struct arvore234 arv234;
typedef struct no no;

// Definição da estrutura da Árvore 2-3-4
struct arvore234 {
    no *raiz;             // Ponteiro para o nó raiz
    int altura;           // Altura atual da árvore
    int qtdSplit;         // Quantidade de splits realizados
    int qtdNos;           // Quantidade de nós na árvore
    int qtdMerges;        // Quantidade de merges realizados
    int qtdRotacoes;      // Quantidade de rotações realizadas
    int *vetorOriginal;   // Vetor usado na construção da árvore
};

// Definição da estrutura de um nó da Árvore 2-3-4
struct no {
    int folha;                     // 0 = não folha, 1 = folha
    int qtd_chaves;                // Número de chaves atualmente no nó
    int chaves[MAX_CHAVES];        // Vetor de chaves do nó
    no *filhos[MAX_FILHOS];        // Vetor de ponteiros para os filhos
    no *pai;                       // Ponteiro para o nó pai
};

// --------- Funções de Alocação ---------

// Aloca e inicializa uma árvore vazia
arv234 *alocaArvore();

// Aloca e inicializa um novo nó vazio
no *alocaNo(arv234 *arv);

// --------- Funções para Inserção ---------

// Insere uma chave na árvore (rotina principal)
void inserir(arv234 *arv, int chave);

// Insere chave em nó não cheio (x) da árvore
void insereNaoCheio(arv234 *arv, no *x, int chave);

// Realiza split no filho cheio pai->filhos[i]
void splitFilho(arv234 *arv, no *pai, int i);

// Percorre a árvore em pré-ordem a partir do nó n, exibindo o nível
void percorrePreOrdem(no *n, int nivel);

// Retorna o ponteiro para o nó raiz
no *getRaiz(arv234 *arv);

// --------- Funções para Remoção ---------

// Encontra índice da primeira chave >= chave no nó n
int encontraChaveNo(no *n, int chave);

// Remove a chave de um nó (rotina principal)
void removeChave(arv234 *arv, int chave);

// Trata remoção de chave em nó folha (índice idx)
void removeDaFolha(no *n, int idx);

// Trata remoção de chave em nó interno (índice idx)
void removeDeNaoFolha(arv234 *arv, no *n, int idx);

// Preenche nó n no índice idx quando estiver abaixo do mínimo
// Tenta emprestar do irmão à esquerda, depois à direita, ou faz merge
void preencher(arv234 *arv, no *n, int idx);

// Realiza merge de n->filhos[idx] com seu irmão
void merge(arv234 *arv, no *n, int idx);

// Empresta chave do próximo irmão (à direita)
void emprestaProximo(no *n, int idx);

// Empresta chave do irmão anterior (à esquerda)
void emprestaAnterior(no *n, int idx);

// --------- Funções Auxiliares de Consulta ---------

int getQtdSplits(arv234 *arv);
int getAltura(arv234 *arv);
int getQtdBlocos(arv234 *arv);
int getQtdRotacoes(arv234 *arv);
int getQtdMerges(arv234 *arv);

#endif // ARV234_H
