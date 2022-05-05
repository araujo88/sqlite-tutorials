#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

void check_connection(int rc, sqlite3 *db);
void check_sql(int rc, sqlite3 *db, char *err_msg);

int main(void)
{
    sqlite3 *db;
    char *err_msg;

    int rc = sqlite3_open(":memory:",  &db);

    check_connection(rc, db);

    char *sql = "CREATE TABLE Friends(Id INTEGER PRIMARY KEY, Name TEXT);"
    "INSERT INTO Friends(Name) VALUES ('Tom');"
    "INSERT INTO Friends(Name) VALUES ('Rebecca');"
    "INSERT INTO Friends(Name) VALUES ('Jim');"
    "INSERT INTO Friends(Name) VALUES ('Roger');"
    "INSERT INTO Friends(Name) VALUES ('Robert');";

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    check_sql(rc, db, err_msg);

    int last_id = sqlite3_last_insert_rowid(db);
    printf("The last id of the inserted row is %d\n", last_id);

    sqlite3_close(db);

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

