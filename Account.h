#if !defined(ACCOUNT_H)
#define ACCOUNT_H
#include <iostream>
#include <ctime>
#include <fstream>
#include <random>

class Account {
    private:
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
    
    public:
        void account_create()
        {
            
            std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_int_distribution<std::mt19937::result_type> dist6(1,10000); 

            time_t now = time(0);
            char* dt = ctime(&now);
            tm *gmtm = gmtime(&now);
            dt = asctime(gmtm);

            id = dist6(rng);
            std::cout << "ID: " << id << std::endl;

            std::cin.ignore(1);
            std::cout << "Name: ";
            std::cin.getline(name,100);
    
            std::cout << "Pin: ";
            std::cin >> pin;
    
            std::cout << "Deposit: ";
            std::cin >> balance;

            std::cout << "Created at: " << dt;

            std::ofstream fp("Accounts.txt",std::ios::app);
            fp << "***************************" << std::endl;
            fp << "Account ID: " << id << std::endl;
            fp << "Account Name: " << name << std::endl;
            // fp << "Account ID: " << id;
            fp << "Account Balance: $" << balance << std::endl;
            fp << "Created at: " << dt << std::endl;
            fp.close();

	    }
         void account_view_all()
        {
             std::ifstream fp("Accounts.txt");
            std::cout << "Account's name: " << name << std::endl
            << "Account's balance: $" << balance << std::endl
            << "Member since: " << created_at << std::endl;  

            while (!fp.eof())
            {
                std::cout << "ID: " << id << std::endl;

                std::cout << "Name: ";

                std::cout << "Pin: ";

                std::cout << "Deposit: ";


            }
            
        
        }
};

#endif