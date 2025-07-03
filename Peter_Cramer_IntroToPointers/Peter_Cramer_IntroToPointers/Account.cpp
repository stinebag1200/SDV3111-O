#include "Account.h"
#include <cstring>

// Constructor sets all fields; uses strcpy_s for char array copy
Account::Account(const char* name, unsigned int* id, double balance,
    unsigned int* limit, unsigned int* fee, double rate)
    : accountId(id), accountBalance(balance), transactionLimit(limit),
    overdraftFee(fee), accountInterestRate(rate) {
    strcpy_s(accountName, sizeof(accountName), name);
}

// Getter for account name (returns char array)
const char* Account::GetAccountName() const { return accountName; }
// Getter for ID (dereference pointer)
unsigned int Account::GetAccountId() const { return *accountId; }
// Getter for balance
double Account::GetAccountBalance() const { return accountBalance; }
// Getter for limit (dereference pointer)
unsigned int Account::GetTransactionLimit() const { return *transactionLimit; }
// Getter for overdraft fee (dereference pointer)
unsigned int Account::GetOverdraftFee() const { return *overdraftFee; }
// Getter for interest rate
double Account::GetAccountInterestRate() const { return accountInterestRate; }
