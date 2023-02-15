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

#endif