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


#include <stdio.h>
#include <stdlib.h>
#include "arv234.h"

#define T           2                // grau mínimo
#define MAX_FILHOS  (2*T)            // 4
#define MAX_CHAVES  (2*T - 1)        // 3
#define MIN_CHAVES  (T - 1)          // 1




no *getRaiz(arv234 *arv) {
    return arv->raiz;
}

arv234 *alocaArvore(){
    arv234 *arv = (arv234*) malloc(sizeof(arv234));
    if (!arv)
        return NULL;

    arv->raiz = NULL;
    arv->altura = 0;
    arv->qtdSplit = 0;
    arv->qtdNos = 0;
    arv->qtdMerges = 0;
    arv->qtdRotacoes = 0;
    arv->vetorOriginal = NULL;

    return arv;
}


no *alocaNo(arv234 *arv){
    no *n = (no*) malloc(sizeof(no));
    if (!n)
        return NULL;

    n->folha = 1;
    n->qtd_chaves = 0;
    n->pai = NULL;
    for (int i=0 ; i < MAX_FILHOS; i++)
        n->filhos[i] = NULL;

    // atualizando quantidade total de nós
    arv->qtdNos+=1;

    return n;
}


/*
    Inserção na Árvore 2-3-4 – três cenários:

    1. Árvore vazia
       - Alocar um novo nó como raiz
       - Inserir a chave na raiz

    2. Inserção em nó não cheio
       - Se for folha: inserir diretamente na posição correta
       - Caso contrário:
         • Determinar o filho apropriado para descer
         • Repetir até alcançar uma folha
         • Se o nó alvo não estiver cheio, inserir a chave
         • Se estiver cheio, tratar como no caso 3

    3. Inserção em nó cheio
       - Realizar split no nó cheio:
         • O elemento mediano sobe para o pai
         • Criar um novo nó para a metade direita
       - Se o pai ficar cheio, propagar o split recursivamente
       - Após splits necessários, inserir a nova chave no nó adequado
*/

// Função principal de inserção
void inserir (arv234 *arv, int chave){
    if (!arv) return;

    // Primeiro caso -> Inserção em uma árvore vazia
    if (arv->raiz == NULL)
    {
        no* raiz = alocaNo(arv);
        raiz->chaves[0] = chave;
        raiz->qtd_chaves = 1;

        arv->altura = 1;
        arv->raiz = raiz;
    }
    else
    {
        // Árvore não está vazia

        // Vamos verificar se a raiz está cheia
        if (arv->raiz->qtd_chaves == MAX_CHAVES)
        {
            // Raiz cheia, precisamos alocar uma nova raiz

            no *s = alocaNo(arv);
            if (!s) return;

            s->folha = 0;
            s->qtd_chaves = 0;

            // Antiga raiz, vai virar filho da nova raiz s
            s->filhos[0] = arv->raiz;

            // Vamos dar split no filho
            splitFilho(arv, s, 0);

            // Nova raiz possui dois filhos
            // Decidir qual deles recebe a nova chave
            int i = 0;
            if (s->chaves[0] < chave)
                i++;

            // Vamos inserir a chave no filho de indice i
            insereNaoCheio(arv, s->filhos[i], chave);

            // Atualizar nova raiz
            arv->raiz->pai = s;
            arv->raiz = s;

            // Como alocamos uma nova raiz, aumentamos a altura da árvore
            arv->altura++;
        }
        else
        {
            // Raiz não cheia, chamamos a função de inserção não cheio
            insereNaoCheio(arv, arv->raiz, chave);
        }
    }
}

