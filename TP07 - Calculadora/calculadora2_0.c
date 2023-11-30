#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct no {
    float valor;
    struct no *proximo;
} No;

No *empilhar(No *pilha, float num) {
    No *novo = malloc(sizeof(No));

    if (novo) {
        novo->valor = num;
        novo->proximo = pilha;
        return novo;
    } else {
        printf("\tErro ao alocar memoria!\n");
        exit(EXIT_FAILURE);
    }
}

No *desempilhar(No **pilha) {
    No *remover = NULL;

    if (*pilha) {
        remover = *pilha;
        *pilha = remover->proximo;
    } else {
        printf("\tPilha vazia\n");
        exit(EXIT_FAILURE);
    }
    return remover;
}

float operacao(float a, float b, char x) {
    switch (x) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '/':
            return a / b;
        case '*':
            return a * b;
        case '^':
            return pow(b, a);
        case 'l': // log
            return log10(a);
        case 's': // sin
            return sin(a);
        case 'c': // cos
            return cos(a);
        case 't': // tan
            return tan(a);
        default:
            return 0.0;
    }
}

float resolver_expressao(char x[]) {
    char *pt;
    float num;
    No *n1, *pilha = NULL;

    pt = strtok(x, " ");
    while (pt) {
        if (pt[0] == '+' || pt[0] == '-' || pt[0] == '/' || pt[0] == '*' || pt[0] == '^' ||
            (pt[0] == 'l' && pt[1] == 'o' && pt[2] == 'g') ||
            (pt[0] == 's' && pt[1] == 'e' && pt[2] == 'n') ||
            (pt[0] == 'c' && pt[1] == 'o' && pt[2] == 's') ||
            (pt[0] == 't' && pt[1] == 'a' && pt[2] == 'n')) {
            if (pilha == NULL) {
                printf("\tErro: operador sem operandos suficientes.\n");
                exit(EXIT_FAILURE);
            }
            n1 = desempilhar(&pilha);

            // Se o operador for log, sen, cos ou tan, eles esperam apenas um operando
            if ((pt[0] == 'l' && pt[1] == 'o' && pt[2] == 'g') || 
                (pt[0] == 's' && pt[1] == 'e' && pt[2] == 'n') ||
                (pt[0] == 'c' && pt[1] == 'o' && pt[2] == 's') ||
                (pt[0] == 't' && pt[1] == 'a' && pt[2] == 'n')) {
                num = operacao(n1->valor, 0, pt[0]);
            } else {
                // Para outros operadores, desempilhar outro operando
                if (pilha == NULL) {
                    printf("\tErro: operador sem operandos suficientes.\n");
                    exit(EXIT_FAILURE);
                }
                No *n2 = desempilhar(&pilha);
                num = operacao(n2->valor, n1->valor, pt[0]);
                free(n2);
            }

            pilha = empilhar(pilha, num);
            free(n1);
        } else {
            num = strtof(pt, NULL);
            pilha = empilhar(pilha, num);
        }
        pt = strtok(NULL, " ");
    }
    if (pilha == NULL || pilha->proximo != NULL) {
        printf("\tErro: expressao mal formada.\n");
        exit(EXIT_FAILURE);
    }
    n1 = desempilhar(&pilha);
    num = n1->valor;
    free(n1);
    return num;
}

int main() {
    char exp[50];

    printf("Digite a expressao que deseja calcular: ");
    fgets(exp, sizeof(exp), stdin);
    exp[strcspn(exp, "\n")] = '\0';  // Remover a quebra de linha do final

    printf("Resultado de %s: %.2f\n", exp, resolver_expressao(exp));
    return 0;
}
