#include "load_env.h"

int main(){


    loadEnv(".env");


    const char* USER=getenv("USER");
    const char* HOST=getenv("HOST");
    const char* PORT=getenv("PORT");
    const char* DBNAME=getenv("DBNAME");
    const char* PASSWORD=getenv("PASSWORD");

    const char *conninfo = ;

    char conninfo[512];

    snprintf(conninfo, sizeof(conninfo), "host=%s port=%s dbname=%s user=%s password=%s", 
    HOST, DBNAME,USER,PASSWORD);
    
    printf("%s", conninfo);

    
return 0;
}