#if !defined(ACCOUNT_H)
#define ACCOUNT_H
#include <iostream>
#include <conio.h>
#include <ctime>
#include <random>
#include <fstream>
#include <cstring>
#include <typeinfo>

#define BUFFER_SIZE 50

class Account
{
    private:
        int pin;
        double balance;
        int id;
        char name[BUFFER_SIZE];
        char created_at[BUFFER_SIZE];

    public:
        Account();
        Account( std::string __name);

        void set_pin(int __pin);
        void set_balance( double __balance );

        int get_id();
        int get_pin();
        int get_balance();

        void account_show();
        double account_deposit();
        double account_withdraw();
};

Account::Account() {}

Account::Account( std::string __name )
{
    strcpy(name,__name.c_str());
    
    time_t now = time(0);
    char* dt = ctime(&now);
    tm *gmtm = gmtime(&now);
    dt = asctime(gmtm); 
    srand(now);
 
    id = rand();

    int __pin;
    std::cout << "Pin: ";
    std::cin >> __pin;
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

double Account::account_deposit()
{
    double amount;
    std:: cout << "How much do you want to deposit?" << std::endl;
    std::cin >> amount;
    this->balance += amount;
    std::cout << "You deposited: $" << amount << std::endl;
    std::cout << "Your balance: $" << balance << std::endl;
    return this->balance;
}

double Account::account_withdraw()
{
    double amount;
    std:: cout << "How much do you want to withdraw?" << std::endl;
    std::cin >> amount;
    this->balance -= amount;
    std::cout << "You withdrew: $" << amount << std::endl;
    std::cout << "Your balance: $" << balance << std::endl;
    return this->balance;
}

#endif