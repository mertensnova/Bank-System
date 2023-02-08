#include <iostream>
#include "Person.h"

using namespace std;


void account_create()
{
    Person account;
    time_t now = time(0);
    char* dt = ctime(&now);
    tm *gmtm = gmtime(&now);
    dt = asctime(gmtm);

    cout << "Name: ";
    getline(cin >> ws, account.name);
    
    cout << "Pin: ";
    cin >> account.pin;
    
    cout << "Deposit: ";
    cin >> account.balance;

    cout << "Created at: " << dt;
    account.created_at  = dt;    
}