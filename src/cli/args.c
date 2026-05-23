#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include "cli/args.h"

void list_args_init(RawArgList *list) {
    list->count = 0;
    list->capacity = 1;
    list->args = malloc(list->capacity * sizeof(RawArg));
}

void list_args_add(RawArgList *list, char flag, const char *value) {
    if (list->count >= list->capacity) {
        list->capacity *= 2;
        list->args = realloc(list->args, list->capacity * sizeof(RawArg));
    }

    list->args[list->count].flag = flag;
    list->args[list->count].raw_value = value ? strdup(value) : NULL;
    list->count++;
}

void list_args_free(RawArgList *list) {
    if (!list) return;
    
    for (int i = 0; i < list->count; i++) {
        if (list->args[i].raw_value) {
            free(list->args[i].raw_value);
        }
    }
    free(list->args);
    list->args = NULL;
    list->count = 0;
    list->capacity = 0;
}