#ifndef MATRIZ_H
#define MATRIZ_H

#include <stdio.h>

typedef struct Celula {
    int coluna;
    float valor;
    struct Celula *prox;
} Celula;

typedef struct {
    int nlin, ncol;
    Celula **elementos;
} Matriz;

Matriz inicializaMatriz(int nlin, int ncol);
void insereElemento(Matriz *matriz, int linha, int coluna, float valor);
void imprimeMatriz(Matriz A);
Matriz leMatriz(FILE *arquivo);
Matriz multiplicaMatrizes(Matriz A, Matriz B);
void liberaMatriz(Matriz *matriz);

#endif // MATRIZ_H
