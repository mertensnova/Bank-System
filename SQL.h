#if !defined(SQL_H)
#define SQL_H

#include <iostream>
#include <sqlite3.h>

class SQL {
public:
  sqlite3 *sql_open();
  void sql_close(sqlite3 *db);
};

sqlite3 *SQL::sql_open() {
  sqlite3 *DB;
  int exit = 0;
  exit = sqlite3_open("bank.db", &DB);

  if (exit) {
    std::cerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
  } else
    std::cout << "Opened Database Successfully!" << std::endl;

  return DB;
}

void SQL::sql_close(sqlite3 *db) {
  sqlite3_close(db);
  std::cout << "Database is closed" << std::endl;
}

#endif // SQL_H
