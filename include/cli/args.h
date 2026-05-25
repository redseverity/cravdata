#ifndef CRAVDATA_CLI_ARGS_H
#define CRAVDATA_CLI_ARGS_H

typedef struct {
    char flag;
    char *raw_value;
} RawArg;

typedef struct args {
    int count;
    int capacity;
    RawArg *items;
} RawArgs;

void cli_args_init(RawArgs *array);
void cli_args_add(RawArgs *array, char flag, const char *value);
void cli_args_free(RawArgs *array);

#endif