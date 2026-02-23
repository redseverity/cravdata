#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "settings/settings.h"

int min = 1;
int max = 3;
int threads = 1;
bool md5 = false;
bool verbose = false;
bool help = false;
char *charset = NULL;

int settings_get_min(void)             { return min; }
int settings_get_max(void)             { return max; }
int settings_get_threads(void)         { return threads; }
bool settings_get_md5(void)            { return md5; }
bool settings_get_verbose(void)        { return verbose; }
bool settings_get_help(void)           { return help; }
const char* settings_get_charset(void) { return charset; } // const to prevent external modification

void settings_set_min(int min_value)         { min = min_value; }
void settings_set_max(int max_value)         { max = max_value; }
void settings_set_threads(int threads_value) { threads = threads_value; }
void settings_set_md5(bool md5_flag)         { md5 = md5_flag; }
void settings_set_verbose(bool verbose_flag) { verbose = verbose_flag; }
void settings_set_help(bool help_flag)       { help = help_flag; }

void settings_set_charset(const char *charset_value) {
    if (!charset_value) return;

    char *tmp = malloc(strlen(charset_value) + 1);
    if (!tmp) return;
    
    strcpy(tmp, charset_value);

    free(charset);
    charset = tmp;
}