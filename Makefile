CC = gcc
TARGET = jogo.exe
SOURCES = main.c tabuleiro.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $^ -o $@ -lintelfpgaup

.PHONY: clean
clean:
	rm -f $(TARGET)