#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
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
    int jogoIniciado = 0; // Flag para controlar se o jogo já foi iniciado
    int sairJogo = 0; // Flag para sair do jogo

    fd = open(MOUSEFILE, O_RDONLY); // Abre arquivo do mouse
    KEY_open(); // Abre botões

    if (fd == -1) {
        perror("Não é possível abrir o dispositivo do mouse");
        exit(EXIT_FAILURE);
    }

    char tabuleiro[3][3] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}
    };

    printf("Clique no botão para iniciar a partida\n");

    // Loop principal
    while (!sairJogo) {
        // Lê o estado dos botões
        KEY_read(&dataButton);

        // Verifica o segundo botão para sair do jogo
        if (dataButton & 0b10) {
            printf("Saindo do jogo...\n");
            break;
        }

        // Verifica o primeiro botão para iniciar ou reiniciar a partida
        if (dataButton & 0b1) {
            if (jogoIniciado) {
                // Reinicia o jogo
                jogadas = 0;
                x = 0;
                y = 0;
                jogador = 'X';
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        tabuleiro[i][j] = '1' + i * 3 + j;
                    }
                }
                printf("Jogo reiniciado. Clique para fazer uma jogada.\n");
            } else {
                // Inicia o jogo pela primeira vez
                jogoIniciado = 1;
                jogador = 'X';
                printf("Jogo iniciado. Clique para fazer uma jogada.\n");
            }
            usleep(500000); // Adiciona um pequeno atraso para evitar múltiplas detecções
        }

        // Apenas processar jogadas se o jogo já foi iniciado
        if (jogoIniciado) {
            // Lê o estado do mouse
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

                int i = posicoes[quadrante-1][0];
                int j = posicoes[quadrante-1][1];

                if (leftButton && jogadaValida(tabuleiro, i, j)) {
                    tabuleiro[i][j] = jogador;
                    jogadas++;
                }

                // Verifica vitória ou empate
                int vitoria = verificarVitoria(tabuleiro);
                int empate = verificarEmpate(tabuleiro);

                if (vitoria) {
                    system("clear");
                    imprimirTabuleiro(tabuleiro);
                    printf("%c Ganhou!\n", jogador);
                    // Reseta o jogo
                    jogoIniciado = 0;
                    continue;
                } else if (empate && jogadas == 9) {
                    system("clear");
                    imprimirTabuleiro(tabuleiro);
                    printf("Empate!\n");
                    // Reseta o jogo
                    jogoIniciado = 0;
                    continue;
                }

                jogador = alternaJogadores(jogadas);
                usleep(2000); // Espera 20ms antes de verificar novamente o mouse
            }
        }
    }

    KEY_close();
    close(fd);
    return 0;
}
