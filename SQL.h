#include <string>
#if !defined(SQL_H)
#define SQL_H

#include <cstring>
#include <iostream>
#include <sqlite3.h>

class SQL {
public:
  char *err_msg;
  sqlite3 *sql_open();
  void sql_close(sqlite3 &db);
  void sql_table_create(sqlite3 &db, std::string sql);
  void sql_account_insert(sqlite3 &db, std::string name, double balance,
                          std::string pin);

  void sql_account_search(sqlite3 &db, std::string name, int id);
  void sql_account_delete(sqlite3 &db, int id);
  void sql_transactions_add(sqlite3 &db, std::string payer, std::string payee,
                            double amount,std::string type);
};

sqlite3 *SQL::sql_open() {
  sqlite3 *DB;
  int exit = 0;
  exit = sqlite3_open("bank.db", &DB);

  if (exit) {
    std::cerr << "[!] Error:  " << sqlite3_errmsg(DB) << "\n\n";
  } else
    std::cout << "Success: Opened Database Successfully!"
              << "\n\n";

  return DB;
}

void SQL::sql_close(sqlite3 &db) {
  sqlite3_close(&db);
  std::cout << "Success: Close Database"
            << "\n\n";
}

void SQL::sql_table_create(sqlite3 &db, std::string sql) {
  int exit = 0;
  exit = sqlite3_exec(&db, sql.c_str(), NULL, 0, &this->err_msg);

  if (exit != SQLITE_OK) {
    std::cerr << "Error: " << this->err_msg << std::endl;
    sqlite3_free(this->err_msg);
  } else
    std::cout << "Success: Tables created Successfully" << std::endl;
}

void SQL::sql_account_insert(sqlite3 &db, std::string name, double balance,
                             std::string pin) {
  sqlite3_stmt *stmt;

  std::string sql =
      "INSERT INTO ACCOUNTS (name, pin, balance) VALUES (?, ?, ?)";

  sqlite3_prepare_v2(&db, sql.c_str(), -1, &stmt, NULL);
  if (stmt != NULL) {
    sqlite3_bind_text(stmt, 1, name.c_str(), name.length(), SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, pin.c_str(), pin.length(), SQLITE_TRANSIENT);
    sqlite3_bind_double(stmt, 3, balance);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    std::cout << name << "has been added successfully"
              << "\n";
  } else
    std::cout << "\n" << sqlite3_errmsg(&db) << "\n";
}

void SQL::sql_account_search(sqlite3 &db, std::string name, int id) {
  sqlite3_stmt *stmt;

  int rc;
  std::string sql = "SELECT *  FROM ACCOUNTS WHERE id = ?;";

  sqlite3_prepare_v2(&db, sql.c_str(), -1, &stmt, NULL);

  sqlite3_bind_int(stmt, 1, id);
  while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
    printf("[*] Name: %s\n", sqlite3_column_text(stmt, 1));
    printf("[*] Balance: %lf\n", sqlite3_column_double(stmt, 3));
    printf("[*] Created at: %s\n", sqlite3_column_text(stmt, 4));
  }
}

void SQL::sql_account_delete(sqlite3 &db, int id) {
  std::string sql =
      "DELETE FROM ACCOUNTS WHERE id = " + std::to_string(id) + ";";
  int exit = sqlite3_exec(&db, sql.c_str(), NULL, 0, &this->err_msg);
  if (exit != SQLITE_OK) {
    std::cerr << "Error: " << this->err_msg << std::endl;
    sqlite3_free(this->err_msg);
  } else
    std::cout << "Record deleted Successfully!" << std::endl;
}
void SQL::sql_transactions_add(sqlite3 &db, std::string payer,
                               std::string payee, double amount,std::string type) {
  sqlite3_stmt *stmt;

  std::string sql = "INSERT INTO TRANSACTIONS (account,type, whom, amount) "
                    "VALUES (?, ?, ?,?)";

  sqlite3_prepare_v2(&db, sql.c_str(), -1, &stmt, NULL);
  if (stmt != NULL) {
    sqlite3_bind_text(stmt, 1, payer.c_str(), payer.length(), SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, type.c_str(), type.length(), SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, payee.c_str(), payee.length(), SQLITE_TRANSIENT);
    sqlite3_bind_double(stmt, 4, amount);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
  } else
    std::cout << "\n" << sqlite3_errmsg(&db) << "\n";
}

#endif // SQL_H
