#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>
#include "cli/help.h"

#include "cli/validate.h"

// Helper to ensure the string is not empty
static void check_empty(const char *str) {
    if (!str || strlen(str) == 0) {
        fprintf(stderr, "Value cannot be empty\n\n");
        cli_help();
        exit(EXIT_FAILURE);
    }
}

// Helper to parse string into int safely
static int parse_int(const char *str) {
    char *end;
    errno = 0;

    long value = strtol(str, &end, 10);

    // No digits found
    if (end == str) {
        fprintf(stderr, "No digits found\n\n");
        cli_help();
        exit(EXIT_FAILURE);
    }

    // Extra characters after number
    if (*end != '\0') {
        fprintf(stderr, "Invalid characters in number\n\n");
        cli_help();
        exit(EXIT_FAILURE);
    }

    // Overflow or underflow
    if (errno == ERANGE) {
        fprintf(stderr, "Integer out of range\n\n");
        cli_help();
        exit(EXIT_FAILURE);
    }

    return (int)value;
}

// Helper to validate that integer is within allowed range
static void check_range(int value, int min_allowed, int max_allowed, const char *name) {
    if (value < min_allowed || value > max_allowed) {
        fprintf(stderr, "Invalid %s: expected %d-%d, got %d\n\n",
            name, min_allowed, max_allowed, value);
        cli_help();
        exit(EXIT_FAILURE);
    }
}

// Validate integer string, parse, and clamp
int cli_validate_int(const char *value_str, int min_allowed, int max_allowed, const char *name) {
    check_empty(value_str);
    int value = parse_int(value_str);
    check_range(value, min_allowed, max_allowed, name);
    return value;
}

// Validate string is non-empty
const char* cli_validate_string(const char *value_str) {
    check_empty(value_str);
    return value_str;
}