#include <stdio.h>

#define TAB_SIZE 10     // tamanho do tabuleiro (10x10)
#define NAV_SIZE 3      // tamanho dos navios (3)
#define SKILL_SIZE 5    // tamanho das matrizes de habilidade (5x5)
#define SHIP_VAL 3      // valor que representa navio no tabuleiro
#define SKILL_VAL 5     // valor que representa área de habilidade no tabuleiro
#define WATER_VAL 0     // valor que representa água

int main() {
    int tabuleiro[TAB_SIZE][TAB_SIZE];
    int i, j;

    // ---------- Inicializa o tabuleiro com água (0) ----------
    for (i = 0; i < TAB_SIZE; i++) {
        for (j = 0; j < TAB_SIZE; j++) {
            tabuleiro[i][j] = WATER_VAL;
        }
    }

    // ---------- Posiciona 4 navios (tamanho 3) ----------
    // Coordenadas escolhidas diretamente no código (lin, col)
    // Navio 1: horizontal
    int l1 = 3, c1 = 1;
    // Navio 2: vertical
    int l2 = 5, c2 = 6;
    // Navio 3: diagonal ↘
    int l3 = 0, c3 = 0;
    // Navio 4: diagonal ↙
    int l4 = 0, c4 = 9;

    // Função simples de validar e posicionar (valida limites e sobreposição)
    // 1) Navio horizontal (linha fixa, colunas consecutivas)
    if (c1 + NAV_SIZE > TAB_SIZE) {
        printf("Erro: Navio 1 fora dos limites\n");
        return 1;
    }
    for (j = 0; j < NAV_SIZE; j++) {
        if (tabuleiro[l1][c1 + j] != WATER_VAL) {
            printf("Erro: Sobreposição ao posicionar navio 1\n");
            return 1;
        }
    }
    for (j = 0; j < NAV_SIZE; j++) tabuleiro[l1][c1 + j] = SHIP_VAL;

    // 2) Navio vertical (coluna fixa, linhas consecutivas)
    if (l2 + NAV_SIZE > TAB_SIZE) {
        printf("Erro: Navio 2 fora dos limites\n");
        return 1;
    }
    for (i = 0; i < NAV_SIZE; i++) {
        if (tabuleiro[l2 + i][c2] != WATER_VAL) {
            printf("Erro: Sobreposição ao posicionar navio 2\n");
            return 1;
        }
    }
    for (i = 0; i < NAV_SIZE; i++) tabuleiro[l2 + i][c2] = SHIP_VAL;

    // 3) Navio diagonal ↘ (linha e coluna aumentam)
    if (l3 + NAV_SIZE > TAB_SIZE || c3 + NAV_SIZE > TAB_SIZE) {
        printf("Erro: Navio 3 fora dos limites\n");
        return 1;
    }
    for (i = 0; i < NAV_SIZE; i++) {
        if (tabuleiro[l3 + i][c3 + i] != WATER_VAL) {
            printf("Erro: Sobreposição ao posicionar navio 3\n");
            return 1;
        }
    }
    for (i = 0; i < NAV_SIZE; i++) tabuleiro[l3 + i][c3 + i] = SHIP_VAL;

    // 4) Navio diagonal ↙ (linha aumenta, coluna diminui)
    if (l4 + NAV_SIZE > TAB_SIZE || c4 - (NAV_SIZE - 1) < 0) {
        printf("Erro: Navio 4 fora dos limites\n");
        return 1;
    }
    for (i = 0; i < NAV_SIZE; i++) {
        if (tabuleiro[l4 + i][c4 - i] != WATER_VAL) {
            printf("Erro: Sobreposição ao posicionar navio 4\n");
            return 1;
        }
    }
    for (i = 0; i < NAV_SIZE; i++) tabuleiro[l4 + i][c4 - i] = SHIP_VAL;

    // ---------- Construção dinâmica das matrizes de habilidade (5x5) ----------
    // Vamos criar 3 matrizes de habilidade com valores 0/1:
    // cone[SKILL_SIZE][SKILL_SIZE] : cone apontando para baixo (↘ expansão)
    // cross[SKILL_SIZE][SKILL_SIZE] : cruz com origem no centro
    // octa[SKILL_SIZE][SKILL_SIZE] : losango (vista frontal de octaedro)

    int cone[SKILL_SIZE][SKILL_SIZE];
    int cross[SKILL_SIZE][SKILL_SIZE];
    int octa[SKILL_SIZE][SKILL_SIZE];

    // índice do centro (para SKILL_SIZE ímpar)
    int center = SKILL_SIZE / 2;

    // --- Preenche todas com zeros primeiro ---
    for (i = 0; i < SKILL_SIZE; i++) {
        for (j = 0; j < SKILL_SIZE; j++) {
            cone[i][j] = 0;
            cross[i][j] = 0;
            octa[i][j] = 0;
        }
    }

    // --- Monta o CONE (apontando para baixo).
    // Para cada linha r (de 0 no topo até SKILL_SIZE-1), a largura é 1 + 2*r
    // centrada na coluna 'center'. Usamos condicionais para marcar 1s.
    for (i = 0; i < SKILL_SIZE; i++) {
        int half_width = i; // expande 0,1,2,... nas linhas (para SKILL_SIZE=5)
        int left = center - half_width;
        int right = center + half_width;
        // garante limites dentro da matriz de habilidade
        if (left < 0) left = 0;
        if (right > SKILL_SIZE - 1) right = SKILL_SIZE - 1;
        for (j = left; j <= right; j++) {
            cone[i][j] = 1;
        }
    }

    // --- Monta a CRUZ: linha central e coluna central são 1
    for (i = 0; i < SKILL_SIZE; i++) {
        for (j = 0; j < SKILL_SIZE; j++) {
            if (i == center || j == center) {
                cross[i][j] = 1;
            }
        }
    }

    // --- Monta o OCTAEDRO (vista frontal -> losango / diamante)
    // condição: abs(i-center) + abs(j-center) <= center
    for (i = 0; i < SKILL_SIZE; i++) {
        for (j = 0; j < SKILL_SIZE; j++) {
            int dist = ( (i > center ? i - center : center - i) +
                         (j > center ? j - center : center - j) );
            if (dist <= center) {
                octa[i][j] = 1;
            } else {
                octa[i][j] = 0;
            }
        }
    }

    // ---------- Define pontos de origem (centro) de cada habilidade no tabuleiro ----------
    // Escolha direta no código:
    int originConeR = 1, originConeC = 2;   // onde o topo (linha 0 da skill) ficará centrado?
    // Para facilidade, vamos tratar a origem como o **centro** da matriz de habilidade.
    // Então origin é a posição do tabuleiro que corresponde ao center da skill.
    int originCrossR = 4, originCrossC = 4;
    int originOctaR  = 6, originOctaC  = 2;

    // ---------- Função de sobreposição: aplica uma skill ao tabuleiro ----------
    // Regras:
    // - Para cada célula da matriz de skill que tiver 1:
    //    calcula a posição correspondente no tabuleiro (com base no centro)
    // - Se estiver dentro dos limites do tabuleiro:
    //    e se tabuleiro[pos] == WATER_VAL -> marca com SKILL_VAL (5)
    //    se já houver navio (SHIP_VAL) -> *não sobrescreve*, mantém navio visível
    // Observação: podemos alterar este comportamento se quiser sobrescrever navios.

    // --- Aplica cone ---
    for (i = 0; i < SKILL_SIZE; i++) {
        for (j = 0; j < SKILL_SIZE; j++) {
            if (cone[i][j] == 1) {
                int boardR = originConeR + (i - center);
                int boardC = originConeC + (j - center);
                if (boardR >= 0 && boardR < TAB_SIZE && boardC >= 0 && boardC < TAB_SIZE) {
                    if (tabuleiro[boardR][boardC] == WATER_VAL) {
                        tabuleiro[boardR][boardC] = SKILL_VAL;
                    }
                    // se tiver navio (3), não sobrescreve - mantém 3
                }
            }
        }
    }

    // --- Aplica cross ---
    for (i = 0; i < SKILL_SIZE; i++) {
        for (j = 0; j < SKILL_SIZE; j++) {
            if (cross[i][j] == 1) {
                int boardR = originCrossR + (i - center);
                int boardC = originCrossC + (j - center);
                if (boardR >= 0 && boardR < TAB_SIZE && boardC >= 0 && boardC < TAB_SIZE) {
                    if (tabuleiro[boardR][boardC] == WATER_VAL) {
                        tabuleiro[boardR][boardC] = SKILL_VAL;
                    }
                }
            }
        }
    }

    // --- Aplica octaedro (diamond) ---
    for (i = 0; i < SKILL_SIZE; i++) {
        for (j = 0; j < SKILL_SIZE; j++) {
            if (octa[i][j] == 1) {
                int boardR = originOctaR + (i - center);
                int boardC = originOctaC + (j - center);
                if (boardR >= 0 && boardR < TAB_SIZE && boardC >= 0 && boardC < TAB_SIZE) {
                    if (tabuleiro[boardR][boardC] == WATER_VAL) {
                        tabuleiro[boardR][boardC] = SKILL_VAL;
                    }
                }
            }
        }
    }

    // ---------- Exibe o tabuleiro final ----------
    // Valores: 0 = água, 3 = navio, 5 = área de habilidade
    printf("\n=== TABULEIRO FINAL (0=agua, 3=navio, 5=area habilidade) ===\n\n");
    for (i = 0; i < TAB_SIZE; i++) {
        for (j = 0; j < TAB_SIZE; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    // ---------- (Opcional) Mostrar as matrizes de habilidade no console ----------
    printf("\nMatriz - CONE (1=afetado):\n");
    for (i = 0; i < SKILL_SIZE; i++) {
        for (j = 0; j < SKILL_SIZE; j++) printf("%d ", cone[i][j]);
        printf("\n");
    }

    printf("\nMatriz - CROSS (1=afetado):\n");
    for (i = 0; i < SKILL_SIZE; i++) {
        for (j = 0; j < SKILL_SIZE; j++) printf("%d ", cross[i][j]);
        printf("\n");
    }

    printf("\nMatriz - OCTAEDRO (1=afetado):\n");
    for (i = 0; i < SKILL_SIZE; i++) {
        for (j = 0; j < SKILL_SIZE; j++) printf("%d ", octa[i][j]);
        printf("\n");
    }

    return 0;
}
