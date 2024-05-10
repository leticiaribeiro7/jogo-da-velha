#include <stdio.h>
#include <ctype.h>

void imprimirTabuleiro(char tabuleiro[3][3]) {
    printf("===== JOGO DA VELHA =====\n\n");
    int i;
    for (i = 0; i < 3; i++) {
        printf(" %c | %c | %c ", tabuleiro[i][0], tabuleiro[i][1], tabuleiro[i][2]);
        if (i != 2) {
            printf("\n---|---|---\n");
        }
    }
    printf("\n\n");
}

void reinicializarTabuleiro(char tabuleiro[3][3]) {
    int num = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            tabuleiro[i][j] = num + '0';
            num++;
        }
    }
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
    int i;
	for (i = 0; i < 3; i++) {
		if (tabuleiro[i][i] != elemento) {
			return 0; 
		}
	}
	return 1; 
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
    int i;
	for (i = 0; i < 3; i++) {
		if (tabuleiro[i][2 - i] != elemento) {
			return 0; 
		}
	}
	return 1; 
}

/**
 * Verifica se há um vencedor em uma linha.
 * 
 * @param tabuleiro   Matriz de dimensão 3x3
 * @return            1 se todos os elementos de uma linha forem iguais,
 *                    caso contrário, retorna 0.
*/
int verificarLinhas(char tabuleiro[3][3]) {
    int lin;

    for (lin = 0; lin < 3; lin++) {
        if ((tabuleiro[lin][0] == tabuleiro[lin][1]) && (tabuleiro[lin][1] == tabuleiro[lin][2])) {
            return 1;
        }
    }
    return 0;
}

/**
 * Verifica se há um vencedor em uma coluna.
 * 
 * @param tabuleiro   Matriz de dimensão 3x3
 * @return            1 se todos os elementos de uma coluna forem iguais,
 *                    caso contrário, retorna 0.
*/
int verificarColunas(char tabuleiro[3][3]) {
    int col;

    for (col = 0; col < 3; col++) {
        if (tabuleiro[0][col] == tabuleiro[1][col] && tabuleiro[1][col] == tabuleiro[2][col]) {
            return 1;
        }
    }
    return 0;
}

/**
 * Verifica se há empate no jogo.
 * 
 * Esta função verifica se o jogo terminou em empate.
 * 
 * @param tabuleiro    Matriz de dimensão 3x3
 * @return             1 se o jogo terminou em empate, 0 caso contrário. 
*/
int verificarEmpate(char tabuleiro[3][3], int *jogadas) {
    // Verifica se não há vencedor em nenhuma das condições possíveis
    int resultadoDiagonalPrincipal = verificaDiagonalPrincipal(tabuleiro);
    int resultadoDiagonalSecundaria = verificaDiagonalSecundaria(tabuleiro);
    int resultadoLinhas = verificarLinhas(tabuleiro);
    int resultadoColunas = verificarColunas(tabuleiro);

    // Se nenhuma das condições indicar um vencedor, então há um empate
    if (!resultadoDiagonalPrincipal &&
        !resultadoDiagonalSecundaria &&
        !resultadoLinhas && 
        !resultadoColunas && *jogadas == 9) {
        return 1;
    }
    else {
        return 0;
    }

}

int verificarVitoria(char tabuleiro[3][3]) {
    int resultadoDiagonalPrincipal = verificaDiagonalPrincipal(tabuleiro);
    int resultadoDiagonalSecundaria = verificaDiagonalSecundaria(tabuleiro);
    int resultadoLinhas = verificarLinhas(tabuleiro);
    int resultadoColunas = verificarColunas(tabuleiro);

    if (resultadoDiagonalPrincipal || resultadoDiagonalSecundaria || resultadoLinhas || resultadoColunas) {
        return 1;
    } else {
        return 0;
    }

}

int jogadaValida(char tabuleiro[3][3], int i, int j) {
    if (tabuleiro[i][j] == 'X' || tabuleiro[i][j] == 'O') {
        return 0;
    }
    return 1;
}
