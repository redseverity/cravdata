from utils.runner import run
from utils.ansi import RED, GREEN, BOLD, RESET, WHITE, PURPLE
from utils.binary_path import BINARY

def return_status(description: str, actual_code: int, expected_code: int):
    # Initialize static function variable for test counting
    if not hasattr(return_status, "operation_number"):
        return_status.operation_number = 0

    return_status.operation_number += 1
    operation_number = return_status.operation_number

    # Evaluate execution result against expectation
    if actual_code != expected_code:
        print(f"{PURPLE}{BOLD}[{operation_number}] {WHITE}{description}: {RED}FAILED{RESET} (Expected {expected_code}, got {actual_code})")
        return

    print(f"{PURPLE}{BOLD}[{operation_number}] {WHITE}{description}: {GREEN}PASS{RESET}")


# Successful execution baselines (Requires mandatory -c/--charset)
ARG_TESTS = [
    # Minimum required argument to execute successfully
    ("Short flag -c (Required)", ["-c", "abcdef"], 0),
    ("Long flag --charset (Required)", ["--charset", "abcdef"], 0),

    # Short options combined with mandatory charset
    ("Short flag -m with charset", ["-m", "1", "-c", "abc"], 0),
    ("Short flag -x with charset", ["-x", "5", "-c", "abc"], 0),
    ("Short flag -t with charset", ["-t", "4", "-c", "abc"], 0),
    ("Short flag -1 with charset", ["-1", "-c", "abc"], 0),
    ("Short flag -v with charset", ["-v", "-c", "abc"], 0),

    # Long options combined with mandatory charset
    ("Long flag --min with charset", ["--min", "1", "-c", "abc"], 0),
    ("Long flag --max with charset", ["--max", "5", "-c", "abc"], 0),
    ("Long flag --threads with charset", ["--threads", "4", "-c", "abc"], 0),
    ("Long flag --md5 with charset", ["--md5", "-c", "abc"], 0),
    ("Long flag --verbose with charset", ["--verbose", "-c", "abc"], 0),

    # Global options that bypass standard input validation
    ("Short flag -h (Help menu)", ["-h"], 0),
    ("Long flag --help (Help menu)", ["--help"], 0),
]


def test():
    # Execute and validate each functional CLI scenario
    for description, args, expected_code in ARG_TESTS:
        result = run([BINARY] + args)
        return_status(description, result.returncode, expected_code)