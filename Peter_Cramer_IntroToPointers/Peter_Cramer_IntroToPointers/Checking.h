#pragma once
#include "Account.h"

// Checking class inherits from Account, adds nickname
class Checking : public Account {
private:
    char accountNickname[50]; // Additional nickname for account

public:
    // Constructor: sets all fields, passes base fields to Account
    Checking(const char* name, unsigned int* id, double balance,
        unsigned int* limit, unsigned int* fee, double rate,
        const char* nickname);

    // Getter for nickname
    const char* GetAccountNickname() const;

    // Override required methods
    void Withdraw(double* amount) override;
    void Deposit(double* amount) override;
    void AddInterest() override;
};
