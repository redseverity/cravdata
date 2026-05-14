from utils.runner import run
from utils.ansi import RED, GREEN, BOLD, RESET, WHITE, PURPLE
from utils.binary_path import BINARY

def return_status(description: str, output_code: int):

    if not hasattr(return_status, "operation_number"):
        return_status.operation_number = 0

    return_status.operation_number += 1
    operation_number = return_status.operation_number

    if output_code != 0:
        print(f"{PURPLE}{BOLD}[{operation_number}] {WHITE}{description}: {RED}FAILED{RESET}")
        return

    print(f"{PURPLE}{BOLD}[{operation_number}] {WHITE}{description}: {GREEN}PASS{RESET}")


# argument test cases
ARG_TESTS = [

    # short flags
    ("Short flag -m", ["-m", "1"]),
    ("Short flag -x", ["-x", "5"]),
    ("Short flag -t", ["-t", "4"]),
    ("Short flag -1", ["-1"]),
    ("Short flag -v", ["-v"]),
    ("Short flag -h", ["-h"]),

    # long flags
    ("Long flag --min", ["--min", "1"]),
    ("Long flag --max", ["--max", "5"]),
    ("Long flag --threads", ["--threads", "4"]),
    ("Long flag --md5", ["--md5"]),
    ("Long flag --verbose", ["--verbose"]),
    ("Long flag --help", ["--help"]),
]


def test():
    print(f"{PURPLE}{BOLD}▶ Running args{RESET}\n")
    for description, args in ARG_TESTS:
        result = run([BINARY] + args)
        return_status(description, result.returncode)
