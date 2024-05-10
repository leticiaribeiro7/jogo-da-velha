CC = gcc
TARGET = jogoExe
SOURCES = main2.c tabuleiro.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $^ -o $@ -lintelfpgaup

.PHONY: clean
clean:
	rm -f $(TARGET)
