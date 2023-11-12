#include <stdio.h>
#include <stdlib.h>

typedef struct Celula {
    int linha, coluna;
    float valor;
    struct Celula *prox;
} Celula;

typedef struct {
    int nlin, ncol;
    Celula **elementos;
} Matriz;

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
    novaCelula->linha = linha;
    novaCelula->coluna = coluna;
    novaCelula->valor = valor;
    novaCelula->prox = matriz->elementos[linha];
    matriz->elementos[linha] = novaCelula;
}

void imprimeMatriz(FILE *arquivo, Matriz A) {
    for (int i = 0; i < A.nlin; i++) {
        for (int j = 0; j < A.ncol; j++) {
            Celula *atual = A.elementos[i];
            while (atual != NULL) {
                if (atual->coluna == j) {
                    fprintf(arquivo, "%.2f\t", atual->valor);
                    break;
                }
                atual = atual->prox;
            }
            if (atual == NULL) {
                fprintf(arquivo, "0.00\t");
            }
        }
        fprintf(arquivo, "\n");
    }
}

Matriz leMatriz(FILE *arquivo) {
    int nlin, ncol;

    // Verifica se o arquivo foi aberto corretamente
    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo.\n");
        exit(EXIT_FAILURE);
    }

    // Tenta ler as dimensões da matriz
    if (fscanf(arquivo, "%d %d", &nlin, &ncol) != 2) {
        fprintf(stderr, "Erro ao ler as dimensões da matriz do arquivo.\n");
        exit(EXIT_FAILURE);
    }

    // Verifica se as dimensões são válidas
    if (nlin <= 0 || ncol <= 0) {
        fprintf(stderr, "Dimensões inválidas da matriz.\n");
        exit(EXIT_FAILURE);
    }

    Matriz matriz = inicializaMatriz(nlin, ncol);

    int i, j;
    float valor;

    while (fscanf(arquivo, "%d %d %f", &i, &j, &valor) == 3) {
        // Verifica se as coordenadas estão dentro dos limites
        if (i < 1 || i > nlin || j < 1 || j > ncol) {
            fprintf(stderr, "Coordenadas fora dos limites da matriz.\n");
            exit(EXIT_FAILURE);
        }

        insereElemento(&matriz, i - 1, j - 1, valor);
    }

    // Verifica se a leitura foi bem-sucedida ou se atingiu o final do arquivo
    if (!feof(arquivo)) {
        fprintf(stderr, "Erro ao ler os elementos da matriz do arquivo.\n");
        exit(EXIT_FAILURE);
    }

    return matriz;
}




Matriz somaMatrizes(Matriz A, Matriz B) {
    if (A.nlin != B.nlin || A.ncol != B.ncol) {
        fprintf(stderr, "As matrizes precisam ter as mesmas dimensões para a soma.\n");
        exit(EXIT_FAILURE);
    }

    Matriz resultado = inicializaMatriz(A.nlin, A.ncol);

    for (int i = 0; i < A.nlin; i++) {
        Celula *celulaA = A.elementos[i];
        Celula *celulaB = B.elementos[i];

        while (celulaA != NULL || celulaB != NULL) {
            int colunaA = (celulaA != NULL) ? celulaA->coluna : A.ncol;
            int colunaB = (celulaB != NULL) ? celulaB->coluna : B.ncol;

            if (colunaA == colunaB) {
                float soma = (celulaA != NULL ? celulaA->valor : 0) + (celulaB != NULL ? celulaB->valor : 0);
                insereElemento(&resultado, i, colunaA, soma);

                if (celulaA != NULL) celulaA = celulaA->prox;
                if (celulaB != NULL) celulaB = celulaB->prox;
            } else if (colunaA < colunaB) {
                insereElemento(&resultado, i, colunaA, celulaA->valor);
                celulaA = celulaA->prox;
            } else {
                insereElemento(&resultado, i, colunaB, celulaB->valor);
                celulaB = celulaB->prox;
            }
        }
    }

    return resultado;
}

void liberaMatriz(Matriz A) {
    for (int i = 0; i < A.nlin; i++) {
        Celula *atual = A.elementos[i];
        while (atual != NULL) {
            Celula *prox = atual->prox;
            free(atual);
            atual = prox;
        }
    }

    free(A.elementos);
}

int main(void) {
    FILE *arquivoA = fopen("matrizA.txt", "r");
    if (arquivoA == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo de matrizA.\n");
        return EXIT_FAILURE;
    }

    FILE *arquivoB = fopen("matrizB.txt", "r");
    if (arquivoB == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo de matrizB.\n");
        fclose(arquivoA);
        return EXIT_FAILURE;
    }

    Matriz A = leMatriz(arquivoA);
    fclose(arquivoA);

    printf("Matriz A lida:\n");
    imprimeMatriz(stdout, A);

    Matriz B = leMatriz(arquivoB);
    fclose(arquivoB);

    printf("\nMatriz B lida:\n");
    imprimeMatriz(stdout, B);

    Matriz C = somaMatrizes(A, B);
    printf("\nMatriz resultante da soma (C = A + B):\n");
    imprimeMatriz(stdout, C);

    // Adicione outros testes conforme necessário

    // Libera a memória alocada para as matrizes
    liberaMatriz(A);
    liberaMatriz(B);
    liberaMatriz(C);

    return 0;
}
