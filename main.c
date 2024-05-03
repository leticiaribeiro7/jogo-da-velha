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
    int i, j;
    int jogadas = 0;
    int ultimoEstadoBotao = 0;

    fd = open(MOUSEFILE, O_RDONLY); // abre arquivo do mouse
    KEY_open(); // abre botões

    if (fd == -1) {
        perror("Não é possível abrir o dispositivo do mouse");
        exit(EXIT_FAILURE);
    }

    char tabuleiro[3][3] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}
    };

    while (1) {
       
        if (read(fd, &mouse_buffer, sizeof(mouse_buffer)) > 0) {
            system("clear");
            imprimirTabuleiro(tabuleiro);

            x_disp = mouse_buffer[1];
            y_disp = mouse_buffer[2];
            leftButton = mouse_buffer[0] & 0x1;

            x += x_disp;
            y -= y_disp;

            // if (leftButton) { // Verifica se o bit 0 (botão esquerdo) está definido
            //     printf("Clicou em x=%d e y=%d\n", x, y);
            // }
            // printf("Botão: %d, Posição X: %d, Posição Y: %d\n", button, x, y);

            printf("Você está no quadrante %d\n", quadrante);

            jogador = alternaJogadores(leftButton, jogadas);    


            // atualiza quadrante e faz a jogada
            if (x < 50 ) {
                if (y < 50) {
                    quadrante = 1;
                    if (leftButton && jogadaValida(tabuleiro, 0, 0)) {
                        tabuleiro[0][0] = jogador;
                        jogadas++;
                    }
                } else if (y > 51 && y < 100) {
                    quadrante = 4;
                    if(leftButton && jogadaValida(tabuleiro, 1, 0)) {
                        tabuleiro[1][0] = jogador;
                        jogadas++;
                    }
                } else if (y > 101) {
                    quadrante = 7;
                    if(leftButton && jogadaValida(tabuleiro, 2, 0)) {
                        tabuleiro[2][0] = jogador;
                        jogadas++;
                    }
                }
            } else if (x > 51 && x < 100) {
                if (y < 50) {
                    quadrante = 2;
                    if(leftButton && jogadaValida(tabuleiro, 0, 1)) {
                        tabuleiro[0][1] = jogador;
                        jogadas++;
                    }
                } else if (y > 51 && y < 100) {
                    quadrante = 5;
                    if(leftButton && jogadaValida(tabuleiro, 1, 1)) {
                        tabuleiro[1][1] = jogador;
                        jogadas++;
                    }
                } else if (y > 101) {
                    quadrante = 8;
                    if(leftButton && jogadaValida(tabuleiro, 2, 1)) {
                        tabuleiro[2][1] = jogador;
                        jogadas++;
                    }
                }
            } else if (x > 101 && x < 200) {
                if(y < 50) {
                    quadrante = 3;
                    if (leftButton && jogadaValida(tabuleiro, 0, 2)) {
                        tabuleiro[0][2] = jogador;
                        jogadas++;
                    }

                } else if (y > 51 && y < 100) {
                    quadrante = 6;
                    if(leftButton && jogadaValida(tabuleiro, 1, 2)) {
                        tabuleiro[1][2] = jogador;
                        jogadas++;
                    }
                } else if (y > 101) {
                    quadrante = 9;
                    if(leftButton && jogadaValida(tabuleiro, 2, 2)) {
                        tabuleiro[2][2] = jogador;
                        jogadas++;
                    }
                }
            }
        }

        int vitoria = verificarVitoria(tabuleiro);
        int empate = verificarEmpate(tabuleiro);

        if (vitoria) {
            system("clear");
            imprimirTabuleiro(tabuleiro);
            printf("%c Ganhou!\n", jogador);
            break;
            
        } else if(empate && jogadas == 9) {
            printf("Empate\n");
        }

        printf("Jogadas: %d", jogadas);
        usleep(2000); // Espera 20ms antes de verificar novamente o mouse
    }

    close(fd);
    return 0;
}
