#if !defined(BANK_H)
#define BANK_H
#include "Accounts.h"
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random>

class Bank {
public:
  void bank_login(sqlite3 &db);
};

void Bank::bank_login(sqlite3 &db) {

  std::string acc_no, pin;

  std::cout << "Enter yout account number: ";
  std::cout << "Enter your pin number: ";

  std::string data("");
  std::string sql =
      "SELECT * FROM ACCOUNTS WHERE id = " + std::to_string(acc_no) + ";";

  int exit =
      sqlite3_exec(&db, sql.c_str(), callback, (void *)data.c_str(), NULL);

  if (exit != SQLITE_OK) {
    std::cerr << "Error: "
              << "\n";
  } else {
    std::cout << "Account has been found"
              << "\n";
  }
}

#endif
