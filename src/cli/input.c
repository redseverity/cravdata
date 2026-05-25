#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#include "cli/input.h"

#include "cli/validate.h"
#include "utils/utils.h"
#include "ui/ui_help.h"

// Standard long options configuration for getopt_long
static struct option cli_options[] = {
    {"min",     required_argument, 0, 'm'},
    {"max",     required_argument, 0, 'x'},
    {"threads", required_argument, 0, 't'},
    {"charset", required_argument, 0, 'c'},
    {"verbose", no_argument,       0, 'v'},
    {"help",    no_argument,       0, 'h'},
    {"md5",     no_argument,       0, '1'},
    {0, 0, 0, 0}
};

void cli_input_args(int argc, char *argv[], RawArgs *array, CravdataMode mode){
    // Disable standard getopt error messages to use custom UI error handlings
    opterr = 0;

    // Adjust optind to skip the subcommand name (e.g., 'hash' or 'file') if a mode is active
    if (mode != MODE_DEFAULT) { 
        optind = 2; 
    } else {
        optind = 1;
    }

    char flag_buf[32];
    const char *flag_name;

    int opt;
    int longindex = -1;

    while ((opt = getopt_long(argc, argv, "+:m:x:t:c:vh1", cli_options, &longindex)) != -1) {

        utils_disable_abbreviations(longindex, optind, argv, cli_options);

        switch (opt) {
            case 'm':
            case 'x':
            case 't':
            case 'c':
                cli_args_add(array, opt, optarg);
                break;

            case 'v':
            case '1':
                cli_args_add(array, opt, NULL);
                break;
            
            case 'h':
                ui_render_help(mode);
                exit(EXIT_SUCCESS);

            // Handle missing argument for options that require one
            case ':':
                flag_name = utils_resolve_flag_name(optopt, optind, argv, flag_buf, sizeof(flag_buf));
                fprintf(stderr, "[!] Option '%s' requires an argument.\n\n", flag_name);
                ui_render_usage();
                exit(EXIT_FAILURE);

            // Handle invalid or unknown options
            case '?':
            default:
                flag_name = utils_resolve_flag_name(optopt, optind, argv, flag_buf, sizeof(flag_buf));
                fprintf(stderr, "[!] Unrecognized option '%s'.\n\n", flag_name);
                ui_render_usage();
                exit(EXIT_FAILURE);
        }

        // Reset longindex tracking for the next iteration
        longindex = -1;
    }
}