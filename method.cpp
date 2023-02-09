#include <iostream>
#include "Person.h"

using namespace std;

void account_create();
void account_view_all();
void menu()
{
     cout << "\t\t\t********************** Banking System****************************" << endl;
     cout << "\t\t\t********************** Main menu ****************************" << endl;
     int choice;

    cout << "\t1- Create an account" << endl;
    cout << "\t2- Login to an account" << endl;
    cout << "\t3- Show all accounts" << endl;
    cout << "\t4- Delete an account" << endl;
    cout << "\tChoose a number: ";
    cin >> choice;
   
     switch (choice)
     {
     case 1:
        account_create();
        break;
    case 2:
        account_view_all();
        break;
     default:
        break;
     }
}

void account_create()
{
    FILE *fp;
    fp = fopen("Accounts.dat", "ab+");
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
    fwrite(&account, sizeof(account), 1, fp);
}
void account_view_all()
{
    Person account;
    FILE *fp;
    fp = fopen("Accounts.dat", "rb");
    while (fread(&account, sizeof(account), 1, fp))
    {
        cout << "\t\t----------------------------------------- \n";
        cout << "\t\tAccount's ID: " << account.id << endl;
        cout << "\t\tAccount's name: " << account.name << endl;
        cout << "\t\tAccount's balance: $" << account.balance << endl;
        cout << "\t\tMember since: " << account.created_at << endl;
  }
    
}