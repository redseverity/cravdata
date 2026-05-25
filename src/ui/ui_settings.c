#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "ui/ui_settings.h"

void ui_render_settings(const Settings *s, CravdataMode mode) {
    if (!s->verbose) return;

    typedef enum { T_INT, T_BOOL, T_STRING } Type;
    
    typedef struct { 
        const char *key; 
        const void *value; 
        Type type; 
        bool enabled;
    } ConfigEntry;

    const char *target_val = NULL;
    const char *mode_str = "default";

    // Resolve target and mode strings based on the active execution mode
    if (mode == MODE_HASH) {
        target_val = s->hash.target_hash;
        mode_str = "hash";
    } else if (mode == MODE_FILE) {
        target_val = s->file.target_file;
        mode_str = "file";
    }

    ConfigEntry entries[] = {
        // Required options (Always enabled)
        {"mode",        &mode_str,   T_STRING, true},
        {
            (mode == MODE_HASH) ? "target_hash" : (mode == MODE_FILE ? "target_file" : "target"),  
            &target_val, 
            T_STRING, 
            mode != MODE_DEFAULT
        },
        {"min",         &s->min,     T_INT,    true}, 
        {"max",         &s->max,     T_INT,    true},
        {"threads",     &s->threads, T_INT,    true}, 
        {"charset",     &s->charset, T_STRING, true},
        
        // Optional options (Enabled only if true)
        {"verbose",     &s->verbose, T_BOOL,   s->verbose},
        {"md5",         &s->hash.md5,  T_BOOL,   mode == MODE_HASH && s->hash.md5}
    };

    // Render configuration panel
    printf("── Current Settings ────────\n");
    
    for (size_t i = 0; i < (sizeof(entries) / sizeof(entries[0])); i++) {
        // Skip inactive or disabled flags
        if (!entries[i].enabled) continue;

        printf("   %-13s ", entries[i].key);
        
        switch (entries[i].type) {
            case T_INT:    
                printf("%d\n", *(const int*)entries[i].value); 
                break;
            
            case T_BOOL:   
                printf("%s\n", *(const bool*)entries[i].value ? "true" : "false"); 
                break;

            case T_STRING: {
                const char *str_val = *(const char * const *)entries[i].value;
                if (!str_val) {
                    printf("NULL\n");
                }
                else if (strcmp(entries[i].key, "mode") == 0) {
                    printf("%s\n", str_val);
                } 
                else {
                    printf("\"%s\"\n", str_val);
                }
                break;
            }
        }
    }
    printf("────────────────────────────\n\n");
}