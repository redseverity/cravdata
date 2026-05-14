from os import system
import sys
sys.dont_write_bytecode = True

from suite import args
from utils.ansi import BOLD, RESET, BLUE
from utils.timer import Timer

def main():
    system("clear")
    print(f"\n{BLUE}{BOLD}[INFO] Starting Test Suite{RESET}\n")

    time = Timer()
    time.start()
    args.test()
    time.stop()
    time.show()

    print(f"\n{BLUE}{BOLD}[INFO] Test Suite Finished{RESET}")

if __name__ == "__main__":
    main()