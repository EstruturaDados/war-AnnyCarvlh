#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[30];
    char cor[15];
    int tropas;
} Territorio;

void limparEnter(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') str[len - 1] = '\0';
}

void mostrarMapa(Territorio *territorios, int n) {
    printf("\n=== Estado Atual do Mapa ===\n");
    for (int i = 0; i < n; i++) {
        printf("%d - %s | Cor: %s | Tropas: %d\n", 
               i + 1, territorios[i].nome, territorios[i].cor, territorios[i].tropas);
    }
}

// Função que simula batalha entre dois territórios
void atacar(Territorio *atacante, Territorio *defensor) {
    int dadoA = rand() % 6 + 1;
    int dadoD = rand() % 6 + 1;

    printf("\nAtaque de %s (%s) contra %s (%s)!\n",
           atacante->nome, atacante->cor,
           defensor->nome, defensor->cor);

    printf("Dado atacante: %d | Dado defensor: %d\n", dadoA, dadoD);

    if (dadoA >= dadoD) {
        defensor->tropas--;
        printf("%s perdeu 1 tropa!\n", defensor->nome);

        if (defensor->tropas <= 0) {
            printf("%s foi conquistado por %s!\n", defensor->nome, atacante->cor);
            defensor->tropas = atacante->tropas / 2;  // transfere parte das tropas
            strcpy(defensor->cor, atacante->cor);     // muda cor do exército
        }
    } else {
        atacante->tropas--;
        printf("%s perdeu 1 tropa!\n", atacante->nome);
    }
}

int main() {
    srand(time(NULL));
    int n = 5;
    Territorio *territorios = calloc(n, sizeof(Territorio));

    // Cadastro inicial
    for (int i = 0; i < n; i++) {
        printf("\nCadastro do território %d:\n", i + 1);
        printf("Nome: ");
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        limparEnter(territorios[i].nome);

        printf("Cor: ");
        fgets(territorios[i].cor, sizeof(territorios[i].cor), stdin);
        limparEnter(territorios[i].cor);

        printf("Tropas: ");
        scanf("%d", &territorios[i].tropas);
        getchar();
    }

    // Loop de batalhas
    int atacante, defensor;
    do {
        mostrarMapa(territorios, n);

        printf("\nEscolha atacante (1-%d, 0 para sair): ", n);
        scanf("%d", &atacante);
        if (atacante == 0) break;

        printf("Escolha defensor (1-%d): ", n);
        scanf("%d", &defensor);

        if (atacante < 1 || atacante > n || defensor < 1 || defensor > n) {
            printf("⚠️ Índice inválido!\n");
            continue;
        }

        if (atacante == defensor) {
            printf("⚠️ Um território não pode atacar a si mesmo!\n");
            continue;
        }

        atacar(&territorios[atacante - 1], &territorios[defensor - 1]);

    } while (1);

    // Mostrar o resultado final
    printf("\n=== Fim do Jogo ===\n");
    mostrarMapa(territorios, n);

    free(territorios);
    return 0;
}

