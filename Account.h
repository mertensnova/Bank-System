#if !defined(ACCOUNT_H)
#define ACCOUNT_H
#include <iostream>
#include <conio.h>
#include <ctime>
#include <random>
#include <fstream>
#include <cstring>
#include <typeinfo>
#include "Utils.h"

#define BUFFER_SIZE 100

class Account
{
    private:
        int pin;
        double balance;
        int id;
        char name[50];
        char created_at[50];

    public:
        Account();
        Account( std::string ___name );

        void set_name();
        void set_pin();
        void set_balance();
        void account_show();
};

Account::Account() {}

Account::Account( std::string ___name)
{
    time_t now = time(0);
    char* dt = ctime(&now);
    tm *gmtm = gmtime(&now);
    dt = asctime(gmtm); 
    srand(now);
 
    id = rand();

    set_name();

    set_pin();
    
    set_balance();
    
    strcpy(created_at,dt);
};

void Account::set_name()
{
    std::string __name;
    std::cout << "Name: ";
    std::cin >> __name;
    strcpy(name,__name.c_str());
}

void Account::set_pin()
{
    int __pin;
    std::cout << "Pin: ";
    std::cin >> __pin;
    pin = __pin;
}

void Account::set_balance()
{
    double __balance;
    std::cout << "Balance: ";
    std::cin >> __balance;
    balance  = __balance;
}

void Account::account_show()
{
    std::cout << "ID: " << id << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Balance: " << balance << std::endl;
    std::cout << "Created At: " << created_at << std::endl;     
}

#endif