#pragma once
#include "Account.h"

class Checking : public Account {
private:
    char accountNickname[50];

public:
    Checking(const char* name, unsigned int* id, double balance,
        unsigned int* limit, unsigned int* fee, double rate,
        const char* nickname);

    const char* GetAccountNickname() const;

    void Withdraw(double* amount) override;
    void Deposit(double* amount) override;
    void AddInterest() override;
};