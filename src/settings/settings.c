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

void settings_set_min(int value) { settings.min = value; }
void settings_set_max(int value) { settings.max = value; }
void settings_set_threads(int value) { settings.threads = value; }
void settings_set_md5(bool value) { settings.md5 = value; }
void settings_set_verbose(bool value) { settings.verbose = value; }

void settings_set_charset(const char *value) {
    if (!value) return;

    char *tmp = malloc(strlen(value) + 1);
    if (!tmp) {
        fprintf(stderr, "[!] Error: Memory allocation failed for charset.\n\n");
        exit(EXIT_FAILURE);
    }

    strcpy(tmp, value);
    free(settings.charset);
    settings.charset = tmp;
}