#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "cli/parser.h"
#include "cli/validate.h"
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

void parse(int argc, char *argv[]){
    int opt;
    while ((opt = getopt_long(argc, argv, "m:x:t:c:1vh", cli_options, NULL)) != -1) {
        switch (opt) {
            case 'm': {
                int value = validate_int(optarg, 1, 1000, "min");
                settings_set_int(&settings.min, value);
                printf("min: %d\n", settings_get_int(&settings.min));
                break;
            }

            case 'x': {
                int value = validate_int(optarg, 1, 1000, "max");
                settings_set_int(&settings.max, value);
                printf("max: %d\n", settings_get_int(&settings.max));
                break;
            }

            case 't': {
                // TODO: Implement dynamic upper bound for threads based on system capabilities.
                int value = validate_int(optarg, 1, 256, "threads");
                settings_set_int(&settings.threads, value);
                printf("threads: %d\n", settings_get_int(&settings.threads));
                break;
            }

            case 'c': {
                const char *value = validate_string(optarg);
                settings_set_string(&settings.charset, value);
                printf("charset: %s\n", settings_get_string(&settings.charset));
                break;
            }

            case '1': {
                settings_set_bool(&settings.md5, true);
                printf("md5: %d\n", settings_get_bool(&settings.md5));
                break;
            }

            case 'v': {
                settings_set_bool(&settings.verbose, true);
                printf("verbose: %d\n", settings_get_bool(&settings.verbose));
                break;
            }
            
            case 'h': {
                settings_set_bool(&settings.help, true);
                printf("help: %d\n", settings_get_bool(&settings.help));
                return;
            }

            default:
                fprintf(stderr, "Invalid argument\n");
                exit(EXIT_FAILURE);
        }
    }
                
}