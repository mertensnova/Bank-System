#if !defined(METHOD_H)
#define METHOD_H
#include <iostream>
#include <ctime>


void menu();
void account_login();
void account_create();
void account_view_all();
void account_search();
void account_deletion();
void account_update(int id,long double balance);
void account_transfer(int id,long double balance);


#endif