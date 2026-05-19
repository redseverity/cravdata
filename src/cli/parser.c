#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#include "cli/parser.h"
#include "cli/validate.h"
#include "ui/display.h"
#include "settings/settings.h"

static struct option cli_options[] = {
    {"min",     required_argument, 0, 'm'}, // minimum password length
    {"max",     required_argument, 0, 'x'}, // maximum password length
    {"threads", required_argument, 0, 't'}, // number of CPU threads
    {"charset", required_argument, 0, 'c'}, // charset to use in generation
    {"md5",     no_argument,       0, '1'}, // enable MD5 attack
    {"verbose", no_argument,       0, 'v'}, // verbose output
    {"help",    no_argument,       0, 'h'}, // help output
    {0, 0, 0, 0} // terminator
};

// sets the flags within the settings structure.
void cli_parse(int argc, char *argv[]){

    if (argc == 1){
        ui_display_help_usage();
        exit(EXIT_SUCCESS);
    }

    opterr = 0;

    int opt;
    int longindex = -1;
    while ((opt = getopt_long(argc, argv, "m:x:t:c:1vh", cli_options, &longindex)) != -1) {

        // --- DISABLE ABBREVIATIONS ---
        if (longindex != -1) {
        
            const char *actual_arg = argv[optind - 1];
            
            if ((actual_arg[0] == '\0' || actual_arg[0] != '-') && optind > 2) {
                actual_arg = argv[optind - 2];
            }

            if (strncmp(actual_arg, "--", 2) == 0) {
                const char *input_name = actual_arg + 2;

                if (strcmp(input_name, cli_options[longindex].name) != 0) {
                    fprintf(stderr, "[!] Error: Argument '%s' is unexpected.\n\n", actual_arg);
                    ui_display_help_usage();
                    exit(EXIT_FAILURE);
                }
            }
        }
        // -----------------------------

        switch (opt) {
            case 'm': {
                int value = cli_validate_arg_int(optarg, optopt, optind, argv, 1, 1000);
                settings_set_min(value);
                break;
            }

            case 'x': {
                int value = cli_validate_arg_int(optarg, optopt, optind, argv, 1, 1000);
                settings_set_max(value);
                break;
            }

            case 't': {
                // TODO: Implement dynamic upper bound for threads based on system capabilities.
                int value = cli_validate_arg_int(optarg, optopt, optind, argv, 1, 256);
                settings_set_threads(value);
                break;
            }

            case 'c': {
                const char *value = cli_validate_arg_str(optarg, optopt, optind, argv);
                settings_set_charset(value);
                break;
            }

            case '1': {
                settings_set_md5(true);
                break;
            }

            case 'v': {
                settings_set_verbose(true);
                break;
            }
            
            case 'h': {
                ui_display_help();
                exit(EXIT_SUCCESS);
            }

            case '?':
            default:
                if (optopt != 0) {
                    fprintf(stderr, "[!] Error: Argument '-%c' is invalid or missing its argument.\n\n", optopt);
                } else {
                    fprintf(stderr, "[!] Error: Argument '%s' is unexpected.\n\n", argv[optind - 1]);
                }
                ui_display_help_usage();
                exit(EXIT_FAILURE);
        }

    // Reset longindex so short options in the next iteration aren't treated as long options
    longindex = -1;
    }

    if (optind < argc) {
        fprintf(stderr, "[!] Error: Argument '%s' is unexpected.\n\n", argv[optind]);
        ui_display_help_usage();
        exit(EXIT_FAILURE);
    }
}