#include <iostream>
#include <sqlite3.h>

#include "Accounts.h"
#include "SQL.h"
int main(void) {

  SQL db;

  sqlite3 *DB = db.sql_open();
  db.sql_table_create(*DB);
  Account account;

  int choice;
  std::cout << "\t\t\t********************** Banking "
               "System****************************"
            << std::endl;
  std::cout
      << "\t\t\t********************** Main menu ****************************"
      << std::endl;
  std::cout << "\t1- Create an account" << std::endl;
  std::cout << "\t2- Login to an account" << std::endl;
  std::cout << "\t3- Show all accounts" << std::endl;
  std::cout << "\t4- Search account" << std::endl;
  std::cout << "\t5- Delete an account" << std::endl;
  std::cout << "\tChoose a number: ";
  std::cin >> choice;

  switch (choice) {

  case 1:
    account.account_create(*DB);
    break;
  case 2:
    account.account_search(*DB);
    break;
  case 3:
    account.account_show_all(*DB);
    break;
  case 4:
    account.account_search(*DB);
    break;
  case 5:
    account.account_delete(*DB);
    break;
  }
  db.sql_close(*DB);
  return 0;
}
