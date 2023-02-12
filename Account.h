#if !defined(ACCOUNT_H)
#define ACCOUNT_H
#include <iostream>
#include <ctime>
#include <fstream>
#include <random>

class Account {
    public:
        int id;
        char name[100];
        int pin;
        long double balance;
        char created_at[100];
        
        void deposit(double amount)
        {
            balance += amount;
            std::cout << "You deposited: " << amount << std::endl;
            std::cout << "Your balance: " << balance << std::endl;
        }
        void show_balance()
        {
            std::cout << "Your balance: " << balance << std::endl;
        }

        void withdraw(double amount)
        {
            balance -= amount;
            std::cout << "You withdrawed: " << amount << std::endl;
            std::cout << "Your balance: " << balance << std::endl;
        }

};

#endif