// Insere chave em nó não cheio (x) da árvore
void insereNaoCheio(arv234 *arv,no *x, int chave){
    if (!arv || !x) return;

    // indice do ultimo elemento cadastrado no no
    int i = x->qtd_chaves-1;

    // Vamos verificar se o nó é uma folha
    if (x->folha == 1){
        // Nó é uma folha

        // Vamos encontrar qual posição do nó o novo elemento deve ser inserido
        // Além de deslocar os elementos maiores
        while (i >= 0 && x->chaves[i] > chave){
            x->chaves[i+1] = x->chaves[i];
            i--;
        }

        x->chaves[i+1] = chave;
        x->qtd_chaves++;
    }
    else
    {
        // Nó não é uma folha, vamos ver em qual dos filhos ele vai ser inserido
        i = x->qtd_chaves-1;
        while (i >= 0 && x->chaves[i] > chave)
            i--;
        i++;

        // Vamos ver se o filho onde a chave deve ser inserida está cheio
        if (x->filhos[i]->qtd_chaves == MAX_CHAVES){
            // Vamos dar um split
            splitFilho(arv, x, i);

            // Após o split, temos dois filhos, vamos ver em qual inserir
            if (x->chaves[i] < chave)
                i++;
        }
        insereNaoCheio(arv, x->filhos[i], chave);
    }
}

void splitFilho(arv234 *arv, no *pai, int i) {
    if (!arv || !pai) return;

    // y é o filho cheio em pai->filhos[i]
    no *y = pai->filhos[i];
    int meio = MAX_CHAVES / 2;  // Índice da chave do meio (ex: 1 para 3 chaves)

    // 1. Criar novo nó z (irmão direito de y)
    no *z = alocaNo(arv);
    if (!z) return;
    z->folha = y->folha;
    z->pai = pai;
    z->qtd_chaves = MAX_CHAVES - meio - 1;  // Chaves após o meio

    // 2. Copiar chaves maiores que o meio para z
    for (int j = 0; j < z->qtd_chaves; j++) {
        z->chaves[j] = y->chaves[j + meio + 1];
    }

    // 3. Copiar filhos se não for folha
    if (!y->folha) {
        for (int j = 0; j <= z->qtd_chaves; j++) {  // +1 para o último filho
            z->filhos[j] = y->filhos[j + meio + 1];
            if (z->filhos[j]) z->filhos[j]->pai = z;
        }
    }

    // 4. Reduzir chaves em y (mantém chaves antes do meio)
    y->qtd_chaves = meio;

    // 5. Abrir espaço para z nos filhos do pai
    for (int j = pai->qtd_chaves; j > i; j--) {
        pai->filhos[j + 1] = pai->filhos[j];
    }
    pai->filhos[i + 1] = z;

    // 6. Abrir espaço para a nova chave no pai
    for (int j = pai->qtd_chaves - 1; j >= i; j--) {
        pai->chaves[j + 1] = pai->chaves[j];
    }

    // 7. Subir a chave do meio para o pai
    pai->chaves[i] = y->chaves[meio];
    pai->qtd_chaves++;

    arv->qtdSplit++;
}


void percorrePreOrdem(no* n, int nivel) {
    if (n == NULL) return;

    printf("Nivel %d: [", nivel);
    for (int i = 0; i < n->qtd_chaves; i++) {
        printf("%d", n->chaves[i]);
        if (i < n->qtd_chaves - 1) printf(", ");
    }
    printf("]\n");

    if (!n->folha) {
        for (int i = 0; i <= n->qtd_chaves; i++) {
            percorrePreOrdem(n->filhos[i], nivel + 1);
        }
    }
}



// --------------- FUNÇÕES PARA REMOÇÃO ---------------------

// Encontra o índice da primeira chave >= k no nó dado
int encontraChaveNo(no *n, int chave) {
    int idx = 0;
    while (idx < n->qtd_chaves && n->chaves[idx] < chave)
        idx++;
    return idx;
}

