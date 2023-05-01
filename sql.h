#if !defined(SQL_H)
#define SQL_H

#include <cstring>
#include <iostream>
#include <memory>
#include <sqlite3.h>

class SQL {
public:
  std::unique_ptr<char *[]> err_msg;
  sqlite3 *sql_open();
  int sql_close(sqlite3 &db);
  int sql_table_create(sqlite3 &db, std::string sql);
  int sql_account_insert(sqlite3 &db, std::string name, double balance,
                         std::string pin);

  int sql_account_search(sqlite3 &db, int id);
  int sql_account_delete(sqlite3 &db, int id);
  int sql_transactions_add(sqlite3 &db, std::string payer, std::string payee,
                           double amount, std::string type);
};

sqlite3 *SQL::sql_open() {

  // Inizilize a new DB
  sqlite3 *DB;

  // Open DB
  int exit = sqlite3_open("bank.db", &DB);

  // Error handling
  if (exit) {
    std::cerr << "[!] Error:  " << sqlite3_errmsg(DB) << std::endl;
  } else
    std::cout << "Success: Opened Database Successfully!"
              << "\n\n";

  // Return DB
  return DB;
}

int SQL::sql_close(sqlite3 &db) {
  // Close DB
  sqlite3_close(&db);
  std::cout << "Success: Close Database" << std::endl;
  return 0;
}

int SQL::sql_table_create(sqlite3 &db, std::string sql) {

  // Create tables
  int exit = sqlite3_exec(&db, sql.c_str(), NULL, 0, this->err_msg.get());

  // Return an error if failed
  if (exit != SQLITE_OK) {
    std::cerr << "Error: " << this->err_msg.get() << std::endl;
    sqlite3_free(&this->err_msg);
    return -1;
  }
  // Return success
  std::cout << "Success: Tables created Successfully" << std::endl;
  return 0;
}

int SQL::sql_account_insert(sqlite3 &db, std::string name, double balance,
                            std::string pin) {

  // Init a STMT
  sqlite3_stmt *stmt;

  // SQL query to insert the account
  std::string sql =
      "INSERT INTO ACCOUNTS (name, pin, balance) VALUES (?, ?, ?)";

  // Convert SQL query to prepare statement
  sqlite3_prepare_v2(&db, sql.c_str(), -1, &stmt, NULL);

  // Bind the the parameters to the SQL query
  if (stmt != NULL) {
    sqlite3_bind_text(stmt, 1, name.c_str(), name.length(), SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, pin.c_str(), pin.length(), SQLITE_TRANSIENT);
    sqlite3_bind_double(stmt, 3, balance);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    std::cout << name << " has been added successfully" << std::endl;
    return 0;
  }
  // Return error if failed
  std::cout << std::endl << sqlite3_errmsg(&db) << std::endl;
  return -1;
}

int SQL::sql_account_search(sqlite3 &db, int id) {

  // Init a STMT
  sqlite3_stmt *stmt;

  // SQL query to get the accounts using the ID
  std::string sql = "SELECT *  FROM ACCOUNTS WHERE id = ?;";

  // Convert SQL query to prepare statement
  int rc = sqlite3_prepare_v2(&db, sql.c_str(), -1, &stmt, NULL);
  if (rc != SQLITE_OK) {
    std::cerr << "Error: " << sqlite3_errmsg(&db) << std::endl;
    return -1;
  }

  // Bind the the parameters to the  prepare statement
  sqlite3_bind_int(stmt, 1, id);

  // Execute the statement and print the results
  rc = sqlite3_step(stmt);
  while (rc == SQLITE_ROW) {
    printf("[*] Name: %s\n", sqlite3_column_text(stmt, 1));
    printf("[*] Balance: %lf\n", sqlite3_column_double(stmt, 3));
    printf("[*] Created at: %s\n", sqlite3_column_text(stmt, 4));
    rc = sqlite3_step(stmt);
  }

  // Finalize the statement and check for errors
  rc = sqlite3_finalize(stmt);
  if (rc != SQLITE_OK) {
    std::cerr << "Error: " << sqlite3_errmsg(&db) << std::endl;
    return -1;
  }

  // Return success
  std::cout << "Account found" << std::endl;
  return 0;
}
int SQL::sql_account_delete(sqlite3 &db, int id) {
  // SQL query to delete an account based on the ID
  std::string sql =
      "DELETE FROM ACCOUNTS WHERE id = " + std::to_string(id) + ";";

  // Execute the SQL query
  int exit = sqlite3_exec(&db, sql.c_str(), NULL, 0, err_msg.get());

  // Return an error if failed
  if (exit != SQLITE_OK) {
    std::cerr << "Error: " << this->err_msg.get() << std::endl;
    return -1;
  }
  std::cout << "Record deleted Successfully!" << std::endl;
  return 0;
}
int SQL::sql_transactions_add(sqlite3 &db, std::string payer, std::string payee,
                              double amount, std::string type) {

  // Init STMT
  sqlite3_stmt *stmt;

  // SQL query to inset a transaction to the database
  std::string sql = "INSERT INTO TRANSACTIONS (account,type, whom, amount) "
                    "VALUES (?, ?, ?,?)";

  // Convert the SQL query to prepare statements
  sqlite3_prepare_v2(&db, sql.c_str(), -1, &stmt, NULL);

  // Bind the the parameters to the  prepare statement
  if (stmt != NULL) {
    sqlite3_bind_text(stmt, 1, payer.c_str(), payer.length(), SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, type.c_str(), type.length(), SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, payee.c_str(), payee.length(), SQLITE_TRANSIENT);
    sqlite3_bind_double(stmt, 4, amount);
    // Finalize the statements
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return 0;
  }
  std::cout << std::endl << sqlite3_errmsg(&db) << std::endl;
  return -1;
}

#endif // SQL_H
