NAME = cravdata
BUILD_DIR = build
OUT = $(BUILD_DIR)/$(NAME)
SRC = src/main.c src/cli/parser.c src/settings/settings.c

CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -std=c99

.PHONY: build start clean

clean:
	rm -f $(OUT)

start:
	./$(OUT)

build:
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)