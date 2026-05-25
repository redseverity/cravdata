#ifndef CRAVDATA_CLI_VALIDATE_H
#define CRAVDATA_CLI_VALIDATE_H

#include <stdbool.h>

#include "settings/settings.h"
#include "cli/args.h"
#include "cli/router.h"

bool cli_validate_syntax(int argc, int optind, char *const argv[], const RawArgs *array, CravdataMode mode);
bool cli_validate_logic(const Settings *s, CravdataMode mode);

#endif