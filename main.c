#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "tabuleiro.h"
#include "intelfpgaup/KEY.h"

#define MOUSEFILE "/dev/input/mice"

char alternaJogadores(int jogadas) {
    if (jogadas % 2 == 0) {
        return 'X'; // Se o número de jogadas for par, retorna 'X'
    }
    return 'O'; // Caso contrário, retorna 'O'
}


// Limitando coordenadas entre 1 e 200
void limitarCursor(int *x, int *y) {
    if (*x <= 1) *x = 1; // Se x for menor ou igual a 1, define x como 1
    if (*y <= 1) *y = 1; // Se y for menor ou igual a 1, define y como 1
    if (*x >= 200) *x = 200; // Se y for menor ou igual a 1, define y como 1
    if (*y >= 200) *y = 200; // Se y for maior ou igual a 200, define y como 200
}

// Esta função determina em qual "casa" (quadrante) do tabuleiro está uma determinada posição (x, y).
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
    char jogador = 'X';
    int jogadas = 0;
    int dataButton = 0;
    int executando = 1; // Flag para executar o jogo
    int controladorCliques = 0;


    fd = open(MOUSEFILE, O_RDONLY); // Abre arquivo do mouse
    KEY_open(); // Abre botões da placa

    if (fd == -1) // Se o arquivo do mouse retornar -1 significa que deu erro ao abrir o dispositivo{
        perror("Não é possível abrir o dispositivo do mouse");
        exit(EXIT_FAILURE);
    }

    // Define o tabuleiro inicial.
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


    
    

    while (executando) {
        
        KEY_read(&dataButton);
       
        menuInicializacaoJogo(); // Exibe o menu de inicialização do jogo
        usleep(500000); // Espera 500 milissegundos (5ms)
        system("clear");  // Limpa a tela do terminal
       

        // Se o botão KEY2 for pressionado, o jogo é finalizado e encerra a execução no terminal
        if (dataButton == 0b100) {
            printf("Saindo do jogo...\n");
            dataButton = 0; // Limpa o estado do botão
            break;
        } // Se o botão KEY0 é pressionado, o jogo inicia.
        else if (dataButton == 0b001) {
			reinicializarTabuleiro(tabuleiro); // Reinicializa o tabuleiro do jogo
            controladorCliques = 1;
            imprimirTabuleiro(tabuleiro); // Imprime o tabuleiro atualizado
            printf("Jogadas: %d\n\n", jogadas);
			printf("Você está na casa %d\n", casa);
            printf("Vez do jogador %c\n\n", jogador);
        }

        while (controladorCliques) { // inicia a partida
            // Se o botão KEY1 for pressionado, a partida atual é encerrada e o menu é exibido.
            if(dataButton == 0b010){
                printf("Desistindo da partida...\n");
                sleep(2);
                system("clear");
                printf("Partida cancelada.\n");
                sleep(2);
                reinicializarTabuleiro(tabuleiro); // Reinicializa o tabuleiro
                dataButton = 0;  
                jogadas = 0; // Reinicia o contador de jogadas.
                controladorCliques = 0; // O loop while (controladorCliques) é encerrado.
            }

            if (read(fd, &mouse_buffer, sizeof(mouse_buffer)) > 0 && (controladorCliques)) {
                KEY_read(&dataButton); // Lê os botões pressionados.
                system("clear");
                imprimirTabuleiro(tabuleiro);
                printf("Jogadas: %d\n\n", jogadas);
                x_disp = mouse_buffer[1];
                y_disp = mouse_buffer[2];
                leftButton = mouse_buffer[0] & 0x1;

                x += x_disp;
                y -= y_disp;

                limitarCursor(&x, &y); // Limita as coordenadas do cursor dentro dos limites do tabuleiro

                casa = determinarCasa(x, y); // Determina em qual casa do tabuleiro o cursor está
                printf("Você está na casa %d\n", casa);

                printf("Vez do jogador %c\n\n", jogador);

                int i = posicoes[casa-1][0];
                int j = posicoes[casa-1][1];

                if (leftButton && jogadaValida(tabuleiro, i, j)) {
                    tabuleiro[i][j] = jogador; // Realiza a jogada se o botão esquerdo do mouse for pressionado e a jogada for válida
                    jogadas++; // Incrementa o contador de jogadas.
                }

                // Verifica vitória ou empate
                int vitoria = verificarVitoria(tabuleiro);
                int empate = verificarEmpate(tabuleiro, &jogadas);

                if (vitoria) {
		            int i = 5;
                    system("clear");
                    for (i; i > 0; i--) {
			            imprimirTabuleiro(tabuleiro);
                    	printf("%c Ganhou!\n", jogador); // Exibe o jogador vencedor.
                        printf("Voltando para o menu em %d...\n", i); // Informa sobre o retorno ao menu.
                        sleep(1);
                        system("clear");
                    }
                    dataButton = 0;   
                    vitoria = 0;
                    jogadas = 0;
                    controladorCliques = 0; // Encerra o loop while (controladorCliques) após o término da partida.
                    
                } else if (empate) {
		            int i = 5;
                    system("clear");
                    imprimirTabuleiro(tabuleiro);
                    printf("Empate!\n");
                    
                    for (i; i > 0; i--) {
			            imprimirTabuleiro(tabuleiro);
                    	printf("Empate!\n");
                        printf("Voltando para o menu em %d...\n", i);
                        sleep(1);
                        system("clear");
                    }
                    
                    dataButton = 0;
                    empate = 0;
                    jogadas = 0;
                    controladorCliques = 0; // Encerra o loop while (controladorCliques) após o término da partida.
              }

                jogador = alternaJogadores(jogadas); // Alterna o jogador atual.
              	usleep(2000); // Espera 2 ms antes de verificar novamente o mouse
            }
        }
       
    }

    KEY_close();
    close(fd);
    return 0;
}
