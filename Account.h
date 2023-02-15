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

        void set_pin(int __pin);
        void set_balance( double __balance );

        int get_id();
        int get_pin();
        int get_balance();

        void account_show();
        void account_deposit();
        // void account_withdraw();
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

    int __pin;
    std::cout << "Pin: ";
    std::cin >> __pin;
    std::cin.ignore(1);
    set_pin(__pin);
    
    double __balance;
    std::cout << "Balance: ";
    std::cin >> __balance;
    set_balance(__balance);
    
    strcpy(created_at,dt);
};


int Account::get_id(){ return this->id;}
int Account::get_pin() {return this->pin;}
int Account::get_balance() {return this->balance;}

void Account::set_pin(int __pin) {this->pin = __pin;}
void Account::set_balance( double __balance ) {this->balance = __balance;}

void Account::account_show()
{
    std::cout << std::endl << "ID: " << id << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Balance: " << balance << std::endl;
    std::cout << "Created At: " << created_at << std::endl;     
}

void Account::account_deposit()
{
    double amount;
    std:: cout << "How much do you want to deposit?" << std::endl;
    this->balance += amount;
    std::cout << "You deposited: $" << amount << std::endl;
    std::cout << "Your balance: $" << balance << std::endl;
    
}

#endif