#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int callback(void *NotUsed, int argc, char **argv, char **azColName);
void check_connection(int rc, sqlite3 *db);
void check_sql(int rc, sqlite3 *db, char *err_msg);

int main(void)
{
    sqlite3 *db;
    char *err_msg;

    int rc = sqlite3_open("test.db", &db);

    check_connection(rc, db);

    char *sql = "SELECT * FROM Cars";

    rc = sqlite3_exec(db, sql, callback, 0, &err_msg);

    check_sql(rc, db, err_msg);

    sqlite3_close(db);

    return 0;
}

int callback(void *NotUsed, int argc, char *argv[], char *azColName[])
{
    NotUsed = NULL;

    for (int i = 0; i < argc; i++) 
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");

    return 0;
}

void check_connection(int rc, sqlite3 *db)
{
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        exit(EXIT_FAILURE);
    }
}

void check_sql(int rc, sqlite3 *db, char *err_msg)
{
    if (rc != SQLITE_OK) 
    {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        
        exit(EXIT_FAILURE);
    }
    else {
        fprintf(stdout, "SQL query executed successfuly\n");
    }
}
