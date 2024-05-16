CC = gcc # Define a variável CC como gcc
TARGET = jogoExe # Define o nome do executável que será gerado
SOURCES = main2.c tabuleiro.c # Lista dos arquivos fonte necessários para a compilação

all: $(TARGET) # Será executada quando nenhum target específico for fornecido

# Regra para criar o executável
$(TARGET): $(SOURCES)
	$(CC) $^ -o $@ -lintelfpgaup
# $(CC) é substituído pelo valor de CC (gcc), $^ representa todos os arquivos fonte e $@ é o nome do target (jogoExe).
# O parâmetro -o indica o nome do arquivo de saída (neste caso, o executável), e -lintelfpgaup são opções de compilação.

.PHONY: clean # Target especial, que será usado para remover arquivos gerados
clean: #Remove o arquivo do executável gerado (jogoExe)
	rm -f $(TARGET) 
