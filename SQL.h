#include <string>
#if !defined(SQL_H)
#define SQL_H

#include <cstring>
#include <iostream>
#include <sqlite3.h>

class SQL {
public:
  sqlite3 *sql_open();
  void sql_close(sqlite3 *db);
  void sql_table_create(sqlite3 *db);
  void sql_account_insert(sqlite3 *db, std::string name, double balance,
                          int pin);
};

sqlite3 *SQL::sql_open() {
  sqlite3 *DB;
  int exit = 0;
  exit = sqlite3_open("bank.db", &DB);

  if (exit) {
    std::cerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
  } else
    std::cout << "Opened Database Successfully!" << std::endl;

  return DB;
}

void SQL::sql_close(sqlite3 *db) {
  sqlite3_close(db);
  std::cout << "Database is closed" << std::endl;
}

void SQL::sql_table_create(sqlite3 *db) {

  std::string sql = "CREATE TABLE ACCOUNTS("
                    "ID INT PRIMARY KEY     NOT NULL, "
                    "NAME           TEXT    NOT NULL, "
                    "PIN            INT     NOT NULL, "
                    "CREATED_AT     TEXT    NOT NULL, "
                    "BALANCE        REAL );";
  int exit = 0;
  char *messaggeError;
  exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messaggeError);

  if (exit != SQLITE_OK) {
    std::cerr << "Error Create Table" << std::endl;
    sqlite3_free(messaggeError);
  } else
    std::cout << "Table Accounts created Successfully" << std::endl;
}
void SQL::sql_account_insert(sqlite3 *db, std::string name, double balance,
                             int pin) {

  char *messaggeError;
  int exit = 0;

  std::string sql("INSERT INTO ACCOUNTS (NAME,PIN,BALANCE) VALUES(" + name +
                  "," + std::to_string(pin) + "," + std::to_string(balance) +
                  ");");

  exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messaggeError);
  if (exit != SQLITE_OK) {
    std::cerr << "Error: " << messaggeError << std::endl;
    sqlite3_free(messaggeError);
  } else
    std::cout << "Records created Successfully!" << std::endl;
}

#endif // SQL_H
