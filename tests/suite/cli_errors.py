from utils.runner import run
from utils.binary_path import BINARY
from .cli_args import return_status


CLI_ERRORS_TESTS = [
    # =========================================================================
    # PARSER.C ERRORS
    # =========================================================================
    (
        "Parser: Usage info when no arguments are passed",
        [],
        1
    ),
    (
        "Parser: Disabled abbreviation detection for long flags",
        ["--h"],
        1
    ),
    (
        "Parser: Flag requiring an argument passed with nothing",
        ["-c"],
        1
    ),
    (
        "Parser: Unrecognized short option format",
        ["-wrongflag"],
        1
    ),
    (
        "Parser: Unrecognized long option format",
        ["--wrongflag"],
        1
    ),
    (
        "Parser: Positional/extra argument unexpected",
        ["wrongflag"],
        1
    ),

    # =========================================================================
    # VALIDATE.C ERRORS
    # =========================================================================
    (
        "Validate: Invalid mixed alphanumeric integer argument",
        ["-t", "123abc"],
        1
    ),
    (
        "Validate: Numeric argument exceeding INT limits (overflow)",
        ["-t", "9999999999"],
        1
    ),
    (
        "Validate: Option collision (missing numeric argument, got next flag)",
        ["-t", "-v"],
        1
    ),
    (
        "Validate: Value out of allowed range (1-256)",
        ["-t", "-9"],
        1
    ),
    (
        "Validate: Prevent empty string as argument",
        ["-c", ""],
        1
    ),
    (
        "Validate: Business logic rule (--min greater than --max)",
        ["--min", "20", "--max", "10"],
        1
    ),
    (
        "Validate: Missing required option dependency (--charset)",
        ["-v"],
        1
    ),
]

def test():
    for description, args, expected_code in CLI_ERRORS_TESTS:
        result = run([BINARY] + args)
        return_status(description, result.returncode, expected_code)