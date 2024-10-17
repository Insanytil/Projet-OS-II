#include "lib/global.h"
#include <stdio.h>
#include <string.h>

char chemin_sauvegarde[256] = "";
char save_name[256] = "";

void sanitize_filename(char* filename) {
    char* dot = strrchr(filename, '.');  
    if (dot != NULL && strcmp(dot, ".csv") == 0) {
        *dot = '\0';  
    }
}