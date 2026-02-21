NAME = cravdata
BUILD_DIR = build
OUT = $(BUILD_DIR)/$(NAME)
SRC = src/main.c src/cli/parser.c

CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

.PHONY: build start clean

clean:
	rm -f $(OUT)

start:
	./$(OUT)

build:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)