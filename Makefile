# Makefile para Proyecto de Pizzería

# Compilador
CC = gcc

# Banderas de compilación
CFLAGS = -Wall -Wextra -I./include -std=c99

# Directorio de código fuente
SRC_DIR = src

# Archivos objeto
OBJS = $(SRC_DIR)/main.o $(SRC_DIR)/csv_parser.o $(SRC_DIR)/metrics.o

# Nombre del ejecutable
TARGET = app1

# Regla por defecto
all: $(TARGET)

# Enlazar el ejecutable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compilar archivos fuente
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpiar archivos compilados
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean