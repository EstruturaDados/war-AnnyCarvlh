#include <stdio.h>
#include <string.h>

// Struct para representar um território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Função para remover quebra de linha do fgets
void limparEnter(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') str[len - 1] = '\0';
}

int main() {
    Territorio territorios[5];

    printf("=== Cadastro de Territórios ===\n");
    for (int i = 0; i < 5; i++) {
        printf("\nTerritório %d:\n", i + 1);

        printf("Nome: ");
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        limparEnter(territorios[i].nome);

        printf("Cor do Exército: ");
        fgets(territorios[i].cor, sizeof(territorios[i].cor), stdin);
        limparEnter(territorios[i].cor);

        printf("Número de tropas: ");
        scanf("%d", &territorios[i].tropas);
        getchar(); // limpar buffer
    }

    printf("\n=== Estado do Mapa ===\n");
    for (int i = 0; i < 5; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
    }
    return 0;
}
