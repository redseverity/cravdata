#include "cli/parser.h"
#include "cli/validate.h"
#include "settings/settings.h"
#include "ui/display.h"

int main(int argc, char *argv[]){
    cli_parse(argc, argv, &settings);
    cli_validate_settings(&settings);
    ui_display_setting(&settings);
    return 0;
}