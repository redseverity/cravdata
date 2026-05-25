#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>

#include "cli/args.h"
#include "cli/router.h"
#include "cli/input.h"
#include "cli/validate.h"
#include "settings/settings.h"
#include "ui/ui_settings.h"

int main(int argc, char *argv[]) {
    RawArgs array;

    CravdataMode mode = cli_router(argc, argv);

    cli_args_init(&array);

    cli_input_args(argc, argv, &array, mode);

    if (!cli_validate_syntax(argc, optind, argv, &array, mode)) {
        cli_args_free(&array);
        exit(EXIT_FAILURE);
    }

    if (!settings_load_raw(&array, argc, argv, mode)) {
        cli_args_free(&array);
        exit(EXIT_FAILURE);
    }

    cli_args_free(&array);

    if (!cli_validate_logic(&settings, mode)) {
        exit(EXIT_FAILURE);
    }
    
    ui_render_settings(&settings, mode);

    exit(EXIT_SUCCESS);
}