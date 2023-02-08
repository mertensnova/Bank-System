#if !defined(PERSON_H)
#define PERSON_H
#include <iostream>
#include <ctime>

class Person {
    public:
        int id;
        std::string name;
        int pin;
        double balance;
        std::string created_at;
        
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
