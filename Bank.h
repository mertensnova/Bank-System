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
  void bank_menu(sqlite3 &db, std::string acc_no);
  void bank_withdraw(sqlite3 &db, std::string acc_no);
  void bank_deposit(sqlite3 &db, std::string acc_no);
  void bank_transfer(sqlite3 &db, std::string acc_no);
};

void Bank::bank_menu(sqlite3 &db, std::string acc_no) {

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
    bank_withdraw(db, acc_no);
    break;
  case 2:
    std::cout << "X";
    break;
  case 3:
    std::cout << "aaa";
    break;
  }
}
void Bank::bank_login(sqlite3 &db) {

  std::string acc_no, pin;
  char *err_msg;
  std::cout << "Enter yout account number: ";

  std::getline(std::cin >> std::ws, acc_no);
  std::cout << "Enter your pin number: ";
  std::getline(std::cin >> std::ws, pin);

  std::string sql =
      "SELECT * FROM ACCOUNTS WHERE id = " + acc_no + " AND pin = " + pin + ";";

  int exit = sqlite3_exec(&db, sql.c_str(), NULL, NULL, &err_msg);

  if (exit != SQLITE_OK) {
    std::cerr << "Error: " << err_msg << "\n";
  } else {
    std::cout << "Account has been found"
              << "\n";
    bank_menu(db, acc_no);
  }
}

#endif
