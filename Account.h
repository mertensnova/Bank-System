#include <random>
#include <string>
#if !defined(ACCOUNT_H)
#define ACCOUNT_H
#include "SQL.h"
#include <iostream>
#include <sqlite3.h>

class Account {
private:
  std::string pin;
  double balance;
  std::string name;
  std::string account_number;

public:
  void account_create(sqlite3 *db);
  void account_search(sqlite3 *db);
};

void Account::account_create(sqlite3 *db) {

  SQL insert;
  std::cout << "Name: ";
  std::getline(std::cin >> std::ws, this->name);

  std::cout << "Pin: ";
  std::getline(std::cin >> std::ws, this->pin);

  std::cout << "Balance: ";
  std::cin >> this->balance;

  insert.sql_account_insert(db, this->name, this->balance, this->pin);
};

void Account::account_search(sqlite3 *db) {
  SQL search;

  search.sql_account_search(db, "Amr Ashebo", 7);
}

#endif
