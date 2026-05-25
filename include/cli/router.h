#ifndef CRAVDATA_CLI_ROUTER_H
#define CRAVDATA_CLI_ROUTER_H

#include "cli/args.h"

typedef enum {
    MODE_DEFAULT,
    MODE_HASH,
    MODE_FILE
} CravdataMode;

/**
 * Intercepts the command line arguments, determines the operational mode,
 * delegates the parsing to the correct input module, and returns the selected mode.
 */
CravdataMode cli_router(int argc, char *argv[]);

#endif