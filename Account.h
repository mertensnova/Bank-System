#include <random>
#include <string>
#if !defined(ACCOUNT_H)
#define ACCOUNT_H
#include "SQL.h"
#include <iostream>
#include <sqlite3.h>

class Account {
private:
  int pin;
  double balance;
  std::string name;
  std::string account_number;

public:
  Account(sqlite3 *db);
};

Account::Account(sqlite3 *db) {

  SQL insert;
  std::cout << "Name: ";
  std::getline(std::cin >> std::ws, this->name);

  std::cout << "Pin: ";
  std::cin >> this->pin;

  std::cout << "Balance: ";
  std::cin >> this->balance;

  insert.sql_account_insert(db, this->name, this->balance, this->pin);

};

#endif
