#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "settings/settings.h"

// Global singleton for configuration
settings_config_t settings = {
    .min = 1,
    .max = 3,
    .threads = 1,
    .md5 = false,
    .verbose = false,
    .help = false,
    .charset = NULL
};

// Generic getter for integers
int settings_get_int(int *settings_field) {
    return *settings_field;
}

// Generic getter for boolean flags
bool settings_get_bool(bool *settings_field) {
    return *settings_field;
}

// Getter for strings
const char* settings_get_string(char **settings_field) {
    return *settings_field;
}

// Generic setter for integers
void settings_set_int(int *settings_field, int value) {
    *settings_field = value;
}

// Generic setter for boolean flags
void settings_set_bool(bool *settings_field, bool value) {
    *settings_field = value;
}

// Setter for strings (manages malloc/free)
void settings_set_string(char **settings_field, const char *value) {
    if (!value) return;

    char *tmp = malloc(strlen(value) + 1);
    if (!tmp) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    strcpy(tmp, value);

    free(*settings_field);
    *settings_field = tmp;
}