#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "utils/utils.h"
#include "ui/ui_help.h"

// Resolves option flag names dynamically from parsing context
const char* utils_resolve_flag_name(int optopt_val, int optind_val, char *const argv[], char *buffer, size_t buf_len) {
    if (optopt_val != 0) {
        snprintf(buffer, buf_len, "-%c", optopt_val);
        return buffer;
    }
    
    const char *flag_name = argv[optind_val - 1];
    
    if ((flag_name[0] == '\0' || flag_name[0] != '-') && optind_val > 2) {
        flag_name = argv[optind_val - 2];
    }
    
    return flag_name;
}

// Enforce strict matching by disabling long option abbreviations
void utils_disable_abbreviations(int longindex, int optind, char *const argv[], const struct option *cli_options) {
    if (longindex == -1) {
        return;
    }

    const char *raw_arg = argv[optind - 1];
        
    if ((raw_arg[0] == '\0' || raw_arg[0] != '-') && optind > 2) {
        raw_arg = argv[optind - 2];
    }

    if (strncmp(raw_arg, "--", 2) == 0) {
        const char *input_name = raw_arg + 2;
        
        if (strcmp(input_name, cli_options[longindex].name) != 0) {
            fprintf(stderr, "[!] Unrecognized option '%s' (abbreviations are disabled).\n\n", raw_arg);
            ui_render_usage();
            exit(EXIT_FAILURE);
        }
    }
}