#ifndef CRAVDATA_SETTINGS_SETTINGS_H
#define CRAVDATA_SETTINGS_SETTINGS_H

#include <stdbool.h>

// Struct that holds all configuration options
typedef struct {
    int min;
    int max;
    int threads;
    bool md5;
    bool verbose;
    bool help;
    char *charset;
} settings_config_t;

// Global singleton for configuration
extern settings_config_t settings;

// Getters
int settings_get_int(int *settings_field);       // Generic getter for integers
bool settings_get_bool(bool *settings_field);    // Generic getter for booleans
const char* settings_get_string(char **settings_field); // Getter for strings

// Setters
void settings_set_int(int *settings_field, int value);       // Generic setter for integers
void settings_set_bool(bool *settings_field, bool value);    // Generic setter for booleans
void settings_set_string(char **settings_field, const char *value); // Setter for strings (manages memory)

#endif