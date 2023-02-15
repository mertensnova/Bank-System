#include <iostream>
#include "Account.h"
#include "Bank.h"

int main(void)
{
    Bank bank;
    Account account("Amr Ashebo");

    bank.bank_account_create(account);
    bank.bank_account_read_all();

    return 0;
}
