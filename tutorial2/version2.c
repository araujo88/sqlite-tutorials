#include <sqlite3.h>
#include <stdlib.h>
#include <stdio.h>

void check_database(int rc, sqlite3 *db);
void check_statement(int rc, sqlite3 *db);

int main(void) 
{
    // database handle
    sqlite3 *db;

    // SQL statement
    sqlite3_stmt *res;
    
    // new database connection (database name and handle - in memory database)
    int rc = sqlite3_open(":memory:", &db);
    
    // checks if connection was successfuly established
    check_database(rc, db);
    
    // compiles the SQL statement into byte-code
    rc = sqlite3_prepare_v2(db, "SELECT SQLITE_VERSION()", -1, &res, 0);    
    
    // checks if data was successfuly fetched
    check_statement(rc, db);
    
    // runs the SQL statement
    rc = sqlite3_step(res);
    
    // prints data from query
    if (rc == SQLITE_ROW) {
        printf("%s\n", sqlite3_column_text(res, 0));
    }
    
    // destroys the statement object
    sqlite3_finalize(res);
    
    // closes database connection
    sqlite3_close(db);
    
    return 0;
}

void check_database(int rc, sqlite3 *db)
{
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        exit(EXIT_FAILURE);
    }
}

void check_statement(int rc, sqlite3 *db)
{
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        exit(EXIT_FAILURE);
    }    
}
