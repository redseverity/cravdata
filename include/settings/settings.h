#ifndef CRAVDATA_SETTINGS_SETTINGS_H
#define CRAVDATA_SETTINGS_SETTINGS_H

#include <stdbool.h>
#include "cli/args.h"
#include "cli/router.h"

typedef struct {
    int min;
    int max;
    int threads;
    bool verbose;
    char *charset;

    struct {
        bool md5;
        const char *target_hash;
    } hash;

    struct {
        const char *target_file;
    } file;
    
} Settings;

extern Settings settings;

bool settings_load_raw(const RawArgs *array, int argc, char *argv[], CravdataMode mode);

#endif