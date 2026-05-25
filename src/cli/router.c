#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "cli/router.h"

#include "ui/ui_help.h"

CravdataMode cli_router(int argc, char *argv[]) {

    if (argc == 1 || argv[1][0] == '-') {
        return MODE_DEFAULT;
    }

    else if (strcmp(argv[1], "hash") == 0) {
        return MODE_HASH;
    }

    else if (strcmp(argv[1], "file") == 0) {
        return MODE_FILE;
    }
    
    fprintf(stderr, "[!] Error: Unknown subcommand '%s'.\n\n", argv[1]);
    ui_render_usage();
    exit(EXIT_FAILURE);
}