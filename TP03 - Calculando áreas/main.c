#include <stdio.h>
#include <stdlib.h>


typedef struct {
    float X;
    float Y;
} Ponto;


double calcularArea(FILE *arquivo) {
    int n; // Número de vértices
    fscanf(arquivo, "%d", &n);

   
    Ponto *vertices = (Ponto *)malloc(n * sizeof(Ponto));

  
    if (vertices == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }

   
    for (int i = 0; i < n; i++) {
        fscanf(arquivo, "%f %f", &vertices[i].X, &vertices[i].Y);
    }

    double area = 0.0;

    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n; // Próximo vértice
        area += (vertices[i].X * vertices[j].Y) - (vertices[j].X * vertices[i].Y);
    }

    area = 0.5 * abs(area); 

    // Liberar a memória alocada dinamicamente
    free(vertices);

    return area;
}

int main() {
    FILE *arquivo;


    char nomeArquivo[100];
    printf("Digite o nome do arquivo de entrada: ");
    scanf("%s", nomeArquivo);

    arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }


    double area = calcularArea(arquivo);


    printf("A área do polígono é %.2lf\n", area);

    fclose(arquivo);

    return 0;
}
