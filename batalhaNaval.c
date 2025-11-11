#include <stdio.h>

int main() {
    // Tamanho fixo do tabuleiro (10x10)
    int tabuleiro[10][10];
    int i, j;

    // Inicializando o tabuleiro com 0 (água)
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // Tamanho fixo dos navios
    int tamanhoNavio = 3;

    // Coordenadas iniciais do primeiro navio (horizontal)
    // Exemplo: começa na linha 2, coluna 4
    int linhaNavio1 = 2;
    int colunaNavio1 = 4;

    // Coordenadas iniciais do segundo navio (vertical)
    // Exemplo: começa na linha 5, coluna 7
    int linhaNavio2 = 5;
    int colunaNavio2 = 7;

    // Validação simples para garantir que os navios caibam no tabuleiro
    // e não ultrapassem os limites
    if (colunaNavio1 + tamanhoNavio <= 10 && linhaNavio2 + tamanhoNavio <= 10) {

        // Posiciona o primeiro navio (horizontal)
        for (j = 0; j < tamanhoNavio; j++) {
            tabuleiro[linhaNavio1][colunaNavio1 + j] = 3;
        }

        // Posiciona o segundo navio (vertical)
        for (i = 0; i < tamanhoNavio; i++) {
            // Verifica se a posição já está ocupada
            if (tabuleiro[linhaNavio2 + i][colunaNavio2] == 0) {
                tabuleiro[linhaNavio2 + i][colunaNavio2] = 3;
            } else {
                printf("Erro: Os navios se sobrepõem!\n");
                return 1; // Encerra o programa com erro
            }
        }

        // Exibe o tabuleiro no console
        printf("\n=== TABULEIRO BATALHA NAVAL ===\n\n");
        for (i = 0; i < 10; i++) {
            for (j = 0; j < 10; j++) {
                printf("%d ", tabuleiro[i][j]);
            }
            printf("\n");
        }
    } else {
        printf("Erro: As coordenadas dos navios ultrapassam o limite do tabuleiro!\n");
    }

    return 0;
}
