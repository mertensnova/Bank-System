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
  void bank_login(sqlite3 &db);
  void bank_menu(sqlite3 &db, std::string acc_no, double balance);
  void bank_withdraw(sqlite3 &db, std::string acc_no, double balance);
  void bank_deposit(sqlite3 &db, std::string acc_no, double balance);
  void bank_transfer(sqlite3 &db, std::string acc_no, double balance);
};

void Bank::bank_menu(sqlite3 &db, std::string acc_no, double balance) {

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
    bank_withdraw(db, acc_no, balance);
    break;
  case 2:
    bank_deposit(db, acc_no, balance);
    break;
  case 3:
    bank_transfer(db, acc_no, balance);
    break;
  }
}
void Bank::bank_login(sqlite3 &db) {

  std::string acc_no, pin;

  double balance;
  char *err_msg;
  std::cout << "[*] Enter yout account name: ";

  std::getline(std::cin >> std::ws, acc_no);
  std::cout << "[*] Enter your pin number: ";
  std::cin >> pin;

  sqlite3_stmt *stmt;
  int rc;
  std::string sql = "SELECT *  FROM ACCOUNTS WHERE name = ? AND pin = ?;";

  sqlite3_prepare_v2(&db, sql.c_str(), -1, &stmt, NULL);

  sqlite3_bind_text(stmt, 1, acc_no.c_str(), acc_no.length(), NULL);
  sqlite3_bind_text(stmt, 2, pin.c_str(), pin.length(), NULL);
  if ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
    balance = sqlite3_column_double(stmt, 4);
    bank_menu(db, acc_no, balance);
  }
}

void Bank::bank_withdraw(sqlite3 &db, std::string acc_no, double balance) {

  double amount;
  sqlite3_stmt *stmt;
  int rc;
  std::cout << "[*] How much do you want to withdraw? ";
  std::cin >> amount;
  if (amount > balance) {
    std::cout << "[!] Not enought balance"
              << "\n";
    return;
  }
  std::string sql = "UPDATE ACCOUNTS SET balance = ? WHERE name = ?;";

  sqlite3_prepare_v2(&db, sql.c_str(), -1, &stmt, NULL);

  if (stmt != NULL) {
    sqlite3_bind_double(stmt, 1, balance - amount);
    sqlite3_bind_text(stmt, 2, acc_no.c_str(), acc_no.length(),
                      SQLITE_TRANSIENT);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    std::cout << "[*] Your balance now " << balance - amount << "\n";
  } else
    std::cout << "\n" << sqlite3_errmsg(&db) << "\n";

  SQL x;
  x.sql_transactions_add(db, acc_no, "", amount, "Withdraw");
}

void Bank::bank_deposit(sqlite3 &db, std::string acc_no, double balance) {

  double amount;
  sqlite3_stmt *stmt;
  int rc;
  std::cout << "[*] How much do you want to deposit? ";
  std::cin >> amount;

  std::string sql = "UPDATE ACCOUNTS SET balance = ? WHERE name = ?;";

  sqlite3_prepare_v2(&db, sql.c_str(), -1, &stmt, NULL);

  if (stmt != NULL) {
    sqlite3_bind_double(stmt, 1, balance + amount);
    sqlite3_bind_text(stmt, 2, acc_no.c_str(), acc_no.length(),
                      SQLITE_TRANSIENT);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    std::cout << "[*] Your balance now " << balance + amount << "\n";
  } else
    std::cout << "\n" << sqlite3_errmsg(&db) << "\n";

  SQL x;
  x.sql_transactions_add(db, acc_no, "", amount, "Deposit");
}

void Bank::bank_transfer(sqlite3 &db, std::string acc_no, double balance) {

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
    sqlite3_bind_text(stmt, 2, acc_no.c_str(), acc_no.length(),
                      SQLITE_TRANSIENT);
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
  x.sql_transactions_add(db, acc_no, whom, amount, "Transfer");
}

#endif
