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

void args_list_init(RawArgList *list);
void args_list_add(RawArgList *list, char flag, const char *value);
void args_list_free(RawArgList *list);

#endif