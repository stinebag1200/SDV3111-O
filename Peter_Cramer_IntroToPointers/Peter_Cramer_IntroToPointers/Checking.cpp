#include "Checking.h"
#include <cstring>

Checking::Checking(const char* name, unsigned int* id, double balance,
    unsigned int* limit, unsigned int* fee, double rate,
    const char* nickname)
    : Account(name, id, balance, limit, fee, rate) {
    strcpy_s(accountNickname, sizeof(accountNickname), nickname);
}

const char* Checking::GetAccountNickname() const { return accountNickname; }

void Checking::Withdraw(double* amount) {
    if (*amount <= 0) return;
    if (*amount > *transactionLimit) return;

    accountBalance -= *amount;
    if (accountBalance < 0) {
        accountBalance -= *overdraftFee;
    }
}

void Checking::Deposit(double* amount) {
    if (*amount <= 0) return;
    accountBalance += *amount;
}

void Checking::AddInterest() {
    accountBalance += accountBalance * accountInterestRate;
}