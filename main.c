#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include "tabuleiro.h"

#define MOUSEFILE "/dev/input/mice"

char alternaJogadores(int leftButton, int jogadas) {
    if (jogadas % 2 == 0) {
        return 'X';
    }
    return 'O';
}


int jogadaValida(char tabuleiro[3][3], int i, int j) {
    if (tabuleiro[i][j] == 'X' || tabuleiro[i][j] == 'O') {
        return 0;
    }
    return 1;
}

// Limitando coordenadas entre 1 e 200
void limitarCursor(int *x, int *y) {
    if (*x <= 1) *x = 1;
    if (*y <= 1) *y = 1;
    if (*x >= 200) *x = 200;
    if (*y >= 200) *y = 200;
}

int determinarQuadrante(int x, int y) {
    int quadrante;

    if (x < 50) {
        quadrante = 1;
    } else if (x < 100) {
        quadrante = 2;
    } else {
        quadrante = 3;
    }

    if (y >= 50 && y < 100) {
        quadrante += 3;
    } else if (y >= 100) {
        quadrante += 6;
    }

    return quadrante;
}


int main() {
    int fd;
    char button;
    int leftButton;
    signed char x_disp, y_disp;
    int x = 0, y = 0; // Inicialize x e y com zero
    char mouse_buffer[3]; 
    int quadrante = 0;
    char jogador = ' ';
    int jogadas = 0;
    
    

    fd = open(MOUSEFILE, O_RDONLY); // abre arquivo do mouse
    //KEY_open(); // abre botões

    if (fd == -1) {
        perror("Não é possível abrir o dispositivo do mouse");
        exit(EXIT_FAILURE);
    }

    char tabuleiro[3][3] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}
    };

    // Mapeamento do quadrante para as posições do tabuleiro
    int posicoes[9][2] = {
        {0, 0}, {0, 1}, {0, 2},
        {1, 0}, {1, 1}, {1, 2},
        {2, 0}, {2, 1}, {2, 2}
    };

    while (1) {
       
        if (read(fd, &mouse_buffer, sizeof(mouse_buffer)) > 0) {
            
            system("clear");
            printf("===== JOGO DA VELHA =====\n\n");
            printf("Jogadas: %d\n", jogadas);
            imprimirTabuleiro(tabuleiro);

            x_disp = mouse_buffer[1];
            y_disp = mouse_buffer[2];
            leftButton = mouse_buffer[0] & 0x1;

            x += x_disp;
            y -= y_disp;

            // if (leftButton) { // Verifica se o bit 0 (botão esquerdo) está definido
            //     printf("Clicou em x=%d e y=%d\n", x, y);
            // }
            //printf("Botão: %d, Posição X: %d, Posição Y: %d\n", button, x, y);

            printf("Vez do jogador %c\n\n", jogador);
            
            quadrante = determinarQuadrante(x, y);
            printf("Você está no quadrante %d\n", quadrante);


            int i = posicoes[quadrante-1][0];
            int j = posicoes[quadrante-1][1];

            if (leftButton && jogadaValida(tabuleiro, i, j)) {
                tabuleiro[i][j] = jogador;
                jogadas++;
            }
        }

        limitarCursor(&x, &y);

        int vitoria = verificarVitoria(tabuleiro);
        int empate = verificarEmpate(tabuleiro);

        if (vitoria) {
            system("clear");
            imprimirTabuleiro(tabuleiro);
            printf("%c Ganhou!\n", jogador);
            break;
            
        } else if (empate && jogadas == 9) {
            system("clear");
            imprimirTabuleiro(tabuleiro);
            printf("Empate!\n");
            break;
        }

        jogador = alternaJogadores(leftButton, jogadas); 

        usleep(2000); // Espera 20ms antes de verificar novamente o mouse
    }


    close(fd);
    return 0;
}
