#include <stdio.h>
#include <string.h>
#include "utils/utils.h"

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