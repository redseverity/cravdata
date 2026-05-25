#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>

#include "cli/validate.h"

#include "ui/ui_help.h"
#include "utils/utils.h"

// Check if flag argument is a valid integer within a specific range
static bool validate_int(const char *arg, int optopt, int optind, char *const argv[], int min_allowed, int max_allowed) {
    char buf[32];
    
    if (arg != NULL && arg[0] == '-' && arg[1] != '\0' && !isdigit((unsigned char)arg[1])) {
        const char *true_flag = NULL;

        // Detect if the user passed another flag instead of a number
        for (int i = optind; i >= 0; i--) {
            if (argv[i] != NULL && argv[i] == arg) {
                if (i > 0 && argv[i - 1] != NULL && argv[i - 1][0] == '-') {
                    true_flag = argv[i - 1];
                    break;
                }
            }
        }

        if (true_flag == NULL) {
            true_flag = utils_resolve_flag_name(optopt, optind, argv, buf, sizeof(buf));
        }
        
        fprintf(stderr, "[!] Option '%s' requires a numeric argument (received '%s').\n\n", true_flag, arg);
        ui_render_usage();
        return false;
    }

    char *end;
    errno = 0;
    long value_long = strtol(arg, &end, 10);
    const char *flag_name = utils_resolve_flag_name(optopt, optind, argv, buf, sizeof(buf));

    // Basic syntax and overflow checks
    if (end == arg || *end != '\0') {
        fprintf(stderr, "[!] Invalid numeric argument '%s' for option '%s'.\n\n", arg, flag_name);
        ui_render_usage();
        return false;
    }

    if (errno == ERANGE || value_long < INT_MIN || value_long > INT_MAX) {
        fprintf(stderr, "[!] Option '%s' argument '%s' exceeds integer limits.\n\n", flag_name, arg);
        ui_render_usage();
        return false;
    }

    int value = (int)value_long;
    if (value < min_allowed || value > max_allowed) {
        const char *flag_name_range = utils_resolve_flag_name(optopt, optind, argv, buf, sizeof(buf));
        fprintf(stderr, "[!] Option '%s' argument (%d) is out of range (%d-%d).\n\n", flag_name_range, value, min_allowed, max_allowed);
        ui_render_usage();
        return false;
    }
    
    return true;
}

// Ensure string arguments are not empty
static bool validate_str(const char *optarg, int optopt, int optind, char *const argv[]) {
    if (!optarg || optarg[0] == '\0') {
        char buf[32];
        const char *flag_name = utils_resolve_flag_name(optopt, optind, argv, buf, sizeof(buf));
        fprintf(stderr, "[!] Option '%s' argument cannot be empty.\n\n", flag_name);
        ui_render_usage();
        return false;
    }
    return true;
}

bool cli_validate_syntax(int argc, int optind, char *const argv[], const RawArgs *array, CravdataMode mode) {

    // 1. Validate key-value flags from raw arguments array
    for (int i = 0; i < array->count; i++) {
        char flag = array->items[i].flag;
        const char *val = array->items[i].raw_value;
        int optopt = (int)flag;

        switch (flag) {
            case 'm':
            case 'x':
                if (!validate_int(val, optopt, optind, argv, 1, 1000)) {
                    return false;
                }
                break;

            case 't':
                if (!validate_int(val, optopt, optind, argv, 1, 256)) {
                    return false;
                }
                break;

            case 'c':
                if (!validate_str(val, optopt, optind, argv)) {
                    return false;
                }
                break;

            default:
                break;
        }
    }

    // 2. Validate mandatory positional arguments based on mode
    if (mode == MODE_HASH) {
        if (optind >= argc) {
            fprintf(stderr, "[!] Missing required argument: <target_hash>.\n\n");
            ui_render_usage();
            return false;
        }
        if (argv[optind][0] == '\0') {
            fprintf(stderr, "[!] Target hash cannot be empty.\n\n");
            ui_render_usage();
            return false;
        }
    } 
    else if (mode == MODE_FILE) {
        if (optind >= argc) {
            fprintf(stderr, "[!] Missing required argument: <target_file>.\n\n");
            ui_render_usage();
            return false;
        }
        if (argv[optind][0] == '\0') {
            fprintf(stderr, "[!] Target file path cannot be empty.\n\n");
            ui_render_usage();
            return false;
        }
    }

    // 3. Check for unexpected trailing arguments
    int expected_args = (mode != MODE_DEFAULT) ? 1 : 0;
    if ((argc - optind) > expected_args) {
        fprintf(stderr, "[!] Unexpected extra argument '%s'.\n\n", argv[optind + expected_args]);
        ui_render_usage();
        return false;
    }

    return true;
}

bool cli_validate_logic(const Settings *s, CravdataMode mode) {
    // Check for inconsistent parameter values
    if (s->min > s->max) {
        fprintf(stderr, "[!] Option '--min / -m' cannot be greater than '--max / -x' (%d > %d).\n\n", s->min, s->max);
        ui_render_usage();
        return false;
    }
    if (s->charset == NULL) {
        fprintf(stderr, "[!] Missing required option '--charset / -c'.\n\n");
        ui_render_usage();
        return false;
    }

    // Ensure mode-specific flags are not used out of context
    if (s->hash.md5 && mode != MODE_HASH) {
            fprintf(stderr, "[!] Option '--md5 / -1' is only valid in 'hash' mode.\n\n");
            ui_render_usage();
            return false;
    }

    return true;
}