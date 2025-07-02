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

#include "experimentos.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// Função para preencher o vetor com números aleatórios
// Utilizamos a técnica de Fisher-Yates para embaralhar os números dentro do vetor
void preencheVetorAleatorioInsercao(int *vetor, int tam) {
    // 1) Preenche com valores distintos de 0 a tam-1
    for (int i = 0; i < tam; i++) {
        vetor[i] = i;
    }
    // 2) Embaralha in-place (Fisher–Yates)
    for (int i = tam - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int tmp = vetor[i];
        vetor[i] = vetor[j];
        vetor[j] = tmp;
    }
}

// Função para preencher vetor de remoção
int preencheVetorAleatorioRemocao(int *vetorOriginal, int *vetorRemocao, int tamOriginal, int percentual) {
    int tamRemocao = (int)((percentual / 100.0) * tamOriginal);
    if (percentual > 0 && tamRemocao == 0) tamRemocao = 1;

    int *indices = (int*)malloc(tamOriginal * sizeof(int));
    for (int i = 0; i < tamOriginal; i++) {
        indices[i] = i;
    }

    for (int i = tamOriginal - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }

    for (int i = 0; i < tamRemocao; i++) {
        vetorRemocao[i] = vetorOriginal[indices[i]];
    }

    free(indices);
    return tamRemocao;
}

void resetContadores(arv234 *arv) {
    if (arv == NULL) return;

    arv->qtdSplit = 0;
    arv->qtdMerges = 0;
    arv->qtdRotacoes = 0;
}

arv234 *realizaTestesInsercao(FILE *arq, char *instancia, int tam, int id) {

    int *vetor = (int*)malloc(tam * sizeof(int));
    if (!vetor) return NULL;

    preencheVetorAleatorioInsercao(vetor, tam);

    arv234 *arvore = alocaArvore();
    if (!arvore) {
        free(vetor);
        return NULL;
    }

    // Resetar contadores antes de iniciar inserções
    resetContadores(arvore);

    for (int i = 0; i < tam; i++) {
        inserir(arvore, vetor[i]);
    }

    if (id == 1) {
        int qtdSplits = getQtdSplits(arvore);
        int altura = getAltura(arvore);
        int qtdBlocos = getQtdBlocos(arvore);
        fprintf(arq, "%s,%d,%d,%d,%d\n", instancia, tam, qtdSplits, altura, qtdBlocos);
    }

    // Armazenar vetor na árvore para uso posterior
    arvore->vetorOriginal = vetor;
    return arvore;
}

void inicializaTesteInsercao() {
    int tamanhos[] = {100, 1000, 10000, 100000};
    int qtdTamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);
    char instancia[50];

    FILE *arq = fopen("experimentoInsercao.csv", "w");
    if (!arq) {
        perror("Erro ao abrir arquivo");
        return;
    }

    fprintf(arq, "instancia,tam,qtdSplits,altura,qtdBlocos\n");

    for (int i = 0; i < qtdTamanhos; i++) {
        sprintf(instancia, "insercao_%d", tamanhos[i]);
        arv234 *arvore = realizaTestesInsercao(arq, instancia, tamanhos[i], 1);
        if (arvore) {
            free(arvore->vetorOriginal);
        }
    }

    fclose(arq);
}

void realizaTesteRemocao(FILE *arq, char *instancia, int *vetorOriginal, int tamOriginal, int percentual, arv234 *arvore) {
    int tamRemocao = (int)(tamOriginal * (percentual / 100.0));
    int *vetorRemocao = (int*)malloc(tamRemocao * sizeof(int));
    if (!vetorRemocao) return;

    tamRemocao = preencheVetorAleatorioRemocao(vetorOriginal, vetorRemocao, tamOriginal, percentual);

    // Resetar contadores antes das remoções
    resetContadores(arvore);

    for (int i = 0; i < tamRemocao; i++) {
        remover(arvore, getRaiz(arvore), vetorRemocao[i]);
    }

    int qtdRotacoes = getQtdRotacoes(arvore);
    int qtdMerges = getQtdMerges(arvore);
    int altura = getAltura(arvore);
    int qtdBlocos = getQtdBlocos(arvore);

    fprintf(arq, "%s,%d,%d,%d,%d,%d\n", instancia, percentual, qtdRotacoes, qtdMerges, altura, qtdBlocos);

    free(vetorRemocao);
}

void inicializaTesteRemocao() {
    int percentuais[] = {10, 20, 35, 50};
    int qtdPercentuais = sizeof(percentuais) / sizeof(percentuais[0]);
    char instancia[50];

    FILE *arq = fopen("experimentoRemocao.csv", "w");
    if (!arq) {
        perror("Erro ao abrir arquivo");
        return;
    }

    fprintf(arq, "instancia,percentual,qtdRotacoes,qtdMerges,altura,qtdBlocos\n");

    const int tamBase = 10000; // Tamanho base para os testes de remoção

    for (int i = 0; i < qtdPercentuais; i++) {
        // Criar árvore com 10.000 elementos
        arv234 *arvore = realizaTestesInsercao(NULL, "", tamBase, 0);
        if (!arvore) continue;

        sprintf(instancia, "remocao_%d", percentuais[i]);
        realizaTesteRemocao(arq, instancia, arvore->vetorOriginal, tamBase, percentuais[i], arvore);


        free(arvore->vetorOriginal);
    }

    fclose(arq);
}

// Função que executa todos os testes
void realizaTeste() {
    srand(time(NULL)); // Inicializar semente aleatória

    printf("Iniciando testes de insercao...\n");
    inicializaTesteInsercao();

    printf("Iniciando testes de remocao...\n");
    inicializaTesteRemocao();

    printf("Todos os testes foram concluidos!\n");
}