// Discente: Erick Rocha Luciano Nascimento | Matricula: 20252160017
#include <stdio.h>
#include <ctype.h>

char tabuleiro[3][3];

void inicializarTabuleiro() {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            tabuleiro[i][j] = ' ';
        }
    }
}

void imprimirTabuleiro() {
    printf("\n    1   2   3\n");
    for(int i = 0; i < 3; i++) {
        printf(" %c  ", 'A' + i);
        for(int j = 0; j < 3; j++) {
            printf(" %c ", tabuleiro[i][j]);
            if(j < 2) printf("|");
        }
        if(i < 2) printf("\n   ---|---|---\n");
    }
    printf("\n\n");
}

int verificarVitoria() {
    for(int i = 0; i < 3; i++) {
        if(tabuleiro[i][0] != ' ' && tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][1] == tabuleiro[i][2]) return 1;
        if(tabuleiro[0][i] != ' ' && tabuleiro[0][i] == tabuleiro[1][i] && tabuleiro[1][i] == tabuleiro[2][i]) return 1;
    }
    if(tabuleiro[0][0] != ' ' && tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2]) return 1;
    if(tabuleiro[0][2] != ' ' && tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][0]) return 1;
    
    return 0;
}

int verificarEmpate() {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(tabuleiro[i][j] == ' ') return 0; 
        }
    }
    return 1;
}

int main() {
    int jogadorAtual = 1;
    char marca;
    char jogada[5];
    int linha, coluna;
    int fimDeJogo = 0;

    inicializarTabuleiro();

    printf("=== JOGO DA VELHA ===\n");

    while(!fimDeJogo) {
        imprimirTabuleiro();
        marca = (jogadorAtual == 1) ? 'X' : '0';
        
        int jogadaValida = 0;
        while(!jogadaValida) {
            printf("Jogador %d, informe sua jogada (ex: B3): ", jogadorAtual);
            scanf("%s", jogada);

            char l = toupper(jogada[0]);
            char c = jogada[1];

            if(l >= 'A' && l <= 'C' && c >= '1' && c <= '3') {
                linha = l - 'A';
                coluna = c - '1';

                if(tabuleiro[linha][coluna] == ' ') {
                    tabuleiro[linha][coluna] = marca;
                    jogadaValida = 1;
                } else {
                    printf("Posicao ja ocupada! Tente novamente.\n");
                }
            } else {
                printf("Coordenada invalida! Use letras de A-C e numeros de 1-3.\n");
            }
        }

        if(verificarVitoria()) {
            imprimirTabuleiro();
            printf("PARABENS! O Jogador %d venceu!\n", jogadorAtual);
            fimDeJogo = 1;
        } else if(verificarEmpate()) {
            imprimirTabuleiro();
            printf("O jogo terminou empatado (VELHA)!\n");
            fimDeJogo = 1;
        } else {
            jogadorAtual = (jogadorAtual == 1) ? 2 : 1;
        }
    }

    return 0;
}