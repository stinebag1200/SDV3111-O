#include <iostream>
#include <climits>
#include <cstdio>
#include "Checking.h"

// Forward declarations for helper functions
void Print(Checking* checking);                // Prints all account info (values + addresses)
void RunWithdrawChecking(Checking* checking);  // Handles withdrawal process with validation
void RunDepositChecking(Checking* checking);   // Handles deposit process with validation

// Typedef for function pointer to Print function
typedef void (*PrintFuncPtr)(Checking*);

// Global function pointers to Print (for rubric: two different styles)
PrintFuncPtr printCheck = Print;
PrintFuncPtr printCheckMem = &Print;

// Prompts the user for a withdrawal, ensures valid input, and performs withdrawal
void RunWithdrawChecking(Checking* checking) {
    double amount;
    while (true) {
        std::cout << "Enter amount to withdraw: ";
        std::cin >> amount;

        // Validate input: must be positive number
        if (std::cin.fail() || amount <= 0) {
            std::cout << "Invalid amount. Please enter a positive number.\n";
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
            continue;
        }

        // Ensure amount does not exceed transaction limit
        if (amount > checking->GetTransactionLimit()) {
            std::cout << "Amount exceeds transaction limit. Try a smaller amount.\n";
            continue;
        }

        break; // Input is valid, exit loop
    }

    checking->Withdraw(&amount); // Pass address (pointer) as required by class
}

// Prompts the user for a deposit, ensures valid input, and performs deposit
void RunDepositChecking(Checking* checking) {
    double amount;
    while (true) {
        std::cout << "Enter amount to deposit: ";
        std::cin >> amount;

        // Validate input: must be positive number
        if (std::cin.fail() || amount <= 0) {
            std::cout << "Invalid amount. Please enter a positive number.\n";
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
            continue;
        }

        break; // Input is valid
    }

    checking->Deposit(&amount); // Pass pointer as required
}

// Prints all account details, including pointer addresses (matches rubric)
void Print(Checking* checking) {
    printf("Account Information\n");
    printf("Name: %s\n", checking->GetAccountName());
    printf("Nickname: %s\n", checking->GetAccountNickname());
    printf("ID: %u (Address: %p)\n", checking->GetAccountId(), (void*)checking->GetAccountId());
    printf("Balance: %.2f\n", checking->GetAccountBalance());
    printf("Transaction Limit: %u (Address: %p)\n", checking->GetTransactionLimit(), (void*)checking->GetTransactionLimit());
    printf("Overdraft Fee: %u (Address: %p)\n", checking->GetOverdraftFee(), (void*)checking->GetOverdraftFee());
    printf("Interest Rate: %.2f\n", checking->GetAccountInterestRate());
    printf("\n");
}

int main() {
    std::cout << "===Bad Bank LLC.===\n";
    std::cout << "==Default Checking==\n";

    // Initial/default account data
    unsigned int id = 1002;
    unsigned int limit = 100;
    unsigned int fee = 100;

    // Create default Checking object using pointers for id, limit, fee
    Checking defaultChecking("Urdnot Grunt", &id, 1000.0, &limit, &fee, 0.05, "Mr. Money");
    Checking* checkingPtr = &defaultChecking;

    // Print using both function pointers (for rubric demonstration)
    printCheck(checkingPtr);
    printCheckMem(checkingPtr);

    // Prompt for and perform withdrawal, print after
    RunWithdrawChecking(checkingPtr);
    printCheck(checkingPtr);

    // Prompt for and perform deposit, print after
    RunDepositChecking(checkingPtr);
    printCheck(checkingPtr);

    // Apply interest and print after
    checkingPtr->AddInterest();
    printCheck(checkingPtr);

    // Begin process for user-created Checking object
    std::cout << "==Created Checking==\n";

    char name[50], nickname[50];
    double balance, rate;
    unsigned int newId;

    // Prompt for name (use cin.ignore to clear newline)
    std::cout << "Enter account name: ";
    std::cin.getline(name, sizeof(name));
    std::cin.getline(name, sizeof(name));

    // Prompt for nickname
    std::cout << "Enter account nickname: ";
    std::cin.getline(nickname, sizeof(nickname));

    // Prompt for balance
    std::cout << "Enter account balance: ";
    std::cin >> balance;

    // Prompt for id
    std::cout << "Enter account ID: ";
    std::cin >> newId;

    // Prompt for interest rate
    std::cout << "Enter interest rate: ";
    std::cin >> rate;

    // Use previous limit and fee variables (pointer) for new object
    Checking userChecking(name, &newId, balance, &limit, &fee, rate, nickname);
    Checking* userCheckingPtr = &userChecking;

    // Print, withdraw, deposit, interest, and print after each (rubric order)
    printCheck(userCheckingPtr);

    RunWithdrawChecking(userCheckingPtr);
    printCheck(userCheckingPtr);

    RunDepositChecking(userCheckingPtr);
    printCheck(userCheckingPtr);

    userCheckingPtr->AddInterest();
    printCheck(userCheckingPtr);

    return 0;
}