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
    .charset = "abc123"
};

// Getters -------------------

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

// Setters -------------------

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

// Print Settings
void settings_print(void) {
    typedef enum {
        T_INT,
        T_BOOL,
        T_STRING,
    } Type;

    typedef struct
    {
        const char *key;
        void *value;
        Type type;
    } ConfigEntry;

    ConfigEntry arrayy[] = {
        {"min", &settings.min, T_INT},
        {"max", &settings.max, T_INT},
        {"threads", &settings.threads, T_INT},
        {"charset", &settings.charset, T_STRING},
        {"md5", &settings.md5, T_BOOL},
        {"verbose", &settings.verbose, T_BOOL},
        {"help", &settings.help, T_BOOL}
    };

    printf("\n••• CURRENT SETTINGS •••\n");

    for (size_t i = 0; i < (sizeof(arrayy) / sizeof(arrayy[0])); i++) {
        switch (arrayy[i].type) {
            case T_INT:
                printf("[✓] %-8s : %i\n", arrayy[i].key, *(int*)arrayy[i].value);
                break;

            case T_BOOL:
                if (*(bool*)arrayy[i].value == true) {
                    printf("[✓] %-8s : true\n", arrayy[i].key);
                }
                break;

            case T_STRING: {
                char *str_val = *(char**)arrayy[i].value;
                printf("[✓] %-8s : %s\n", arrayy[i].key, str_val);
                break;
            }
            
            default:
                break;
        }
    }

    printf("••••••••••••••••••••••••\n\n");
}