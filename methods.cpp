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
    Person account;
    fstream fp_obj;

    account.account_create();
  
    fp_obj.open("Accounts.dat",ios::out|ios::binary);
    if (!fp_obj)
        cout << "File not open\n";
    

    
    fp_obj.write((char*)&account,sizeof(account));
    
    fp_obj.close();   

}

void account_view_all()
{
    ifstream fp_obj; 
    Person account;
    // fp_obj.open("Accounts.dat",ios::out|ios::binary);
    fstream file("Accounts.dat",ios::in|ios::binary);
    if (!file.is_open())
        cout << "File not open\n";
    
    if (file.read((char*)&account,sizeof(account)))
    {
        account.account_view();
    }	

    else
		cout<<"Error in reading data from file...\n";
    
    fp_obj.close();  

}