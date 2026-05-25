#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>

#include "cli/args.h"

void cli_args_init(RawArgs *array) {
    array->count = 0;
    array->capacity = 1;
    array->items = malloc(array->capacity * sizeof(RawArg));
}

void cli_args_add(RawArgs *array, char flag, const char *value) {
    if (array->count >= array->capacity) {
        array->capacity *= 2;
        array->items = realloc(array->items, array->capacity * sizeof(RawArg));
    }

    array->items[array->count].flag = flag;
    array->items[array->count].raw_value = value ? strdup(value) : NULL;
    array->count++;
}

void cli_args_free(RawArgs *array) {
    if (!array) return;
    
    for (int i = 0; i < array->count; i++) {
        if (array->items[i].raw_value) {
            free(array->items[i].raw_value);
        }
    }
    free(array->items);
    array->items = NULL;
    array->count = 0;
    array->capacity = 0;
}