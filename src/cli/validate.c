#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>

#include "ui/display.h"
#include "cli/validate.h"
#include "utils/utils.h"

// Parses string to integer with strict error handling and flag collision checks
static int parse_int(const char *str, int optopt_val, int optind_val, char *const argv[]) {
    char *end;
    errno = 0;

    long value = strtol(str, &end, 10);
    
    // Resolve flag name dynamically
    char buf[32];
    const char *flag_name = utils_resolve_flag_name(optopt_val, optind_val, argv, buf, sizeof(buf));

    // No digits found (e.g., --threads "abc")
    if (end == str) {
        fprintf(stderr, "[!] Error: Argument '%s' must be a valid number (no digits found in '%s').\n\n", 
                flag_name, str);
        ui_display_help_usage();
        exit(EXIT_FAILURE);
    }

    // Extra characters after number (e.g., --threads "4ade")
    if (*end != '\0') {
        fprintf(stderr, "[!] Error: Argument '%s' contains invalid characters in '%s'.\n\n", 
                flag_name, str);
        ui_display_help_usage();
        exit(EXIT_FAILURE);
    }

    // Overflow or underflow (e.g., --threads "99999999999999")
    if (errno == ERANGE || value < INT_MIN || value > INT_MAX) {
        fprintf(stderr, "[!] Error: Argument '%s' value '%s' exceeds integer limits.\n\n", 
                flag_name, str);
        ui_display_help_usage();
        exit(EXIT_FAILURE);
    }

    return (int)value;
}

// Validates integer value against allowed limits with flag collision checks
int cli_validate_arg_int(const char *arg_val, int optopt_val, int optind_val, char *const argv[], int min_allowed, int max_allowed) {
    char buf[32];
    
    if (arg_val != NULL && arg_val[0] == '-' && arg_val[1] != '\0' && !isdigit((unsigned char)arg_val[1])) {
        
        const char *true_flag = NULL;
        for (int i = optind_val; i >= 0; i--) {
            if (argv[i] != NULL && argv[i] == arg_val) {
                if (i > 0 && argv[i - 1] != NULL && argv[i - 1][0] == '-') {
                    true_flag = argv[i - 1];
                    break;
                }
            }
        }
        
        if (true_flag == NULL) {
            true_flag = utils_resolve_flag_name(optopt_val, optind_val, argv, buf, sizeof(buf));
        }
        
        fprintf(stderr, "[!] Error: Option '%s' requires a numeric argument, but received '%s' (looks like another option).\n\n",
                true_flag, arg_val);
        ui_display_help_usage();
        exit(EXIT_FAILURE);
    }

    int value = parse_int(arg_val, optopt_val, optind_val, argv);
    
    if (value < min_allowed || value > max_allowed) {
        const char *flag_name = utils_resolve_flag_name(optopt_val, optind_val, argv, buf, sizeof(buf));
        
        fprintf(stderr, "[!] Error: Argument '%s' value (%d) is out of bounds (allowed range: %d-%d).\n\n",
                flag_name, value, min_allowed, max_allowed);
        ui_display_help_usage();
        exit(EXIT_FAILURE);
    }
    
    return value;
}

// Validates non-empty string
const char* cli_validate_arg_str(const char *optarg, int optopt_val, int optind_val, char *const argv[]) {
    if (!optarg || optarg[0] == '\0') {
        char buf[32];
        const char *flag_name = utils_resolve_flag_name(optopt_val, optind_val, argv, buf, sizeof(buf));
        
        fprintf(stderr, "[!] Error: Argument '%s' cannot be empty.\n\n", flag_name);
        ui_display_help_usage();
        exit(EXIT_FAILURE);
    }
    return optarg;
}

// Validates logical conflicts and mandatory parameters
void cli_validate_settings(const Settings *s) {
    if (s->min > s->max) {
        fprintf(stderr, "[!] Error: --min (%d) cannot be greater than --max (%d).\n\n", s->min, s->max);
        ui_display_help_usage();
        exit(EXIT_FAILURE);
    }

    if (s->charset == NULL) {
        fprintf(stderr, "[!] Error: Missing required argument '--charset'.\n\n");
        ui_display_help_usage();
        exit(EXIT_FAILURE);
    }
}