// Standard library includes
#include <stdio.h>
#include <getopt.h>
#include <string.h>
// Project headers
#include "cli/parser.h"

void parse(int argc, char *argv[]){
    if (argc > 1) printf("param count: %d\n", argc-1);

    for(int c = 0; c < argc; c++){
        if(c > 0) printf("param: %s\n", argv[c]);
    }
}