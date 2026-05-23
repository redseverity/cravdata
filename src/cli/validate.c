#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>

#include "cli/args.h"
#include "cli/validate.h"
#include "ui/display.h"
#include "utils/utils.h"

static bool validate_int(const char *arg, int optopt, int optind, char *const argv[], int min_allowed, int max_allowed) {
    char buf[32];
    
    if (arg != NULL && arg[0] == '-' && arg[1] != '\0' && !isdigit((unsigned char)arg[1])) {
        const char *true_flag = NULL;

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
        ui_display_help_usage();
        return false;
    }

    char *end;
    errno = 0;
    long value_long = strtol(arg, &end, 10);
    const char *flag_name = utils_resolve_flag_name(optopt, optind, argv, buf, sizeof(buf));

    if (end == arg || *end != '\0') {
        fprintf(stderr, "[!] Invalid numeric argument '%s' for option '%s'.\n\n", arg, flag_name);
        ui_display_help_usage();
        return false;
    }

    if (errno == ERANGE || value_long < INT_MIN || value_long > INT_MAX) {
        fprintf(stderr, "[!] Option '%s' argument '%s' exceeds integer limits.\n\n", flag_name, arg);
        ui_display_help_usage();
        return false;
    }

    int value = (int)value_long;
    if (value < min_allowed || value > max_allowed) {
        const char *flag_name_range = utils_resolve_flag_name(optopt, optind, argv, buf, sizeof(buf));
        fprintf(stderr, "[!] Option '%s' argument (%d) is out of range (%d-%d).\n\n", flag_name_range, value, min_allowed, max_allowed);
        ui_display_help_usage();
        return false;
    }
    
    return true;
}

static bool validate_str(const char *optarg, int optopt, int optind, char *const argv[]) {
    if (!optarg || optarg[0] == '\0') {
        char buf[32];
        const char *flag_name = utils_resolve_flag_name(optopt, optind, argv, buf, sizeof(buf));
        fprintf(stderr, "[!] Option '%s' argument cannot be empty.\n\n", flag_name);
        ui_display_help_usage();
        return false;
    }
    return true;
}

bool validate_raw_list(const RawArgList *list, int argc, int optind, char *const argv[]) {

    if (optind < argc) {
        fprintf(stderr, "[!] Unexpected extra argument '%s'.\n\n", argv[optind]);
        ui_display_help_usage();
        return false;
    }

    for (int i = 0; i < list->count; i++) {
        char flag = list->args[i].flag;
        const char *val = list->args[i].raw_value;
        int optopt = (int)flag;

        switch (flag) {
            case 'm':
                if (!validate_int(val, optopt, optind, argv, 1, 1000)) {
                    return false;
                }
                break;

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

    return true;
}

bool validate_logic(const Settings *s) {
    if (s->min > s->max) {
        fprintf(stderr, "[!] --min (%d) cannot be greater than --max (%d).\n\n", s->min, s->max);
        ui_display_help_usage();
        return false;
    }
    if (s->charset == NULL) {
        fprintf(stderr, "[!] Missing required option '--charset'.\n\n");
        ui_display_help_usage();
        return false;
    }
    return true;
}