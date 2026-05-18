#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "cli/help.h"

void cli_help(void) {
    printf("Cravdata is a CPU-bound generative brute-force tool written in C.\n");
    printf("\n");
    printf("Usage:\n");
    printf("  cravdata [options]\n");
    printf("\n");
    printf("Options:\n");
    printf("  -m, --min <length>      Minimum password/path length\n");
    printf("  -x, --max <length>      Maximum password/path length\n");
    printf("  -t, --threads <num>     Number of CPU threads to use\n");
    printf("  -c, --charset <str>     Charset to use in generation\n");
    printf("  -1, --md5               Enable MD5 attack mode\n");
    printf("  -v, --verbose           Enable verbose output\n");
    printf("  -h, --help              Display this help menu\n");
    printf("\n");
    printf("Examples:\n");
    printf("  cravdata -m 4 -x 8 -t 4 -c abcdef\n");
    printf("  cravdata --md5 --verbose\n");
    printf("\n");
    printf("For more information, bugs, and updates visit:\n");
    printf("  https://github.com/redseverity/cravdata");
}