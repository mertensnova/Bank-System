#include <iostream>
#include <fstream>
#include "Person.h"
#include "Methods.h"

using namespace std;

void menu()
{
     cout << "\t\t\t********************** Banking System****************************" << endl;
     cout << "\t\t\t********************** Main menu ****************************" << endl;
     int choice;

    cout << "\t1 - Create an account" << endl;
    cout << "\t2 - Login to an account" << endl;
    cout << "\t3 - Show all accounts" << endl;
    cout << "\t4 - Delete an account" << endl;
    cout << "\tChoose a number: ";
    cin >> choice;
   
     switch (choice)
     {
     case 1:
        account_create();
        break;
    case 3:
        account_view_all();
        break;
     default:
        break;
     }
}

void account_create()
{
    // fsstream fp_obj;
    char *x;
    Person account;
    ofstream file("Accounts.txt");
    if (!file.is_open())
        cout << "File not open\n";

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

    file >> account.name;
    
    file.close();
    
  
}

void account_view_all()
{
    Person account;
    ifstream fp_obj;
    fstream file("Accounts.dat",ios::in);
    if (!file.is_open())
        cout << "File not open\n";
    do
    {
        getline(file,account.name, '\0');
        file.read((char *)&account.balance,sizeof(account.balance));
    } while (!file.eof());
    file.close();
    
}


