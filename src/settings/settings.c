#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>

#include "settings/settings.h"

Settings settings = {
    .min = 1,
    .max = 3,
    .threads = 1,
    .verbose = false,
    .charset = NULL,
    .hash = {
        .md5 = false,
        .target_hash  = NULL
    },
    .file = {
        .target_file = NULL
    }
};

static void settings_set_int(int *settings_field, int value) {
    *settings_field = value;
}

static void settings_set_bool(bool *settings_field) {
    *settings_field = true;
}

static bool settings_set_str(char **settings_field, const char *value) {
    if (!value) return false;

    size_t len = strlen(value);
    char *tmp = malloc(len + 1);
    
    if (!tmp) {
        fprintf(stderr, "[!] Fatal error: Out of memory allocating %zu bytes for charset.\n", len + 1);
        return false;
    }

    strcpy(tmp, value);
    free(*settings_field); 
    *settings_field = tmp; 
    
    return true;
}

bool settings_load_raw(const RawArgs *array, int argc, char *argv[], CravdataMode mode) {
    for (int i = 0; i < array->count; i++) {
        char flag = array->items[i].flag;
        const char *val = array->items[i].raw_value;

        switch (flag) {
            case 'm': settings_set_int(&settings.min, val ? atoi(val) : 0); break;
            case 'x': settings_set_int(&settings.max, val ? atoi(val) : 0); break;
            case 't': settings_set_int(&settings.threads, val ? atoi(val) : 0); break;
            case 'c': if (!settings_set_str(&settings.charset, val)) return false; break;
            case 'v': settings_set_bool(&settings.verbose); break;
            case '1': settings_set_bool(&settings.hash.md5); break;
            default: return false;
        }
    }

    // Capture positional target argument based on current mode
    if (mode == MODE_HASH && optind < argc) {
        settings.hash.target_hash = argv[optind];
    } 
    else if (mode == MODE_FILE && optind < argc) {
        settings.file.target_file = argv[optind];
    }

    return true;
}