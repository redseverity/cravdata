#ifndef CRAVDATA_CLI_UTILS_H
#define CRAVDATA_CLI_UTILS_H

#include <stddef.h>
#include <getopt.h>

#include "cli/args.h"

const char* utils_resolve_flag_name(int optopt_val, int optind_val, char *const argv[], char *buffer, size_t buf_len);
void utils_disable_abbreviations(int longindex, int optind, char *const argv[], const struct option *cli_options);

#endif