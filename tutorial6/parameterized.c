#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int callback(void *NotUsed, int argc, char **argv, char **azColName);
void check_connection(int rc, sqlite3 *db);
void check_statement(int rc, sqlite3 *db, sqlite3_stmt *res);
void check_sql(int rc, sqlite3 *db, char *err_msg);

int main(void)
{
    sqlite3 *db;
    sqlite3_stmt *res;

    int rc = sqlite3_open("test.db", &db);

    check_connection(rc, db);

    char *sql = "SELECT Id, Name FROM Cars WHERE Id = ?";

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    check_statement(rc, db, res);

    int step = sqlite3_step(res);

    if (step == SQLITE_ROW) {
        printf("%s: ", sqlite3_column_text(res, 0));
        printf("%s: \n", sqlite3_column_text(res, 1));
    }

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

void check_statement(int rc, sqlite3 *db, sqlite3_stmt *res)
{
    if (rc == SQLITE_OK) {
        sqlite3_bind_int(res, 1, 3);
    }
    else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
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
