#include <stdio.h>

#include "ui/ui_help.h"

void ui_render_usage(void) {
    fprintf(stdout, "Try 'cravdata --help' for more information.\n");
}

void ui_render_help(const CravdataMode mode) {
    if (mode == MODE_HASH) {
        fprintf(stdout,
            "Cravdata - Hash Cracking Mode\n\n"
            "Usage:\n"
            "  cravdata hash [options] <target_hash>\n\n"
            "Hash Options:\n"
            "  -1, --md5               Assume the target hash is MD5\n\n"
            "Global Options:\n"
            "  -m, --min <length>      Minimum password length (default: 1)\n"
            "  -x, --max <length>      Maximum password length (default: 3)\n"
            "  -t, --threads <num>     Number of CPU threads to use (default: 1)\n"
            "  -c, --charset <str>     Charset to use in generation\n"
            "  -v, --verbose           Enable verbose output\n"
            "  -h, --help              Display this help menu\n\n"
            "For more information, bugs, and updates visit:\n"
            "  https://github.com/redseverity/cravdata\n"
        );
    } 
    else if (mode == MODE_FILE) {
        fprintf(stdout,
            "Cravdata - File Cracking Mode\n\n"
            "Usage:\n"
            "  cravdata file [options] <target_file>\n\n"
            "Global Options:\n"
            "  -m, --min <length>      Minimum path length (default: 1)\n"
            "  -x, --max <length>      Maximum path length (default: 3)\n"
            "  -t, --threads <num>     Number of CPU threads to use (default: 1)\n"
            "  -c, --charset <str>     Charset to use in generation\n"
            "  -v, --verbose           Enable verbose output\n"
            "  -h, --help              Display this help menu\n\n"
            "For more information, bugs, and updates visit:\n"
            "  https://github.com/redseverity/cravdata\n"
        );
    } 
    else {
        // (MODE_DEFAULT)
        fprintf(stdout,
            "Cravdata is a CPU-bound generative brute-force tool.\n\n"
            "Usage:\n"
            "  cravdata [options]              (Runs in default generation mode)\n"
            "  cravdata <command> [options]    (Runs in a specific mode)\n\n"
            "Commands:\n"
            "  hash                    Perform hash cracking attacks\n"
            "  file                    Perform file cracking attacks\n\n"
            "Global Options:\n"
            "  -m, --min <length>      Minimum password/path length (default: 1)\n"
            "  -x, --max <length>      Maximum password/path length (default: 3)\n"
            "  -t, --threads <num>     Number of CPU threads to use (default: 1)\n"
            "  -c, --charset <str>     Charset to use in generation\n"
            "  -v, --verbose           Enable verbose output\n"
            "  -h, --help              Display this help menu\n\n"
            "Note:\n"
            "  If no command is specified, Cravdata defaults uses default generation.\n"
            "  Use \"cravdata [command] --help\" for more information about a specific mode.\n\n"
            "For more information, bugs, and updates visit:\n"
            "  https://github.com/redseverity/cravdata\n"
        );
    }
}