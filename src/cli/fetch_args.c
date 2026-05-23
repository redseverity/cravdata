#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#include "cli/fetch_args.h"
#include "cli/validate.h"
#include "utils/utils.h"
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
void fetch_args(int argc, char *argv[], RawArgList *list){
    opterr = 0;

    char flag_buf[32];
    const char *flag_name;

    int opt;
    int longindex = -1;
    while ((opt = getopt_long(argc, argv, "+:m:x:t:c:1vh", cli_options, &longindex)) != -1) {

        utils_disable_abbreviations(longindex, optind, argv, cli_options);

        switch (opt) {
            case 'm':
            case 'x':
            case 't':
            case 'c':
                list_args_add(list, opt, optarg);
                break;

            case '1':
            case 'v':
                list_args_add(list, opt, NULL);
                break;
            
            case 'h':
                ui_display_help();
                exit(EXIT_SUCCESS);

            case ':':
                flag_name = utils_resolve_flag_name(optopt, optind, argv, flag_buf, sizeof(flag_buf));
                fprintf(stderr, "[!] Option '%s' requires an argument.\n\n", flag_name);
                ui_display_help_usage();
                exit(EXIT_FAILURE);

            case '?':
            default:
                flag_name = utils_resolve_flag_name(optopt, optind, argv, flag_buf, sizeof(flag_buf));
                fprintf(stderr, "[!] Unrecognized option '%s'.\n\n", flag_name);
                ui_display_help_usage();
                exit(EXIT_FAILURE);
        }

        longindex = -1;
    }
}