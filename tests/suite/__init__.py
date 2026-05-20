from . import cli_args
from . import cli_errors
from utils.ansi import PURPLE, BOLD, RESET

def run():
    print(f"{PURPLE}{BOLD}▶ Running functional arguments{RESET}\n")
    cli_args.test()

    print(f"\n{PURPLE}{BOLD}▶ Running CLI Errors (Validation){RESET}\n")
    cli_errors.test()