#include <iostream>
#include <ctime>
#include <random>
#include <fstream>
#include "Account.h"
#include "Methods.h"

using namespace std;

void menu()
{
    Account account;
    cout << "<<<<<\tBanking System\t>>>>>" << endl;
    cout << "<<<\tMain menu\t>>>" << endl;
    int choice;

    cout << "1 - Create an account" << endl;
    cout << "2 - Login to an account" << endl;
    cout << "3 - Show all accounts" << endl;
    cout << "4 - Delete an account" << endl;
    cout << "Choose a number: ";
    cin >> choice;
   
     switch (choice)
     {
     case 1:
        account.account_create();
        break;
    case 3:
       account.account_view_all();
        break;
     default:
        break;
     }
}