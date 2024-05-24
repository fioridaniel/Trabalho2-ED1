# Makefile para compilar os códigos

# Compiler
CC = gcc

# Flags de compilação
CFLAGS = -Wall -Wextra -W -g -std=c99 -fstack-protector-all

# Nome do executável
TARGET = ted

# Fontes
SOURCES = arqgeo.c main.c arqsvg.c circulo.c retangulo.c linha.c texto.c leArquivo.c shapebank.c registrador.c qry.c pilha.c path.c garbage.c lista.c

# Objetos
OBJECTS = $(SOURCES:.c=.o)

# Regra principal
all: $(TARGET)

# Regra de compilação
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

# Regra para compilar cada fonte
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza
clean:
	rm -f $(OBJECTS) $(TARGET)