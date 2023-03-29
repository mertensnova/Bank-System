#if !defined(BANK_H)
#define BANK_H
#include <iostream>
#include <conio.h>
#include <ctime>
#include <random>
#include <fstream>
#include <cstring>
#include "Account.h"

class Bank
{
    public:
        void bank_account_create(Account account);
        void bank_account_read_all();
        void bank_account_search();
        void bank_account_delete();
        void bank_account_login();
        void bank_account_menu(Account account);
        void bank_account_update_balance(double __balance,Account acc);
        void bank_account_transfer(double __amount);
};

void Bank::bank_account_create(Account account)
{
    std::ofstream fp("Accounts.dat",std::ios::app | std::ios::binary);
    fp.write((char *)&account,sizeof(account));
    fp.close();
}

void Bank::bank_account_read_all()
{
    std::ifstream fp("Accounts.dat",std::ios::binary);
    Account account;
    while (fp.read((char *)&account,sizeof(account))) account.account_show();
    fp.close();
}


void Bank::bank_account_search()
{
    int choice; 
    Account account;
    std::ifstream fp("Accounts.dat",std::ios::binary);
    std::cout << "Enter the id of the account you want to find? ";
    std::cin >> choice;

    while (fp.read((char *)&account,sizeof(account))) if (choice == account.get_id()) account.account_show();
    
    fp.close(); 
}

void Bank::bank_account_delete()
{
    int choice; 

    Account account;
    std::ifstream fp("Accounts.dat",std::ios::binary);
    std::ofstream tmp("tmp.dat",std::ios::binary | std::ios::app);
    std::cout << "Enter the id of the account you want to delete? ";
    std::cin >> choice;

    while (fp.read((char *)&account,sizeof(account))) 
    {
        if (choice != account.get_id()) tmp.write((char*)&account,sizeof(account));

        if (choice == account.get_id()) account.account_show();
    }

    fp.close();
    tmp.close();

    int status = remove("Accounts.dat");
    if( status != 0 ) std::cout << "\nError Occurred!";

    if (rename("tmp.dat", "Accounts.dat") != 0) perror("Error renaming file\n");
}

 void Bank::bank_account_update_balance(double __balance,Account acc)
 {
    Account account;
    std::ifstream fp("Accounts.dat");
    std::ofstream tmp("tmp.dat",std::ios::binary | std::ios::app);
    int choice = acc.get_id();

    while (fp.read((char *)&account,sizeof(account)))
    {
        if (choice == account.get_id()) account.set_balance(__balance);

        tmp.write((char*)&account,sizeof(account));
    }

    fp.close();
    tmp.close();

    int status = remove("Accounts.dat");
    if( status != 0 ) std::cout << "\nError Occurred!";

    if (rename("tmp.dat", "Accounts.dat") != 0) perror("Error renaming file\n");
 }
 
 void Bank::bank_account_transfer(double __amount)
 {
  
    int choice;
    std::cout << "To whom do you want to transfer" << "\n";
    std::cin >> choice;
    
    Account account;
    std::ifstream fp("Accounts.dat");
    std::ofstream tmp("tmp.dat",std::ios::binary | std::ios::app);

    while (fp.read((char *)&account,sizeof(account)))
    {
        if (choice == account.get_id()) 
            account.set_balance(account.get_balance() + __amount);

            tmp.write((char*)&account,sizeof(account));
    }

    fp.close();
    tmp.close();

    int status = remove("Accounts.dat");
    if( status != 0 ) std::cout << "\nError Occurred!";

    if (rename("tmp.dat", "Accounts.dat") != 0) perror("Error renaming file\n");
}

void Bank::bank_account_menu(Account account)
{
    int choice;
    std::cout << "What do you want to do?" << std::endl;
    std::cout << "1 - Show Balance" << std::endl;
    std::cout << "2 - Deposit" << std::endl;
    std::cout << "3 - Withdraw" << std::endl;
    std::cout << "4 - Transfer" << std::endl;
    std::cout << "Choose a number: ";
    std::cin >> choice;

    switch (choice)
    {
    case 1:
        std::cout << "Your balance : $" << account.get_balance() << std::endl;
        break;
    case 2:
        account.account_deposit();
        bank_account_update_balance(account.get_balance(),account);
        break;
    case 3:
        account.account_withdraw();
        bank_account_update_balance(account.get_balance(),account);
        break;      
    case 4:
        bank_account_transfer(account.account_transfer());
        bank_account_update_balance(account.get_balance(),account);
        break;
    default:
        std::cout << "Invalid choice" << std::endl;
        break;
    }
}


void Bank::bank_account_login()
{
    int choice; 
    Account account;
    std::ifstream fp("Accounts.dat",std::ios::binary);
    std::cout << "Enter the id of the account you want to login? ";
    std::cin >> choice;

    while (fp.read((char *)&account,sizeof(account))) 
    {
        if (choice == account.get_id())
        {
            int pin;
            std::cout << "Enter your pin number: ";
            std::cin >> pin;
            fp.close(); 
            if (pin == account.get_pin()) bank_account_menu(account);
            else std::cout << "Wrong pin";
        }
    }
}

#endif