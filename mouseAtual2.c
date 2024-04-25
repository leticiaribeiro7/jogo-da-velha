#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include "tabuleiro.h"

#define MOUSEFILE "/dev/input/mice"


int main() {
    int fd;
    char button;
    int leftButton;
    signed char x_disp, y_disp;
    int x = 0, y = 0; // Inicialize x e y com zero
    char mouse_buffer[3]; 
    int quadrante;
    char jogador = 'X';

    fd = open(MOUSEFILE, O_RDONLY);

    if (fd == -1) {
        perror("Não é possível abrir o dispositivo do mouse");
        exit(EXIT_FAILURE);
    }

    char tabuleiro[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    while (1) {
       // imprimirTabuleiro(tabuleiro);

        if (read(fd, &mouse_buffer, sizeof(mouse_buffer)) > 0) {
            imprimirTabuleiro(tabuleiro);

            button = mouse_buffer[0] & 0x07; // Extrai os bits do botão do buffer
            x_disp = mouse_buffer[1];
            y_disp = mouse_buffer[2];
            leftButton = button & 0x01;

            x += x_disp;
            y -= y_disp;

            if (leftButton) { // Verifica se o bit 0 (botão esquerdo) está definido
                printf("Clicou em x=%d e y=%d\n", x, y);
            }
            printf("Botão: %d, Posição X: %d, Posição Y: %d\n", button, x, y);

            if (quadrante == 0) {
                printf("Você está fora do tabuleiro!");
            } else {
                printf("Você está no quadrante %d", quadrante);
            }

            // primeira coluna
            if (x > 0 && x < 50 ) {
                if (y > 0 && y < 50) {
                    quadrante = 1;
                } else if (y > 51 && y < 100) {
                    quadrante = 4;
                } else if (y > 101 && y < 150) {
                    quadrante = 7;
                }
            }

            jogador = (jogador == 'X') ? 'O' : 'X'; // alterna jogadores

            if (leftButton) { // col lin
                tabuleiro[0][quadrante-1] = jogador; // so funciona pra col 0
            }
        }

        usleep(10000); // Espera 10ms antes de verificar novamente o mouse
    }

    close(fd);
    return 0;
}
