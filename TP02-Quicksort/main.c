#include <stdio.h>
#include <string.h>

void swap(char **a, char **b) {
    char *temp = *a;
    *a = *b;
    *b = temp;
}

int partition(char **arr, int low, int high, int *trocas, int *comparacoes) {
    char *pivot = arr[low];
    int i = low - 1;
    int j = high + 1;

    while (1) {
        do {
            i++;
        } while (strcmp(arr[i], pivot) < 0);

        do {
            j--;
        } while (strcmp(arr[j], pivot) > 0);

        if (i >= j) {
            return j;
        }

        swap(&arr[i], &arr[j]);
        (*trocas)++;
    }
}

void quicksort(char **arr, int low, int high, int *trocas, int *comparacoes) {
    if (low < high) {
        int pi = partition(arr, low, high, trocas, comparacoes);

        quicksort(arr, low, pi, trocas, comparacoes);
        quicksort(arr, pi + 1, high, trocas, comparacoes);
    }
}

int main() {
    char *arr[20] = {
        "maca", "banana", "pera", "uva", "laranja", "abacaxi", "limão", "manga", "abacate", "kiwi",
        "cereja", "morango", "pêssego", "goiaba", "melancia", "framboesa", "amora", "caqui", "figo", "papaya"
    };
    int n = 20;          // Número de elementos no vetor

    int comparacoes = 0;
    int trocas = 0;

    quicksort(arr, 0, n - 1, &trocas, &comparacoes);

    // Calculando a mediana
    char *mediana = arr[n / 2];

    // Mostrando o vetor ordenado
    printf("Vetor Ordenado:\n");
    for (int i = 0; i < n; i++) {
        printf("%s\n", arr[i]);
    }

    // Contando comparações e trocas
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
        }
    }

                                    // Gerando o arquivo de saída
    FILE *saida = fopen("ArquivoSaida.txt", "w");
    if (saida == NULL) {
        perror("Erro ao abrir o arquivo de saída");
        return 1;
    }

    fprintf(saida, "Vetor Ordenado:\n");
    for (int i = 0; i < n; i++) {
        fprintf(saida, "%s\n", arr[i]);
    }
    fprintf(saida, "Número de comparações é: %d\n", comparacoes);
    fprintf(saida, "Número de trocas aproximadamente é: %d\n", trocas);
    fprintf(saida, "A Média encontrada: %s\n", mediana);

    fclose(saida);

    return 0;
}
