#ifndef CRAVDATA_CLI_VALIDATE_H
#define CRAVDATA_CLI_VALIDATE_H

#include <stdbool.h>

#include "settings/settings.h"
#include "cli/args.h"

bool validate_raw_list(const RawArgList *list, int argc, int optind, char *const argv[]);
bool validate_logic(const Settings *s);

#endif