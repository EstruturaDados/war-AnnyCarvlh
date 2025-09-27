#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura de território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Função de ataque
void atacar(Territorio* atacante, Territorio* defensor) {
    if (atacante->tropas <= 1) {
        printf("O atacante precisa ter mais de 1 tropa para atacar.\n");
        return;
    }

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("%s ataca %s! (Atacante tirou %d, Defensor tirou %d)\n",
           atacante->nome, defensor->nome, dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("O atacante venceu a batalha!\n");
        defensor->tropas -= 1;
        if (defensor->tropas <= 0) {
            printf("%s foi conquistado!\n", defensor->nome);
            strcpy(defensor->cor, atacante->cor);
            defensor->tropas = atacante->tropas / 2;
            atacante->tropas -= defensor->tropas;
        }
    } else {
        printf("O defensor resistiu!\n");
        atacante->tropas -= 1;
    }
}

// Exibir o mapa (territórios numerados de 1 a 5)
void exibirMapa(Territorio* mapa, int tamanho) {
    printf("\n===== MAPA ATUAL =====\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%d) %s | Cor: %s | Tropas: %d\n",
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Verificar missão (simples — cada missão tem sua lógica inicial)
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {
    int conquistados = 0;
    int tropaTotal = 0;
    int territoriosVermelhos = 0;

    for (int i = 0; i < tamanho; i++) {
        if (strcmp(mapa[i].cor, "azul") == 0) {
            conquistados++;
            tropaTotal += mapa[i].tropas;
        }
        if (strcmp(mapa[i].cor, "vermelha") == 0) {
            territoriosVermelhos++;
        }
    }

    if (strcmp(missao, "Conquistar 3 territorios.") == 0 && conquistados >= 3) return 1;
    if (strcmp(missao, "Conquistar todos os territorios.") == 0 && conquistados == tamanho) return 1;
    if (strcmp(missao, "Ter pelo menos 10 tropas acumuladas.") == 0 && tropaTotal >= 10) return 1;
    if (strcmp(missao, "Eliminar todos os territorios vermelhos.") == 0 && territoriosVermelhos == 0) return 1;
    if (strcmp(missao, "Controlar exatamente 2 territorios.") == 0 && conquistados == 2) return 1;

    return 0;
}

int main() {
    srand(time(NULL));

    int n = 5;
    Territorio* mapa = (Territorio*) malloc(n * sizeof(Territorio));

    // Entrada personalizada dos territórios
    printf("=== Cadastro dos Territorios ===\n");
    for (int i = 0; i < n; i++) {
        printf("\nTerritorio %d:\n", i + 1);
        printf("Nome: ");
        scanf(" %[^\n]", mapa[i].nome);
        printf("Cor: ");
        scanf(" %[^\n]", mapa[i].cor);
        printf("Tropas: ");
        scanf("%d", &mapa[i].tropas);
    }

    // Vetor de missões
    char* missoes[5] = {
        "Conquistar 3 territorios.",
        "Conquistar todos os territorios.",
        "Ter pelo menos 10 tropas acumuladas.",
        "Eliminar todos os territorios vermelhos.",
        "Controlar exatamente 2 territorios."
    };

    // Sorteio da missão
    char* missao = (char*) malloc(100 * sizeof(char));
    strcpy(missao, missoes[rand() % 5]);

    printf("\n=== SUA MISSAO ===\n%s\n", missao);

    int atacante, defensor;

    // Loop de jogadas
    while (1) {
        exibirMapa(mapa, n);

        printf("\nEscolha atacante (1-%d, 0 para sair): ", n);
        scanf("%d", &atacante);
        if (atacante == 0) break;
        atacante--;

        printf("Escolha defensor (1-%d): ", n);
        scanf("%d", &defensor);
        defensor--;

        if (atacante < 0 || atacante >= n || defensor < 0 || defensor >= n) {
            printf("Índices inválidos.\n");
            continue;
        }
        if (strcmp(mapa[atacante].cor, mapa[defensor].cor) == 0) {
            printf("Não é possível atacar territórios da mesma cor.\n");
            continue;
        }

        atacar(&mapa[atacante], &mapa[defensor]);

        if (verificarMissao(missao, mapa, n)) {
            printf("\n=== Missão cumprida! Você venceu! ===\n");
            break;
        }
    }

    free(mapa);
    free(missao);
    return 0;
}



