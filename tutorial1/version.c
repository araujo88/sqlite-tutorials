#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int main(int argc, char *argv[])
{
    // print sqlite3 version
    printf("SQLite3 version: %s\n", sqlite3_libversion());

    return 0;
}