#include <stdlib.h>
#include <getopt.h>
#include <stdio.h>

#include "cli/args.h"
#include "cli/fetch_args.h"
#include "cli/validate.h"
#include "settings/settings.h"
#include "ui/display.h"
#include "utils/utils.h"

int main(int argc, char *argv[]){
    RawArgList args;

    list_args_init(&args);

    if (argc == 1){
        list_args_free(&args);
        exit(EXIT_FAILURE);
    }

    fetch_args(argc, argv, &args);

    if (!validate_raw_list(&args, argc, optind, argv)) {
        list_args_free(&args);
        exit(EXIT_FAILURE);
    }

    if (!settings_load_from_raw(&args)) {
        list_args_free(&args);
        exit(EXIT_FAILURE);
    }

    list_args_free(&args);

    if (!validate_logic(&settings)) exit(EXIT_FAILURE);
    
    ui_display_setting(&settings);
    return 0;
}