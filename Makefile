CC = gcc
TARGET = jogo.exe
SOURCES = main.c tabuleiro.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $^ -o $@

.PHONY: clean
clean:
	rm -f $(TARGET)