#include <stdio.h>

#define TAM 10         // tamanho do tabuleiro (10x10)
#define TAM_NAVIO 3    // tamanho fixo dos navios

int main() {
    int tabuleiro[TAM][TAM];
    int i, j;

    // Inicializa o tabuleiro com 0 (água)
    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // =========================
    // Coordenadas dos 4 navios
    // (definidas diretamente no código)
    // =========================

    // 1º navio - horizontal (sem sobreposição agora)
    int linhaNavio1 = 3;
    int colunaNavio1 = 1;

    // 2º navio - vertical
    int linhaNavio2 = 5;
    int colunaNavio2 = 6;

    // 3º navio - diagonal ↘ (linha e coluna aumentam)
    int linhaNavio3 = 0;
    int colunaNavio3 = 0;

    // 4º navio - diagonal ↙ (linha aumenta, coluna diminui)
    int linhaNavio4 = 0;
    int colunaNavio4 = 9;

    // =========================
    // FUNÇÃO SIMPLIFICADA DE VALIDAÇÃO E POSICIONAMENTO
    // Para cada navio: 1) validar limites 2) validar sobreposição 3) posicionar
    // =========================

    // --- 1º NAVIO (Horizontal) ---
    // Valida limites
    if (colunaNavio1 + TAM_NAVIO > TAM) {
        printf("Erro: Navio 1 (horizontal) fora dos limites!\n");
        return 1;
    }
    // Valida sobreposição
    for (j = 0; j < TAM_NAVIO; j++) {
        if (tabuleiro[linhaNavio1][colunaNavio1 + j] != 0) {
            printf("Erro: Sobreposição detectada no navio 1!\n");
            return 1;
        }
    }
    // Posiciona navio 1
    for (j = 0; j < TAM_NAVIO; j++) {
        tabuleiro[linhaNavio1][colunaNavio1 + j] = 3;
    }

    // --- 2º NAVIO (Vertical) ---
    if (linhaNavio2 + TAM_NAVIO > TAM) {
        printf("Erro: Navio 2 (vertical) fora dos limites!\n");
        return 1;
    }
    for (i = 0; i < TAM_NAVIO; i++) {
        if (tabuleiro[linhaNavio2 + i][colunaNavio2] != 0) {
            printf("Erro: Sobreposição detectada no navio 2!\n");
            return 1;
        }
    }
    for (i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linhaNavio2 + i][colunaNavio2] = 3;
    }

    // --- 3º NAVIO (Diagonal ↘) ---
    if (linhaNavio3 + TAM_NAVIO > TAM || colunaNavio3 + TAM_NAVIO > TAM) {
        printf("Erro: Navio 3 (diagonal ↘) fora dos limites!\n");
        return 1;
    }
    for (i = 0; i < TAM_NAVIO; i++) {
        if (tabuleiro[linhaNavio3 + i][colunaNavio3 + i] != 0) {
            printf("Erro: Sobreposição detectada no navio 3!\n");
            return 1;
        }
    }
    for (i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linhaNavio3 + i][colunaNavio3 + i] = 3;
    }

    // --- 4º NAVIO (Diagonal ↙) ---
    if (linhaNavio4 + TAM_NAVIO > TAM || colunaNavio4 - (TAM_NAVIO - 1) < 0) {
        printf("Erro: Navio 4 (diagonal ↙) fora dos limites!\n");
        return 1;
    }
    for (i = 0; i < TAM_NAVIO; i++) {
        if (tabuleiro[linhaNavio4 + i][colunaNavio4 - i] != 0) {
            printf("Erro: Sobreposição detectada no navio 4!\n");
            return 1;
        }
    }
    for (i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linhaNavio4 + i][colunaNavio4 - i] = 3;
    }

    // =========================
    // Exibe o tabuleiro
    // =========================
    printf("\n=== TABULEIRO BATALHA NAVAL - NIVEL AVENTUREIRO ===\n\n");
    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}
