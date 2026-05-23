#ifndef CRAVDATA_SETTINGS_SETTINGS_H
#define CRAVDATA_SETTINGS_SETTINGS_H

#include <stdbool.h>

#include "cli/args.h"

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
bool settings_load_from_raw(const RawArgList *list);

#endif