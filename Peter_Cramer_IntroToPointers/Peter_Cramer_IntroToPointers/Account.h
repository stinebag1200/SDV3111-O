#pragma once
#include <iostream>

// Abstract Account class (base for Checking)
class Account {
protected:
    char accountName[50];                // Account holder's name
    unsigned int* accountId;             // Pointer to unique account ID
    double accountBalance;               // Current balance
    unsigned int* transactionLimit;      // Pointer to transaction limit
    unsigned int* overdraftFee;          // Pointer to overdraft fee
    double accountInterestRate;          // Annual interest rate

public:
    // Constructor: sets all fields (using pointers where required)
    Account(const char* name, unsigned int* id, double balance,
        unsigned int* limit, unsigned int* fee, double rate);

    virtual ~Account() = default;

    // Getters for all fields (dereference pointers where needed)
    const char* GetAccountName() const;
    unsigned int GetAccountId() const;
    double GetAccountBalance() const;
    unsigned int GetTransactionLimit() const;
    unsigned int GetOverdraftFee() const;
    double GetAccountInterestRate() const;

    // Pure virtual methods (must be implemented in derived classes)
    virtual void Withdraw(double* amount) = 0;
    virtual void Deposit(double* amount) = 0;
    virtual void AddInterest() = 0;
};
