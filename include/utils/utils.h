#ifndef CRAVDATA_CLI_UTILS_H
#define CRAVDATA_CLI_UTILS_H

#include <stddef.h>

const char* utils_resolve_flag_name(int optopt_val, int optind_val, char *const argv[], char *buffer, size_t buf_len);

#endif