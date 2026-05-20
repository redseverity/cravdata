#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "settings/settings.h"

#include "ui/display.h"

Settings settings = {
    .min = 1,
    .max = 3,
    .threads = 1,
    .md5 = false,
    .verbose = false,
    .charset = NULL
};


// --- GETTERS ---
int settings_get_min(void) { return settings.min; }
int settings_get_max(void) { return settings.max; }
int settings_get_threads(void) { return settings.threads; }
bool settings_get_md5(void) { return settings.md5; }
bool settings_get_verbose(void) { return settings.verbose; }
const char* settings_get_charset(void) { return settings.charset; }


// --- SETTERS ---
void settings_set_int(int *settings_field, int value) {
    *settings_field = value;
}

void settings_set_bool(bool *settings_field) {
    *settings_field = true;
}

bool settings_set_string(char **settings_field, const char *value) {
    if (!value) return false;

    char *tmp = malloc(strlen(value) + 1);
    if (!tmp) {
        return false;
    }

    strcpy(tmp, value);
    free(*settings_field); 
    *settings_field = tmp; 
    
    return true;
}