#include <stdio.h>
#include <stdbool.h>

#include "ui/display.h"
#include "settings/settings.h"

void ui_display_help(void) {
    fprintf(stdout,
        "Cravdata is a CPU-bound generative brute-force tool written in C.\n\n"
        "Usage:\n"
        "  cravdata [options]\n\n"
        "Options:\n"
        "  -m, --min <length>      Minimum password/path length\n"
        "  -x, --max <length>      Maximum password/path length\n"
        "  -t, --threads <num>     Number of CPU threads to use\n"
        "  -c, --charset <str>     Charset to use in generation\n"
        "  -1, --md5               Enable MD5 attack mode\n"
        "  -v, --verbose           Enable verbose output\n"
        "  -h, --help              Display this help menu\n\n"
        "For more information, bugs, and updates visit:\n"
        "  https://github.com/redseverity/cravdata"
    );
}

void ui_display_help_usage(void) {
    fprintf(stderr, "Try 'cravdata --help' for more information.\n\n");
}

void ui_display_setting(const Settings *s) {
    if (!s->verbose) return;

    typedef enum { T_INT, T_BOOL, T_STRING } Type;
    typedef struct { const char *key; const void *value; Type type; } ConfigEntry;

    ConfigEntry entries[] = {
        {"min",     &s->min,     T_INT}, 
        {"max",     &s->max,     T_INT},
        {"threads", &s->threads, T_INT}, 
        {"charset", &s->charset, T_STRING},
        {"md5",     &s->md5,     T_BOOL}, 
        {"verbose", &s->verbose, T_BOOL},
    };

    printf("\n••• CURRENT SETTINGS •••\n");
    for (size_t i = 0; i < (sizeof(entries) / sizeof(entries[0])); i++) {
        printf("[✓] %-8s : ", entries[i].key);
        switch (entries[i].type) {
            case T_INT:    
                printf("%i\n", *(const int*)entries[i].value); 
                break;
            
            case T_BOOL:   
                printf("%s\n", *(const bool*)entries[i].value ? "true" : "false"); 
                break;

            case T_STRING: {
                const char *str_val = *(const char * const *)entries[i].value;
                printf("%s\n", str_val ? str_val : "NULL"); 
                break;
            }
        }
    }
    printf("••••••••••••••••••••••••\n");
}