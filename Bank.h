#if !defined(BANK_H)
#define BANK_H
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random>

#include "Accounts.h"
#include "SQL.h"

class Bank {
public:
  int bank_login(sqlite3 &db);
  int bank_menu(sqlite3 &db, std::string name, double balance);
  int bank_withdraw(sqlite3 &db, std::string name, double balance);
  int bank_deposit(sqlite3 &db, std::string name, double balance);
  int bank_transfer(sqlite3 &db, std::string name, double balance);
};

int Bank::bank_menu(sqlite3 &db, std::string name, double balance) {

  // Get users choice
  int choice;

  std::cout << "Menu"
            << "\n";

  std::cout << "[1] Withdraw"
            << "\n";
  std::cout << "[2] Deposit"
            << "\n";
  std::cout << "[3] Transfer"
            << "\n";

  std::cout << "Your choice: ";
  std::cin >> choice;
  switch (choice) {
  case 1:
    // Witdraw
    bank_withdraw(db, name, balance);
    break;
  case 2:
    // Depoist
    bank_deposit(db, name, balance);
    break;
  case 3:
    // Transfer
    bank_transfer(db, name, balance);
    break;
  default:
    std::cout << "Choice dosnt exits" << std::endl;
    return -1;
  }

  return 0;
}
int Bank::bank_login(sqlite3 &db) {

  std::string name, pin;
  // Get user input
  double balance;
  char *err_msg;
  std::cout << "[*] Enter yout account name: ";

  std::getline(std::cin >> std::ws, name);
  std::cout << "[*] Enter your pin number: ";
  std::cin >> pin;

  // Check if the name and pin are valid
  sqlite3_stmt *stmt;
  int rc = sqlite3_step(stmt);

  // SQL query that checks the if the name and pin
  std::string sql = "SELECT *  FROM ACCOUNTS WHERE name = ? AND pin = ?;";

  // Converts SQL query to prepare statement
  sqlite3_prepare_v2(&db, sql.c_str(), -1, &stmt, NULL);

  // Bind the values to the statement
  sqlite3_bind_text(stmt, 1, name.c_str(), name.length(), NULL);
  sqlite3_bind_text(stmt, 2, pin.c_str(), pin.length(), NULL);
  if (rc == SQLITE_ROW) {
    // Return the balance pass it to bank menu function
    balance = sqlite3_column_double(stmt, 4);
    bank_menu(db, name, balance);
  }
  return 0;
}

int Bank::bank_withdraw(sqlite3 &db, std::string name, double balance) {

  // Get user input
  double amount;
  // INit a stmt
  sqlite3_stmt *stmt;
  std::cout << "[*] How much do you want to withdraw? ";
  std::cin >> amount;

  // Check if the amount is valid
  if (amount > balance || amount < 0) {
    std::cout << "[!] Not enought balance" << std::endl;
    return -1;
  }

  // SQL query to update the users balance
  std::string sql = "UPDATE ACCOUNTS SET balance = ? WHERE name = ?;";

  // COnvert the sql query to prepare statement
  sqlite3_prepare_v2(&db, sql.c_str(), -1, &stmt, NULL);

  if (stmt != NULL) {
    // Bind the statements
    sqlite3_bind_double(stmt, 1, balance - amount);
    sqlite3_bind_text(stmt, 2, name.c_str(), name.length(), SQLITE_TRANSIENT);

    // Finalize the statement
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    std::cout << "[*] Your balance now " << balance - amount << "\n";
  } else {
    std::cout << "\n" << sqlite3_errmsg(&db) << "\n";
    return -1;
  }

  // Add the transation to the database
  SQL x;
  x.sql_transactions_add(db, name, "", amount, "Withdraw");
  return 0;
}

int Bank::bank_deposit(sqlite3 &db, std::string name, double balance) {

  double amount;
  sqlite3_stmt *stmt;
  std::cout << "[*] How much do you want to deposit? ";
  std::cin >> amount;

  std::string sql = "UPDATE ACCOUNTS SET balance = ? WHERE name = ?;";

  sqlite3_prepare_v2(&db, sql.c_str(), -1, &stmt, NULL);

  if (stmt != NULL) {
    sqlite3_bind_double(stmt, 1, balance + amount);
    sqlite3_bind_text(stmt, 2, name.c_str(), name.length(), SQLITE_TRANSIENT);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    std::cout << "[*] Your balance now " << balance + amount << "\n";
  } else
    std::cout << "\n" << sqlite3_errmsg(&db) << "\n";

  SQL x;
  x.sql_transactions_add(db, name, "", amount, "Deposit");
}

int Bank::bank_transfer(sqlite3 &db, std::string name, double balance) {

  double amount, payee;
  std::string whom;
  sqlite3_stmt *stmt;
  int rc;
  std::cout << "[*] How much do you want to transfer? ";
  std::cin >> amount;
  std::cout << "[*] To whom? ";
  std::getline(std::cin >> std::ws, whom);

  if (amount > balance) {
    std::cout << "[!] Not enought balance"
              << "\n";
    return;
  }

  std::string sql = "UPDATE ACCOUNTS SET balance = ? WHERE name = ?;";

  sqlite3_prepare_v2(&db, sql.c_str(), -1, &stmt, NULL);

  if (stmt != NULL) {
    sqlite3_bind_double(stmt, 1, balance - amount);
    sqlite3_bind_text(stmt, 2, name.c_str(), name.length(), SQLITE_TRANSIENT);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    std::cout << "[*] Your balance now " << balance - amount << "\n";
  } else
    std::cout << "\n" << sqlite3_errmsg(&db) << "\n";

  sql = "SELECT *  FROM ACCOUNTS WHERE name = ?;";

  sqlite3_prepare_v2(&db, sql.c_str(), -1, &stmt, NULL);

  sqlite3_bind_text(stmt, 1, whom.c_str(), whom.length(), NULL);
  if ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
    payee = sqlite3_column_double(stmt, 4);
  }

  sql = "UPDATE ACCOUNTS SET balance = ? WHERE name = ?;";

  sqlite3_prepare_v2(&db, sql.c_str(), -1, &stmt, NULL);

  if (stmt != NULL) {
    sqlite3_bind_double(stmt, 1, payee + amount);
    sqlite3_bind_text(stmt, 2, whom.c_str(), whom.length(), SQLITE_TRANSIENT);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
  } else
    std::cout << "\n" << sqlite3_errmsg(&db) << "\n";

  SQL x;
  x.sql_transactions_add(db, name, whom, amount, "Transfer");
}

#endif
