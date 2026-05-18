#ifndef CRAVDATA_CLI_VALIDATE_H
#define CRAVDATA_CLI_VALIDATE_H

int cli_validate_arg_int(const char *value_str, int min_allowed, int max_allowed, const char *name);
const char* cli_validate_arg_str(const char *value_str);

void cli_validate_settings(void);

#endif