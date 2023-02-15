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
    if( status == 0 ) std::cout<<"\nFile Deleted Successfully!";
    else std::cout<<"\nError Occurred!";

    if (rename("tmp.dat", "Accounts.dat") != 0) perror("Error renaming file\n");
	else std::cout << "File renamed successfully";
}

#endif