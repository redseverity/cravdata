#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "cli/parser.h"
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
            case 'm':
                settings_set_min(atoi(optarg));
                break;

            case 'x':
                settings_set_max(atoi(optarg));
                break;

            case 't':
                settings_set_threads(atoi(optarg));
                break;

            case 'c':
                settings_set_charset(optarg);
                break;

            case '1':
                settings_set_md5(true);
                break;

            case 'v':
                settings_set_verbose(true);
                break;
            
            case 'h':
                settings_set_help(true);
                return;

            default:
                fprintf(stderr, "Invalid argument\n");
                exit(1);
        }
    }
    
}