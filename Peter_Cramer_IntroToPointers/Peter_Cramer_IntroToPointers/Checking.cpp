#include "Checking.h"
#include <cstring>

// Constructor initializes Account base and sets nickname
Checking::Checking(const char* name, unsigned int* id, double balance,
    unsigned int* limit, unsigned int* fee, double rate,
    const char* nickname)
    : Account(name, id, balance, limit, fee, rate) {
    strcpy_s(accountNickname, sizeof(accountNickname), nickname);
}

// Getter for account nickname
const char* Checking::GetAccountNickname() const { return accountNickname; }

// Withdraws amount if valid; applies overdraft fee if balance goes below zero
void Checking::Withdraw(double* amount) {
    if (*amount <= 0) return;
    if (*amount > *transactionLimit) return;

    accountBalance -= *amount;
    if (accountBalance < 0) {
        accountBalance -= *overdraftFee; // Only if negative
    }
}

// Deposits a positive amount to balance
void Checking::Deposit(double* amount) {
    if (*amount <= 0) return;
    accountBalance += *amount;
}

// Adds interest to balance (simple interest for demonstration)
void Checking::AddInterest() {
    accountBalance += accountBalance * accountInterestRate;
}
