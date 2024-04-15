
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int mouse_fd;
    char mouse_buffer[3]; // Para armazenar os dados do mouse
    int x = 0, y = 0; // Variáveis para rastrear a posição X e Y
    int left_button = 0; // Estado do botão esquerdo

    // Abrir o arquivo do mouse em modo de leitura
    mouse_fd = open("/dev/input/mice", O_RDONLY);
    if (mouse_fd == -1) {
        perror("Erro ao abrir o dispositivo do mouse");
        return 1;
    }

    while (1) {
        // Ler 3 bytes do arquivo do mouse
        if (read(mouse_fd, mouse_buffer, sizeof(mouse_buffer)) != sizeof(mouse_buffer)) {
            perror("Erro ao ler dados do mouse");
            break;
        }

        // Atualizar a posição X e Y baseada nos dados do mouse
        x += (int)(char)mouse_buffer[1]; // Movimento horizontal
        y -= (int)(char)mouse_buffer[2]; // Movimento vertical


        // Verificar o estado dos botões
        int left_button = mouse_buffer[0] & 0x01;

        
            // Limpar a linha anterior imprimindo espaços
            printf("\r                                                                                ");
            
            if (left_button == 1) {
                printf("Clicou em x=%d e y=%d\n", x, y);
            }

            // Exemplo de saída para demonstração
            printf("\rPosição X: %d, Posição Y: %d, Botões: Left=%d", x, y, left_button);
            fflush(stdout); // Para forçar a saída ser exibida imediatamente


    }

    // Fechar o arquivo do mouse
    close(mouse_fd);

    return 0;
}