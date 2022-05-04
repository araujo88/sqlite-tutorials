#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

void check_connection(int rc, sqlite3 *db);
void check_query(int rc, sqlite3 *db, char *err_msg);

int main(int argc, char *argv[])
{
    sqlite3 *db;
    char *err_msg = (char) 0;

    // create connection to the database
    int rc = sqlite3_open("test.db", &db);

    check_connection(rc, db);

    // SQL statement
    char *sql = "DROP TABLE IF EXISTS Cars;" 
                "CREATE TABLE Cars(Id INT, Name TEXT, Price INT);" 
                "INSERT INTO Cars VALUES(1, 'Audi', 52642);" 
                "INSERT INTO Cars VALUES(2, 'Mercedes', 57127);" 
                "INSERT INTO Cars VALUES(3, 'Skoda', 9000);" 
                "INSERT INTO Cars VALUES(4, 'Volvo', 29000);" 
                "INSERT INTO Cars VALUES(5, 'Bentley', 350000);" 
                "INSERT INTO Cars VALUES(6, 'Citroen', 21000);" 
                "INSERT INTO Cars VALUES(7, 'Hummer', 41400);" 
                "INSERT INTO Cars VALUES(8, 'Volkswagen', 21600);";

    // wrapper for qlite3_prepare_v2(), sqlite3_step(), and sqlite3_finalize()
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    check_query(rc, db, err_msg);

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

void check_query(int rc, sqlite3 *db, char *err_msg)
{
    if (rc != SQLITE_OK) 
    {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        
        exit(EXIT_FAILURE);
    }    
}

