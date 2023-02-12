#if !defined(PERSON_H)
#define PERSON_H
#include <iostream>
#include <ctime>

class Person {
    private:
        int id;
        std::string name;
        int pin;
        long double balance;
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
    
    public:
        void account_create()
        {
            time_t now = time(0);
            char* dt = ctime(&now);
            tm *gmtm = gmtime(&now);
            dt = asctime(gmtm);

            std::cout << "Name: ";
            getline(std::cin >> std::ws, name);
    
            std::cout << "Pin: ";
            std::cin >> pin;
    
            std::cout << "Deposit: ";
            std::cin >> balance;

            std::cout << "Created at: " << dt;
            created_at  = dt;  
	    }
         void account_view()
        {
            std::cout << "Account's name: " << name << std::endl
            << "Account's balance: $" << balance << std::endl
            << "Member since: " << created_at << std::endl;
	    }
};

#endif