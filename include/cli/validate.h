#ifndef CRAVDATA_CLI_VALIDATE_H
#define CRAVDATA_CLI_VALIDATE_H

int cli_validate_int(const char *value_str, int min_allowed, int max_allowed, const char *name);
const char* cli_validate_string(const char *value_str);

#endif