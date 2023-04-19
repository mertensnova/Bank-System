#include <ostream>
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
                          std::string pin);
};

sqlite3 *SQL::sql_open() {
  sqlite3 *DB;
  int exit = 0;
  exit = sqlite3_open("bank.db", &DB);

  if (exit) {
    std::cerr << "Error:  " << sqlite3_errmsg(DB) << std::endl;
  } else
    std::cout << "Success: Opened Database Successfully!" << std::endl;

  return DB;
}

void SQL::sql_close(sqlite3 *db) {
  sqlite3_close(db);
  std::cout << "Success: Close Database" << std::endl;
}

void SQL::sql_table_create(sqlite3 *db) {

  std::string sql = "CREATE TABLE ACCOUNTS("
                    "ID INT PRIMARY KEY AUTO_INCREMENT NOT NULL,"
                    "NAME           TEXT NOT NULL,"
                    "PIN            TEXT NOT NULL,"
                    "Created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP, "
                    "BALANCE        REAL NOT NULL );";
  int exit = 0;
  char *messaggeError;
  exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messaggeError);

  if (exit != SQLITE_OK) {
    std::cerr << "Error: Create Table" << std::endl;
    sqlite3_free(messaggeError);
  } else
    std::cout << "Success: Table Accounts created Successfully" << std::endl;
}
void SQL::sql_account_insert(sqlite3 *db, std::string name, double balance,
                             std::string pin) {
  sqlite3_stmt *stmt;

  std::string sql =
      "INSERT INTO ACCOUNTS (name, pin, balance) VALUES (?, ?, ?)";

  sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
  if (stmt != NULL) {
    sqlite3_bind_text(stmt, 1, name.c_str(), 0, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, pin.c_str(), 0, SQLITE_TRANSIENT);
    sqlite3_bind_double(stmt, 3, balance);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    std::cout << name << "has been added successfully"
              << "\n";
  } else
    std::cout << "\n" << sqlite3_errmsg(db) << "\n";
}

#endif // SQL_H
