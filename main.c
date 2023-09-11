#include <stdio.h>

int main() {
    FILE *entrada = fopen("DadosEntrada.csv", "r");
    FILE *saida = fopen("SituacaoFinal.csv", "w");

    if (entrada == NULL || saida == NULL) {
        perror("Erro ao abrir arquivo");
        return 1;
    }

    char linha[1024];
    fprintf(saida, "Nome,Media,Situacao\n"); // Cabeçalho do arquivo de saída

    // Ignorar a primeira linha (cabeçalho)
    if (fgets(linha, sizeof(linha), entrada) == NULL) {
        perror("Erro ao ler cabeçalho");
        return 1;
    }

    while (fgets(linha, sizeof(linha), entrada) != NULL) {
        char nome[100];
        double nota1, nota2;

        if (sscanf(linha, "%99[^,],%*[^,],%*[^,],%lf,%lf", nome, &nota1, &nota2) == 3) {
            double media = (nota1 + nota2) / 2.0;
            const char *situacao = (media >= 7.0) ? "APROVADO" : "REPROVADO";
            fprintf(saida, "%s,%.2lf,%s\n", nome, media, situacao);
        }
    }

    fclose(entrada);
    fclose(saida);

    printf("Arquivo SituacaoFinal.csv criado com sucesso!\n");

    return 0;
}
