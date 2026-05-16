#include "cli/parser.h"
#include "settings/settings.h"

int main(int argc, char *argv[]){
    parse(argc, argv);
    settings_print();
    return 0;
}