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

  void sql_account_search(sqlite3 *db, std::string name, int id);
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
                    "ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                    "NAME           TEXT NOT NULL,"
                    "PIN            TEXT NOT NULL,"
                    "CREATED_AT TIMESTAMP DEFAULT CURRENT_TIMESTAMP, "
                    "BALANCE        REAL NOT NULL );";
  int exit = 0;
  char *messaggeError;
  exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messaggeError);

  if (exit != SQLITE_OK) {
    std::cerr << "Error: " << messaggeError << std::endl;
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
    sqlite3_bind_text(stmt, 1, name.c_str(), name.length(), SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, pin.c_str(), pin.length(), SQLITE_TRANSIENT);
    sqlite3_bind_double(stmt, 3, balance);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    std::cout << name << "has been added successfully"
              << "\n";
  } else
    std::cout << "\n" << sqlite3_errmsg(db) << "\n";
}

void SQL::sql_account_search(sqlite3 *db, std::string name, int id) {
  char *messaggeError;

  sqlite3_stmt *stmt;
  std::string sql = "SELECT * FROM ACCOUNTS WHERE name = ? AND id = ?;";

  sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
  if (stmt != NULL) {
    sqlite3_bind_text(stmt, 1, name.c_str(), name.length(), SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, id);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    std::cout << name << " has been found"
              << "\n";
  } else
    std::cout << "\n" << sqlite3_errmsg(db) << "\n";
}

#endif // SQL_H
