#ifndef CRAVDATA_CLI_VALIDATE_H
#define CRAVDATA_CLI_VALIDATE_H

#include "settings/settings.h"

int cli_validate_arg_int(const char *arg_val, int optopt_val, int optind_val, char *const argv[], int min_allowed, int max_allowed);
const char* cli_validate_arg_str(const char *optarg, int optopt_val, int optind_val, char *const argv[]);

void cli_validate_settings(const Settings *s);

#endif