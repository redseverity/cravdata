NAME = cravdata
BUILD_DIR = build
OUT = $(BUILD_DIR)/$(NAME)

SRC = \
src/main.c \
src/cli/args.c \
src/cli/fetch_args.c \
src/cli/validate.c \
src/utils/utils.c \
src/settings/settings.c \
src/ui/display.c

CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -std=c99 -O3 -march=native

.PHONY: build start clean

clean:
	rm -rf $(BUILD_DIR)

build: $(OUT)

$(OUT): $(SRC)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)