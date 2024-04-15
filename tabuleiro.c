#include <stdio.h>

void imprimirTabuleiro(char tabuleiro[3][3]) {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        printf(" %c | %c | %c ", tabuleiro[i][0], tabuleiro[i][1], tabuleiro[i][2]);
        if (i != 2) {
            printf("\n---|---|---\n");
        }
    }
    printf("\n\n");
}

/**
 * Função para verificar se todos os elementos da diagonal principal são iguais.
 * 
 * @param tabuleiro    Matriz de dimensão 3x3
 * @return             1 se todos os elementos da diagonal principal forem iguais,
 *                     caso contrário, retorna 0.
*/
int verificaDiagonalPrincipal(char tabuleiro[3][3]) {
    char elemento = tabuleiro[0][0];
    int contador = 0;

    for (int col = 0; col < 3; col++) {
        for (int lin = 0; lin < 3; lin++) {
            if(col == lin && tabuleiro[col][lin] == elemento) {
                contador++;
                if(contador == 3) {
                    printf("Ganhou");
                    return 1;
                }
            }
        }
    }
    //printf("NAO GANHOU");
    return 0;
}

/**
 * Função para verificar se todos os elementos da diagonal secundária são iguais.
 * 
 * @param tabuleiro    Matriz de dimensão 3x3
 * @return             1 se todos os elementos da diagonal secundária forem iguais,
 *                     caso contrário, retorna 0.
*/
int verificaDiagonalSecundaria(char tabuleiro[3][3]) {
    char elemento = tabuleiro[2][0];
    int contador = 0;

    for (int col = 2; col >= 0; col--) {
        for (int lin = 2; lin >=0; lin--) {
            if(col == lin && tabuleiro[col][lin] == elemento) {
                contador++;
                
            }
        }
    }
    if(contador == 3) {
        //printf("Ganhou");
        return 1;
    }
    else {
        //printf("NAO GANHOU");
        return 0;
    }
}

int main() {
    char tabuleiro[3][3] = {
        {'O', 'O', 'O'},
        {'O', 'X', 'X'},
        {'O', 'O', 'O'}
    };
    imprimirTabuleiro(tabuleiro);

    //verificaDiagonalPrincipal(tabuleiro);
    verificaDiagonalSecundaria(tabuleiro);

    return 0;
    
}

