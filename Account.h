#if !defined(ACCOUNT_H)
#define ACCOUNT_H
#include <iostream>
#include <conio.h>
#include <ctime>
#include <random>
#include <fstream>
#include <cstring>
#include <typeinfo>

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
        Account( std::string __name);

        void set_pin();
        void set_balance();

        int get_id();
        int get_pin();
        int get_balance();

        void account_show();
        void account_deposit();
        void account_withdraw();
};

Account::Account() {}

Account::Account( std::string __name )
{
    time_t now = time(0);
    char* dt = ctime(&now);
    tm *gmtm = gmtime(&now);
    dt = asctime(gmtm); 
    srand(now);
 
    id = rand();
    strcpy(name,__name.c_str());
    std::cin.ignore(1);

    set_pin();
    
    set_balance();
    
    strcpy(created_at,dt);
};

void Account::set_pin()
{
    int __pin;
    std::cout << "Pin: ";
    std::cin >> __pin;
    std::cin.ignore(1);
    pin = __pin;
}

void Account::set_balance()
{
    double __balance;
    std::cout << "Balance: ";
    std::cin >> __balance;
    balance  = __balance;
}

int Account::get_id(){ return this->id;}
int Account::get_pin() {return this->pin;}
int Account::get_balance() {return this->balance;}

void Account::account_show()
{
    std::cout << std::endl << "ID: " << id << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Balance: " << balance << std::endl;
    std::cout << "Created At: " << created_at << std::endl;     
}

#endif