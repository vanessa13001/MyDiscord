#include "load_env.h"

void loadEnv(const char* filename){
    FILE* file=fopen(filename, "r");
    if (!file){
        perror("cannot open .env file");
        return;
    }

    char line[512];
    while (fgets(line, sizeof(line), file)){
        if (line[0] =='\n'){
            continue;
        }

        char* equal_sign = strchr(line, '=');
        if (!equal_sign){
            continue;
        }

        *equal_sign = '\0';
        char* key = line;
        char* value= equal_sign+1;

        size_t length=strlen(value);
        if (length && value[length-1]=='\n'){
            value[length-1]='\0';
        }

        _putenv_s(key,value);
    }

    fclose(file);
}