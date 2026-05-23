#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "settings/settings.h"

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

// --- SETTERS PRIVADOS ---
static void settings_set_int(int *settings_field, int value) {
    *settings_field = value;
}

static void settings_set_bool(bool *settings_field) {
    *settings_field = true;
}

static bool settings_set_string(char **settings_field, const char *value) {
    if (!value) return false;

    char *tmp = malloc(strlen(value) + 1);
    if (!tmp) return false;

    strcpy(tmp, value);
    free(*settings_field); 
    *settings_field = tmp; 
    
    return true;
}

bool settings_load_from_raw(const RawArgList *list) {
    for (int i = 0; i < list->count; i++) {
        char flag = list->args[i].flag;
        const char *val = list->args[i].raw_value;

        switch (flag) {
            case 'm':
                // Conversão direta sem julgamento de valor.
                settings_set_int(&settings.min, val ? atoi(val) : 0);
                break;
            case 'x':
                settings_set_int(&settings.max, val ? atoi(val) : 0);
                break;
            case 't':
                settings_set_int(&settings.threads, val ? atoi(val) : 0);
                break;
            case 'c':
                if (!settings_set_string(&settings.charset, val)) {
                    return false;
                }
                break;
            case '1': 
                settings_set_bool(&settings.md5); 
                break;
            case 'v': 
                settings_set_bool(&settings.verbose); 
                break;
        }
    }
    return true;
}