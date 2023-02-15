#include <iostream>
#include "Account.h"
#include "Bank.h"

int main(void)
{
    Bank bank;
    int choice;
    std::cout << "\t\t\t********************** Banking System****************************" << std::endl;
    std::cout << "\t\t\t********************** Main menu ****************************" << std::endl;
    std::cout << "\t1- Create an account" << std::endl;
    std::cout << "\t2- Login to an account" << std::endl;
    std::cout << "\t3- Show all accounts" << std::endl;
    std::cout << "\t4- Search account" << std::endl;
    std::cout << "\t5- Delete an account" << std::endl;
    std::cout << "\tChoose a number: ";
    std::cin >> choice;

    switch (choice)
    {
    case 1:
    {
        std::string name;
        std::cout << "Name: ";
        std::cin >> name;
        Account account(name);
        bank.bank_account_create(account);
        break;
    }
    case 2:
        
        break;
    case 3:
        bank.bank_account_read_all();
        break;
    case 4:
        bank.bank_account_search();
        break;
    case 5:
        bank.bank_account_delete();
        break;
    default:
        std::cout << "Invalid choice" << std::endl;
        break;
    }
    return 0;
}
