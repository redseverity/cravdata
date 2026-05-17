#include "cli/parser.h"
#include "settings/settings.h"
#include <stdbool.h>

int main(int argc, char *argv[]){
    cli_parse(argc, argv);
    settings_print(settings_get_bool(&settings.verbose));
    return 0;
}