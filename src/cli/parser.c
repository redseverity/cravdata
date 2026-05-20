#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#include "cli/parser.h"
#include "cli/validate.h"
#include "utils/utils.h"
#include "settings/settings.h"
#include "ui/display.h"

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

// Parses command-line arguments and populates settings structure
void cli_parse(int argc, char *argv[], Settings *s){

    if (argc == 1){
        ui_display_help_usage();
        exit(EXIT_SUCCESS);
    }

    opterr = 0;
    int opt;
    int longindex = -1;
    char flag_buf[32];
    const char *flag_name;

    while ((opt = getopt_long(argc, argv, ":m:x:t:c:1vh", cli_options, &longindex)) != -1) {

        // Enforce strict matching by disabling long option abbreviations
        if (longindex != -1) {
            const char *raw_arg = argv[optind - 1];
            
            if ((raw_arg[0] == '\0' || raw_arg[0] != '-') && optind > 2) {
                raw_arg = argv[optind - 2];
            }

            if (strncmp(raw_arg, "--", 2) == 0) {
                const char *input_name = raw_arg + 2;

                if (strcmp(input_name, cli_options[longindex].name) != 0) {
                    fprintf(stderr, "[!] Error: Argument '%s' is unexpected (abbreviations are disabled).\n\n", raw_arg);
                    ui_display_help_usage();
                    exit(EXIT_FAILURE);
                }
            }
        }

        switch (opt) {
            case 'm': {
                int value = cli_validate_arg_int(optarg, optopt, optind, argv, 1, 1000);
                settings_set_int(&s->min, value);
                break;
            }

            case 'x': {
                int value = cli_validate_arg_int(optarg, optopt, optind, argv, 1, 1000);
                settings_set_int(&s->max, value);
                break;
            }

            case 't': {
                // TODO: Implement dynamic upper bound for threads based on system capabilities.
                int value = cli_validate_arg_int(optarg, optopt, optind, argv, 1, 256);
                settings_set_int(&s->threads, value);
                break;
            }

            case 'c': {
                const char *value = cli_validate_arg_str(optarg, optopt, optind, argv);
                
                if (!settings_set_string(&s->charset, value)) {
                    flag_name = utils_resolve_flag_name(optopt, optind, argv, flag_buf, sizeof(flag_buf));
                    fprintf(stderr, "[!] Critical Error: Memory allocation failed while parsing '%s'.\n\n", flag_name);
                    ui_display_help_usage();
                    exit(EXIT_FAILURE);
                }

                break;
            }

            case '1': {
                settings_set_bool(&s->md5);
                break;
            }

            case 'v': {
                settings_set_bool(&s->verbose);
                break;
            }
            
            case 'h': {
                ui_display_help();
                exit(EXIT_SUCCESS);
            }

            case ':':
                flag_name = utils_resolve_flag_name(optopt, optind, argv, flag_buf, sizeof(flag_buf));
                fprintf(stderr, "[!] Error: Argument '%s' requires a value.\n\n", flag_name);
                ui_display_help_usage();
                exit(EXIT_FAILURE);

            case '?':
            default:
                flag_name = utils_resolve_flag_name(optopt, optind, argv, flag_buf, sizeof(flag_buf));
                fprintf(stderr, "[!] Error: Argument '%s' is unexpected.\n\n", flag_name);
                ui_display_help_usage();
                exit(EXIT_FAILURE);
        }

        longindex = -1;
    }

    // Check for unexpected positional arguments after processing options
    if (optind < argc) {
        fprintf(stderr, "[!] Error: Argument '%s' is unexpected.\n\n", argv[optind]);
        ui_display_help_usage();
        exit(EXIT_FAILURE);
    }
}