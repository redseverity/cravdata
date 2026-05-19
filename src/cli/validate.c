#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>

#include "ui/display.h"
#include "cli/validate.h"

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>

#include "ui/display.h"
#include "cli/validate.h"

// Helper to dynamically resolve the correct flag name (handles short, long, and empty arg offsets)
static const char* resolve_flag_name(int optopt_val, int optind_val, char *const argv[], char *buffer, size_t buf_len) {
    if (optopt_val != 0) {
        snprintf(buffer, buf_len, "-%c", optopt_val);
        return buffer;
    }
    
    const char *flag_name = argv[optind_val - 1];
    // If the index points to an empty argument or the value itself, the real flag is one step behind
    if ((flag_name[0] == '\0' || flag_name[0] != '-') && optind_val > 2) {
        flag_name = argv[optind_val - 2];
    }
    
    return flag_name;
}

// Helper to parse string into int safely with dynamic context-aware errors
static int parse_int(const char *str, int optopt_val, int optind_val, char *const argv[]) {
    char *end;
    errno = 0;

    long value = strtol(str, &end, 10);
    
    // Resolve flag name dynamically
    char buf[32];
    const char *arg_name = resolve_flag_name(optopt_val, optind_val, argv, buf, sizeof(buf));

    // No digits found (e.g., --threads "abc")
    if (end == str) {
        fprintf(stderr, "[!] Error: Argument '%s' must be a valid number (no digits found in '%s').\n\n", 
                arg_name, str);
        ui_display_help_usage();
        exit(EXIT_FAILURE);
    }

    // Extra characters after number (e.g., --threads "4ade")
    if (*end != '\0') {
        fprintf(stderr, "[!] Error: Argument '%s' contains invalid characters in '%s'.\n\n", 
                arg_name, str);
        ui_display_help_usage();
        exit(EXIT_FAILURE);
    }

    // Overflow or underflow (e.g., --threads "99999999999999")
    if (errno == ERANGE || value < INT_MIN || value > INT_MAX) {
        fprintf(stderr, "[!] Error: Argument '%s' value '%s' exceeds integer limits.\n\n", 
                arg_name, str);
        ui_display_help_usage();
        exit(EXIT_FAILURE);
    }

    return (int)value;
}

// Dynamically validates integer bounds
int cli_validate_arg_int(const char *arg_val, int optopt_val, int optind_val, char *const argv[], int min_allowed, int max_allowed) {
    int value = parse_int(arg_val, optopt_val, optind_val, argv);
    
    if (value < min_allowed || value > max_allowed) {
        char buf[32];
        const char *arg_name = resolve_flag_name(optopt_val, optind_val, argv, buf, sizeof(buf));
        
        fprintf(stderr, "[!] Error: Argument '%s' value (%d) is out of bounds (allowed range: %d-%d).\n\n",
                arg_name, value, min_allowed, max_allowed);
        ui_display_help_usage();
        exit(EXIT_FAILURE);
    }
    return value;
}

// Dynamically validates that string is non-empty
const char* cli_validate_arg_str(const char *optarg, int optopt_val, int optind_val, char *const argv[]) {
    if (!optarg || optarg[0] == '\0') {
        char buf[32];
        const char *arg_name = resolve_flag_name(optopt_val, optind_val, argv, buf, sizeof(buf));
        
        fprintf(stderr, "[!] Error: Argument '%s' cannot be empty.\n\n", arg_name);
        ui_display_help_usage();
        exit(EXIT_FAILURE);
    }
    return optarg;
}

// === Business Rules Validation ===
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