void remover(arv234 *arv, no *n, int chave) {
    // Verificação de segurança
    if (n == NULL) return;

    int idx = encontraChaveNo(n, chave);

    // Caso 1: a chave está neste nó
    if (idx < n->qtd_chaves && n->chaves[idx] == chave) {
        if (n->folha) {
            removeDaFolha(n, idx);
        } else {
            removeDeNaoFolha(arv, n, idx);
        }
    }
    // Caso 2: a chave não está neste nó
    else {
        if (n->folha) {
            // Chave não encontrada na árvore
            return;
        }

        // Flag para verificar se estamos no último filho
        int flag = (idx == n->qtd_chaves);

        // Se o filho tem menos que T chaves, preencher antes de descer
        if (n->filhos[idx]->qtd_chaves < T) {
            preencher(arv, n, idx);
        }

        // Após o preenchimento, a estrutura pode ter mudado
        // Verificamos se o índice ainda é válido
        if (flag && idx > n->qtd_chaves) {
            remover(arv, n->filhos[idx - 1], chave);
        } else {
            remover(arv, n->filhos[idx], chave);
        }
    }
}

void removeChave(arv234* arv, int chave) {
    if (!arv || !arv->raiz) return;

    remover(arv, arv->raiz, chave);

    // Se a raiz ficou vazia
    if (arv->raiz->qtd_chaves == 0) {
        no* temp = arv->raiz;
        if (arv->raiz->folha) {
            arv->raiz = NULL;
        } else {
            // A nova raiz é o primeiro filho
            arv->raiz = arv->raiz->filhos[0];
        }
        free(temp);
    }
}

// Preenche o filho[idx] que tem menos que T chaves
void preencher(arv234* arv, no* n, int idx) {
    // Tenta pegar emprestado do irmão esquerdo
    if (idx > 0 && n->filhos[idx-1]->qtd_chaves > T) {
        emprestaAnterior(n, idx);
        arv->qtdRotacoes++;
    }
    // Tenta pegar emprestado do irmão direito
    else if (idx < n->qtd_chaves && n->filhos[idx+1]->qtd_chaves > T) {
        emprestaProximo(n, idx);
        arv->qtdRotacoes++;
    }
    // Caso não possa pegar emprestado, faz merge
    else {
        if (idx > 0) {
            merge(arv, n, idx-1);
        } else {
            merge(arv, n, idx);
        }
    }
}

void merge(arv234* arv, no* n, int idx) {
    // Verificações de segurança
    if (n == NULL || idx < 0 || idx >= n->qtd_chaves) return;
    no* filho = n->filhos[idx];
    no* irmao = n->filhos[idx+1];
    if (filho == NULL || irmao == NULL) return;

    // Verifica capacidade
    if (filho->qtd_chaves + irmao->qtd_chaves + 1 > 3) return;

    // Move chave do pai para o filho
    filho->chaves[filho->qtd_chaves] = n->chaves[idx];
    filho->qtd_chaves++;

    // Copia chaves do irmão
    for (int i = 0; i < irmao->qtd_chaves; i++) {
        filho->chaves[filho->qtd_chaves + i] = irmao->chaves[i];
    }

    // Copia filhos do irmão (se aplicável)
    if (!filho->folha) {
        for (int i = 0; i <= irmao->qtd_chaves; i++) {
            filho->filhos[filho->qtd_chaves + i] = irmao->filhos[i];
        }
    }

    // Atualiza contagem total de chaves
    filho->qtd_chaves += irmao->qtd_chaves;

    // Remove chave e filho do nó pai
    for (int i = idx+1; i < n->qtd_chaves; i++) {
        n->chaves[i-1] = n->chaves[i];
    }
    for (int i = idx+2; i <= n->qtd_chaves; i++) {
        n->filhos[i-1] = n->filhos[i];
    }
    n->qtd_chaves--;

    free(irmao);
    arv->qtdMerges++;
}

// Pega uma chave do irmão direito
void emprestaProximo(no* n, int idx) {
    no* filho = n->filhos[idx];
    no* irmao = n->filhos[idx+1];

    // Move chave do pai para o filho
    filho->chaves[filho->qtd_chaves] = n->chaves[idx];

    // Move primeiro filho do irmão se necessário
    if (!filho->folha) {
        filho->filhos[filho->qtd_chaves+1] = irmao->filhos[0];
    }

    // Move primeira chave do irmão para o pai
    n->chaves[idx] = irmao->chaves[0];

    // Ajusta chaves do irmão
    for (int i = 1; i < irmao->qtd_chaves; i++) {
        irmao->chaves[i-1] = irmao->chaves[i];
    }

    // Ajusta filhos do irmão se necessário
    if (!irmao->folha) {
        for (int i = 1; i <= irmao->qtd_chaves; i++) {
            irmao->filhos[i-1] = irmao->filhos[i];
        }
    }

    filho->qtd_chaves++;
    irmao->qtd_chaves--;
}

