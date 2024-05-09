#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "tabuleiro.h"
#include "intelfpgaup/KEY.h"

#define MOUSEFILE "/dev/input/mice"

char alternaJogadores(int jogadas) {
    if (jogadas % 2 == 0) {
        return 'X';
    }
    return 'O';
}


// Limitando coordenadas entre 1 e 200
void limitarCursor(int *x, int *y) {
    if (*x <= 1) *x = 1;
    if (*y <= 1) *y = 1;
    if (*x >= 200) *x = 200;
    if (*y >= 200) *y = 200;
}

int determinarCasa(int x, int y) {
    int casa;

    if (x < 50) {
        casa = 1;
    } else if (x < 100) {
        casa = 2;
    } else {
        casa = 3;
    }

    if (y >= 50 && y < 100) {
        casa += 3;
    } else if (y >= 100) {
        casa += 6;
    }

    return casa;
}

int main() {

    int fd;
    int leftButton;
    signed char x_disp, y_disp;
    int x = 0, y = 0;
    char mouse_buffer[3];
    int casa = 0;
    char jogador = ' ';
    int jogadas = 0;
    int dataButton = 0b0;
    int executando = 1; // Flag para executar o jogo
    int controladorCliques = 0;

    fd = open(MOUSEFILE, O_RDONLY); // Abre arquivo do mouse
    KEY_open(); // Abre botões da placa

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


    
    printf("Clique no botão KEY0 para iniciar a partida\n");

    while (executando) {

        KEY_read(&dataButton);
//printf("%d", dataButton);
        // Se o botão KEY1 for pressionado, o jogo termina
        if (dataButton == 0b10) {
            printf("Saindo do jogo...");
            dataButton = 0;
            break;
        } // Se o botão KEY0 é pressionado, o jogo inicia
        else if (dataButton == 0b01) {
            controladorCliques = 1;
            imprimirTabuleiro(tabuleiro);
            printf("Jogadas: %d\n", jogadas);
        }sleep(1);
}
        while (controladorCliques) { // inicia a partida


            if (read(fd, &mouse_buffer, sizeof(mouse_buffer)) > 0) {
		
                system("clear");
                imprimirTabuleiro(tabuleiro);
                printf("Jogadas: %d\n\n", jogadas);

                x_disp = mouse_buffer[1];
                y_disp = mouse_buffer[2];
                leftButton = mouse_buffer[0] & 0x1;

                x += x_disp;
                y -= y_disp;

                limitarCursor(&x, &y);

                casa = determinarCasa(x, y);
                printf("Você está na casa %d\n", casa);

                printf("Vez do jogador %c\n\n", jogador);

                int i = posicoes[casa-1][0];
                int j = posicoes[casa-1][1];

               if (leftButton && jogadaValida(tabuleiro, i, j)) {
                    tabuleiro[i][j] = jogador;
                    jogadas++;
                }

                // Verifica vitória ou empate
                int vitoria = verificarVitoria(tabuleiro);
                int empate = verificarEmpate(tabuleiro, &jogadas);

                if (vitoria) {
                    system("clear");
                    imprimirTabuleiro(tabuleiro);
                    printf("%c Ganhou!\n", jogador);
dataButton = 0;   
vitoria = 0;
jogadas =0;
                    controladorCliques = 0;
                    
                    
                } else if (empate) {
                    system("clear");
                    imprimirTabuleiro(tabuleiro);

                    printf("Empate!\n");
dataButton = 0;
empate = 0;
   

                    controladorCliques = 0;
              }


                jogador = alternaJogadores(jogadas);
              usleep(2000); // Espera 2 ms antes de verificar novamente o mouse
           }
        }
    }

    KEY_close();
    close(fd);
    return 0;
}
