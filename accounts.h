#if !defined(ACCOUNTS_H)
#define ACCOUNTS_H
#include <iostream>
#include <sqlite3.h>

#include "sql.h"

class Account {
private:
  std::string pin;
  double balance;
  std::string name;

public:
  SQL operation;
  void account_create(sqlite3 &db);
  void account_search(sqlite3 &db);
  void account_delete(sqlite3 &db);
};

void Account::account_create(sqlite3 &db) {

  // Get user input
  std::cout << "Name: ";
  std::getline(std::cin >> std::ws, this->name);

  std::cout << "Pin: ";
  std::getline(std::cin >> std::ws, this->pin);

  std::cout << "Balance: ";
  std::cin >> this->balance;

  // Insert to the database
  operation.sql_account_insert(db, this->name, this->balance, this->pin);
};

void Account::account_search(sqlite3 &db) {
  // Get user input
  int id;
  std::cout << "Enter a ID number: ";
  std::cin >> id;

  // Search the account
  operation.sql_account_search(db, id);
}
void Account::account_delete(sqlite3 &db) {
  // Get user input
  int id;
  std::cout << "Enter a ID number: ";
  std::cin >> id;

  // Delete the account
  operation.sql_account_delete(db, id);
}

#endif
