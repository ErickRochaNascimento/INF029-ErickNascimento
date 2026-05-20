// Discente: Erick Rocha Luciano Nascimento | Matricula: 20252160017
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int numero_de_navios = 5;
int tamanho_navios[] = {4, 3, 1, 1, 1}; 

char tab1[10][10];
char tab2[10][10];
char tiros1[10][10]; 
char tiros2[10][10];

void inicializarMatrizes() {
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            tab1[i][j] = ' ';
            tab2[i][j] = ' ';
            tiros1[i][j] = ' ';
            tiros2[i][j] = ' ';
        }
    }
}

void imprimirTabuleiro(char tab[10][10], int esconderNavios) {
    printf("\n    0  1  2  3  4  5  6  7  8  9\n");
    for(int i = 0; i < 10; i++) {
        printf(" %c ", 'A' + i);
        for(int j = 0; j < 10; j++) {
            char celula = tab[i][j];
            if(esconderNavios && celula == 'N') {
                printf("[ ]"); 
            } else {
                printf("[%c]", celula);
            }
        }
        printf("\n");
    }
}

int posicionarNavio(char tab[10][10], int tamanho, int jogador) {
    char linhaChar;
    int linha, coluna;
    char direcao;

    printf("\nJogador %d, posicione um navio de tamanho %d.\n", jogador, tamanho);
    
    while(1) {
        printf("Digite a linha (A-J), coluna (0-9) e direcao (H/V) ex: A 5 H: ");
        scanf(" %c %d %c", &linhaChar, &coluna, &direcao);
        
        linha = toupper(linhaChar) - 'A';
        direcao = toupper(direcao);

        if(linha < 0 || linha > 9 || coluna < 0 || coluna > 9 || (direcao != 'H' && direcao != 'V')) {
            printf("Entrada invalida! Tente novamente.\n");
            continue;
        }

        if(direcao == 'H' && coluna + tamanho > 10) {
            printf("O navio ultrapassa o limite horizontal do tabuleiro.\n");
            continue;
        }
        if(direcao == 'V' && linha + tamanho > 10) {
            printf("O navio ultrapassa o limite vertical do tabuleiro.\n");
            continue;
        }

        int colisao = 0;
        for(int i = 0; i < tamanho; i++) {
            if(direcao == 'H' && tab[linha][coluna + i] == 'N') colisao = 1;
            if(direcao == 'V' && tab[linha + i][coluna] == 'N') colisao = 1;
        }

        if(colisao) {
            printf("Posicao ja ocupada por outro navio!\n");
            continue;
        }

        for(int i = 0; i < tamanho; i++) {
            if(direcao == 'H') tab[linha][coluna + i] = 'N';
            if(direcao == 'V') tab[linha + i][coluna] = 'N';
        }
        break;
    }
    return 1;
}

void setupJogador(char tab[10][10], int jogador) {
    printf("\n=== SETUP DO JOGADOR %d ===\n", jogador);
    for(int i = 0; i < numero_de_navios; i++) {
        imprimirTabuleiro(tab, 0);
        posicionarNavio(tab, tamanho_navios[i], jogador);
    }
    imprimirTabuleiro(tab, 0);
    printf("\nSetup concluido. Pressione Enter para limpar a tela...");
    getchar(); getchar(); 
    for(int i=0; i<50; i++) printf("\n");
}

int verificarVitoria(char tab[10][10]) {
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            if(tab[i][j] == 'N') return 0; 
        }
    }
    return 1;
}

int main() {
    inicializarMatrizes();
    
    setupJogador(tab1, 1);
    setupJogador(tab2, 2);

    int turno = 1;
    int fimDeJogo = 0;

    while(!fimDeJogo) {
        printf("\n===================================\n");
        printf("Vez do Jogador %d\n", turno);
        
        char (*meuTab)[10] = (turno == 1) ? tab1 : tab2;
        char (*tabOponente)[10] = (turno == 1) ? tab2 : tab1;
        char (*meusTiros)[10] = (turno == 1) ? tiros1 : tiros2;

        printf("\n--- SEU TABULEIRO ---\n");
        imprimirTabuleiro(meuTab, 0);
        
        printf("\n--- TABULEIRO DO OPONENTE (SEUS TIROS) ---\n");
        imprimirTabuleiro(meusTiros, 1);

        int jogadaValida = 0;
        while(!jogadaValida) {
            char lChar;
            int col;
            printf("\nInforme a coordenada para atirar (ex: C 4): ");
            scanf(" %c %d", &lChar, &col);
            
            int lin = toupper(lChar) - 'A';
            
            if(lin < 0 || lin > 9 || col < 0 || col > 9) {
                printf("Coordenada fora do mapa!\n");
                continue;
            }

            if(meusTiros[lin][col] != ' ') {
                printf("Voce ja atirou nessa posicao!\n");
                continue;
            }

            if(tabOponente[lin][col] == 'N') {
                printf("=> TIRO CERTEIRO! Voce acertou um navio!\n");
                tabOponente[lin][col] = '0'; 
                meusTiros[lin][col] = '0';
            } else {
                printf("=> AGUA! Tiro invalido (erro).\n");
                tabOponente[lin][col] = 'X'; 
                meusTiros[lin][col] = 'X';
            }
            jogadaValida = 1;
        }

        if(verificarVitoria(tabOponente)) {
            printf("\nPARABENS! O Jogador %d afundou toda a frota inimiga e VENCEU!\n", turno);
            fimDeJogo = 1;
        } else {
            turno = (turno == 1) ? 2 : 1;
        }
    }

    return 0;
}