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

        void menu(float balance)
        {
            int choice;
            std::cout << "What do you want to do?" << std::endl;
            std::cout << "1 - Show Balance" << std::endl;
            std::cout << "2 - Deposit" << std::endl;
            std::cout << "3 - Withdraw" << std::endl;
            std::cout << "Choose a number: ";
            std::cin >> choice;

            switch (choice)
            {
            case 1:
                show_balance();
                break;
            case 2:
                deposit();
                break;
            case 3:
                withdraw();  
                break;          
            default:
                std::cout << "Invalid choice" << std::endl;
                break;
            }
        }

        void deposit()
        {
            long double amount;
            std:: cout << "How much do you want to deposit?" << std::endl;
            std::cin >> amount;

            balance += amount;
            std::cout << "You deposited: $" << amount << std::endl;
            std::cout << "Your balance: $" << balance << std::endl;
        }
        void show_balance()
        {
            std::cout << "Your balance: $" << balance << std::endl;
        }

        void withdraw()
        {
            long double amount;
            std:: cout << "How much do you want to withdraw?" << std::endl;
            std::cin >> amount;
            balance -= amount;
            std::cout << "You withdrawed: $" << amount << std::endl;
            std::cout << "Your balance: $" << balance << std::endl;
        }

};

#endif