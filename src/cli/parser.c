// Standard library includes
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <stdbool.h>
// Project headers
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
                min = atoi(optarg);
                printf("min: %d\n", min);
                break;

            case 'x':
                max = atoi(optarg);
                printf("max: %d\n", max);
                break;

            case 't':
                threads = atoi(optarg);
                printf("threads: %d\n", threads);
                break;

            case 'c':
                charset = optarg;
                printf("charset: %s\n", charset);
                break;

            case '1':
                md5 = true;
                printf("md5: %d\n", md5);
                break;

            case 'v':
                verbose = true;
                printf("verbose: %d\n", verbose);
                break;
            
            case 'h':
                help = true;
                printf("help here\n");
                return;

            default:
                fprintf(stderr, "Invalid argument\n");
                exit(1);
        }
    }
    
}