// Pega uma chave do irmão esquerdo
void emprestaAnterior(no* n, int idx) {
    no* filho = n->filhos[idx];
    no* irmao = n->filhos[idx-1];

    // Abre espaço no filho
    for (int i = filho->qtd_chaves-1; i >= 0; i--) {
        filho->chaves[i+1] = filho->chaves[i];
    }

    // Move filhos se necessário
    if (!filho->folha) {
        for (int i = filho->qtd_chaves; i >= 0; i--) {
            filho->filhos[i+1] = filho->filhos[i];
        }
    }

    // Move chave do pai para o filho
    filho->chaves[0] = n->chaves[idx-1];

    // Move último filho do irmão se necessário
    if (!filho->folha) {
        filho->filhos[0] = irmao->filhos[irmao->qtd_chaves];
    }

    // Move última chave do irmão para o pai
    n->chaves[idx-1] = irmao->chaves[irmao->qtd_chaves-1];

    filho->qtd_chaves++;
    irmao->qtd_chaves--;
}

// Remove chave de nó folha
void removeDaFolha(no* n, int idx) {
    for (int i = idx+1; i < n->qtd_chaves; i++) {
        n->chaves[i-1] = n->chaves[i];
    }
    n->qtd_chaves--;
}

// Remove chave de nó interno
void removeDeNaoFolha(arv234* arv, no* n, int idx) {
    int chave = n->chaves[idx];

    // Caso 3a: Filho anterior tem chaves suficientes
    if (n->filhos[idx]->qtd_chaves > T) {
        no* pred = n->filhos[idx];
        while (!pred->folha) {
            pred = pred->filhos[pred->qtd_chaves];
        }
        int pred_chave = pred->chaves[pred->qtd_chaves-1];
        n->chaves[idx] = pred_chave;
        remover(arv, n->filhos[idx], pred_chave);
    }
    // Caso 3b: Filho posterior tem chaves suficientes
    else if (n->filhos[idx+1]->qtd_chaves > T) {
        no* succ = n->filhos[idx+1];
        while (!succ->folha) {
            succ = succ->filhos[0];
        }
        int succ_chave = succ->chaves[0];
        n->chaves[idx] = succ_chave;
        remover(arv, n->filhos[idx+1], succ_chave);
    }
    // Caso 3c: Ambos os filhos têm número mínimo de chaves
    else {
        merge(arv, n, idx);
        remover(arv, n->filhos[idx], chave);
    }
}

// --------- Funções Auxiliares de Consulta ---------

int getQtdSplits(arv234 *arv) {
    return arv->qtdSplit;
}

int getAltura(arv234 *arv) {
    return arv->altura;
}

// Considerando um bloco de memória de HD de 512 bytes,
// o tamanho aproximado da struct `no` (incluindo padding) é de ~64 bytes.
// Sendo assim, um bloco acomoda 512/64 = 8 nós.
int getQtdBlocos(arv234 *arv) {
    int tam_bloco = 512;
    int tam_no = 64;

    if (arv->qtdNos == 0) return 0;

    int nos_por_bloco = tam_bloco / tam_no;

    // ceil(arv->qtdNos / nos_por_bloco)
    int blocos_necessarios = (arv->qtdNos + nos_por_bloco - 1) / nos_por_bloco;

    return blocos_necessarios;
}

int getQtdRotacoes(arv234 *arv) {
    return arv->qtdRotacoes;
}

int getQtdMerges(arv234 *arv) {
    return arv->qtdMerges;
}