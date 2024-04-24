#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

#define MOUSEFILE "/dev/input/mice"

int main() {
    int fd;
    char button;
    signed char x_disp, y_disp;
    int x = 0, y = 0; // Inicialize x e y com zero
    char mouse_buffer[3]; 

    fd = open(MOUSEFILE, O_RDONLY);

    if (fd == -1) {
        perror("Não é possível abrir o dispositivo do mouse");
        exit(EXIT_FAILURE);
    }

    while (1) {
        if (read(fd, &mouse_buffer, sizeof(mouse_buffer)) > 0) {
            button = mouse_buffer[0] & 0x07; // Extrai os bits do botão do buffer
            x_disp = mouse_buffer[1];
            y_disp = mouse_buffer[2];

            x += x_disp;
            y -= y_disp;

            if (button & 0x01) { // Verifica se o bit 0 (botão esquerdo) está definido
                printf("Clicou em x=%d e y=%d\n", x, y);
            }
            printf("Botão: %d, Posição X: %d, Posição Y: %d\n", button, x, y);
        }

        usleep(10000); // Espera 10ms antes de verificar novamente o mouse
    }

    close(fd);
    return 0;
}
