#ifndef SETTINGS_SETTINGS_H
#define SETTINGS_SETTINGS_H

#include <stdbool.h>

int settings_get_min(void);
int settings_get_max(void);
int settings_get_threads(void);
bool settings_get_md5(void);
bool settings_get_verbose(void);
bool settings_get_help(void);
const char* settings_get_charset(void);

void settings_set_min(int min_value);
void settings_set_max(int max_value);
void settings_set_threads(int threads_value);
void settings_set_md5(bool md5_flag);
void settings_set_verbose(bool verbose_flag);
void settings_set_help(bool help_flag);
void settings_set_charset(const char *charset_value);

#endif