#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
//#include <termios.h>
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
    int leftButton;
    signed char x_disp, y_disp;
    int x = 0, y = 0; // Inicialize x e y com zero
    char mouse_buffer[3];
    int quadrante = 0;
    char jogador = ' ';
    int jogadas = 0;
    int dataButton = 0b0;
    //int jogoIniciado = 0; // Flag para controlar se o jogo já foi iniciado
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

    //KEY_read(&dataButton);
       // printf("botao: %d", dataButton);

    
    printf("Clique no botão KEY0 para iniciar a partida\n");

    while (executando) {
        KEY_read(&dataButton);
        printf("botao: %d", dataButton);

        if (dataButton == 0b10) {
            printf("Saindo do jogo...");
            dataButton = 0;
            break;
        } 
        else if (dataButton == 0b01) {
            controladorCliques = 1;
            printf("===== JOGO =====\n\n");
            printf("Jogadas: %d\n", jogadas);
            imprimirTabuleiro(tabuleiro);
        }

        while (controladorCliques) { // inicia a partida
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

                limitarCursor(&x, &y);

                printf("Vez do jogador %c\n\n", jogador);

                quadrante = determinarQuadrante(x, y);
                printf("Você está no quadrante %d\n", quadrante);

                int i = (quadrante - 1) / 3;
                int j = (quadrante - 1) % 3;

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
                    printf("%c Ganhou!\n Jogar novamente? aperte botao 0, senao 1\n", jogador);
                    //if (dataButton == 1) {
                        //continue;
                    if(dataButton == 2) {
                        printf("%d", dataButton);
                        dataButton = 0;
                        break;
                    }
                    // Reseta o jogo
                    //controladorCliques = 0;
                    
                } else if (empate) {
                    system("clear");
                    imprimirTabuleiro(tabuleiro);
                    printf("Empate!\n");
                    // Reseta o jogo
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