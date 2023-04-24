#include <iostream>
#include <sqlite3.h>

#include "Accounts.h"
#include "Bank.h"
#include "SQL.h"
int main(void) {

  SQL db;

  sqlite3 *DB = db.sql_open();

  std::string sql = "CREATE TABLE ACCOUNTS("
                    "ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                    "NAME           TEXT NOT NULL,"
                    "PIN            TEXT NOT NULL,"
                    "BALANCE        REAL NOT NULL,"
                    "CREATED_AT TIMESTAMP DEFAULT CURRENT_TIMESTAMP);";

  db.sql_table_create(*DB, sql);

  
  sql = "CREATE TABLE TRANSACTIONS("
                    "ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                    "ACCOUNT         TEXT NOT NULL,"
                    "TYPE            TEXT NOT NULL,"
                    "WHOM            TEXT ,"
                    "AMOUNT REAL NOT NULL,"
                    "CREATED_AT TIMESTAMP DEFAULT CURRENT_TIMESTAMP);";

  db.sql_table_create(*DB, sql);
 
  Account account;
  Bank Op;

  int choice;
  std::cout << "Banking System" << std::endl;
  std::cout << "Main Menu" << std::endl;
  std::cout << "[1] Create an account" << std::endl;
  std::cout << "[2] Login to an account" << std::endl;
  std::cout << "[3] Search an account" << std::endl;
  std::cout << "[4] Delete an account" << std::endl;
  std::cout << "Choose a number: ";
  std::cin >> choice;

  switch (choice) {

  case 1:
    account.account_create(*DB);
    break;
  case 2:
    Op.bank_login(*DB);
    break;
  case 3:
    account.account_search(*DB);
    break;
  case 4:
    account.account_delete(*DB);
    break;
  }
  db.sql_close(*DB);
  return 0;
}
