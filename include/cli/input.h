#ifndef CRAVDATA_CLI_INPUT_H
#define CRAVDATA_CLI_INPUT_H

#include "cli/args.h"
#include "cli/router.h"

void cli_input_args(int argc, char *argv[], RawArgs *array, CravdataMode mode);

#endif