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
    char *charset;
} Settings;

// Global singleton for configuration
extern Settings settings;


// --- GETTERS ---
int settings_get_min(void);
int settings_get_max(void);
int settings_get_threads(void);
bool settings_get_md5(void);
bool settings_get_verbose(void);
const char* settings_get_charset(void);

// --- SETTERS ---
void settings_set_int(int *settings_field, int value);
void settings_set_bool(bool *settings_field);
bool settings_set_string(char **settings_field, const char *value);

#endif