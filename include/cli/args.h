#ifndef CRAVDATA_CLI_ARGS_H
#define CRAVDATA_CLI_ARGS_H

typedef struct {
    char flag;
    char *raw_value;
} RawArg;

typedef struct args {
    int count;
    int capacity;
    RawArg *args;
} RawArgList;

void list_args_init(RawArgList *list);
void list_args_add(RawArgList *list, char flag, const char *value);
void list_args_free(RawArgList *list);

#endif