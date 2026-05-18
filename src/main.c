#include "cli/parser.h"
#include "cli/validate.h"
#include "settings/settings.h"

int main(int argc, char *argv[]){
    cli_parse(argc, argv);
    cli_validate_settings();
    settings_print(settings_get_bool(&settings.verbose));
    return 0;
}