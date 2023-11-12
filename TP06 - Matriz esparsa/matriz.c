#include "matriz.h"
#include <stdlib.h>

Matriz inicializaMatriz(int nlin, int ncol) {
    Matriz matriz;
    matriz.nlin = nlin;
    matriz.ncol = ncol;
    matriz.elementos = (Celula **)malloc(nlin * sizeof(Celula *));

    for (int i = 0; i < nlin; i++) {
        matriz.elementos[i] = NULL;
    }

    return matriz;
}

void insereElemento(Matriz *matriz, int linha, int coluna, float valor) {
    Celula *novaCelula = (Celula *)malloc(sizeof(Celula));
    novaCelula->coluna = coluna;
    novaCelula->valor = valor;
    novaCelula->prox = matriz->elementos[linha];
    matriz->elementos[linha] = novaCelula;
}

void imprimeMatriz(Matriz A) {
    for (int i = 0; i < A.nlin; i++) {
        Celula *atual = A.elementos[i];
        printf("Linha %d: ", i + 1);

        while (atual != NULL) {
            printf("(%d, %.2f) ", atual->coluna + 1, atual->valor);
            atual = atual->prox;
        }

        printf("\n");
    }
}

Matriz leMatriz(FILE *arquivo) {
    int nlin, ncol;

    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo.\n");
        exit(EXIT_FAILURE);
    }

    if (fscanf(arquivo, "%d %d", &nlin, &ncol) != 2) {
        fprintf(stderr, "Erro ao ler as dimensões da matriz do arquivo.\n");
        exit(EXIT_FAILURE);
    }

    if (nlin <= 0 || ncol <= 0) {
        fprintf(stderr, "Dimensões inválidas da matriz.\n");
        exit(EXIT_FAILURE);
    }

    Matriz matriz = inicializaMatriz(nlin, ncol);

    int i, j;
    float valor;

    while (fscanf(arquivo, "%d %d %f", &i, &j, &valor) == 3) {
        if (i < 1 || i > nlin || j < 1 || j > ncol) {
            fprintf(stderr, "Coordenadas fora dos limites da matriz.\n");
            exit(EXIT_FAILURE);
        }

        insereElemento(&matriz, i - 1, j - 1, valor);
    }

    if (!feof(arquivo)) {
        fprintf(stderr, "Erro ao ler os elementos da matriz do arquivo.\n");
        exit(EXIT_FAILURE);
    }

    return matriz;
}

Matriz multiplicaMatrizes(Matriz A, Matriz B) {
    if (A.ncol != B.nlin) {
        fprintf(stderr, "Número de colunas de A não é igual ao número de linhas de B.\n");
        exit(EXIT_FAILURE);
    }

    Matriz resultado = inicializaMatriz(A.nlin, B.ncol);

    for (int i = 0; i < A.nlin; i++) {
        for (int j = 0; j < B.ncol; j++) {
            float soma = 0.0;

            Celula *atualA = A.elementos[i];
            Celula *atualB = B.elementos[j];

            while (atualA != NULL && atualB != NULL) {
                if (atualA->coluna == atualB->coluna) {
                    soma += atualA->valor * atualB->valor;
                    atualA = atualA->prox;
                    atualB = atualB->prox;
                } else if (atualA->coluna < atualB->coluna) {
                    atualA = atualA->prox;
                } else {
                    atualB = atualB->prox;
                }
            }

            if (soma != 0.0) {
                insereElemento(&resultado, i, j, soma);
            }
        }
    }

    return resultado;
}

void liberaMatriz(Matriz *matriz) {
    for (int i = 0; i < matriz->nlin; i++) {
        Celula *atual = matriz->elementos[i];
        while (atual != NULL) {
            Celula *prox = atual->prox;
            free(atual);
            atual = prox;
        }
    }
    free(matriz->elementos);
}
