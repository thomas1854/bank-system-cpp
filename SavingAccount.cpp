#include "SavingAccount.h"
#include "Exceptions.h"
#include "Constants.h"

// Default constructor to initialize a SavingAccount object.
// Inherits from BankAccount to set default base class members.
SavingAccount::SavingAccount() : BankAccount() {}

// Parameterized constructor to initialize a SavingAccount with a Person and balance.
// Inherits from BankAccount to set the person and balance with validation.
SavingAccount::SavingAccount(const Person& personArgument, double balanceArgument) : BankAccount(personArgument, balanceArgument) {}

// Withdraws the specified amount from the saving account with validation.
// Ensures the amount is non-negative and the remaining balance meets the minimum requirement.
// Overrides the pure virtual withdraw function from the BankAccount base class.
void SavingAccount::withdraw(double amount)
{
    double accountBalance = getBalance(); // Retrieves the current account balance.
    if (amount < 0) // Checks if the withdrawal amount is negative.
    {
        throw InvalidAmountException(); // Throws an exception for invalid (negative) amounts.
    }
    else if (accountBalance - amount < MIN_BALANCE) // Checks if the remaining balance would be below the minimum.
    {
        throw InsufficientBalanceException(); // Throws an exception if insufficient funds are available.
    }
    else
    {
        accountBalance -= amount; // Deducts the withdrawal amount from the balance.
        setBalance(accountBalance); // Updates the account with the new balance.
    }
}

// Deposits the specified amount into the saving account with validation.
// Ensures the deposit amount is non-negative.
void SavingAccount::deposit(double amount)
{
    double accountBalance = getBalance(); // Retrieves the current account balance.
    if (amount < 0)
    {
        throw InvalidAmountException(); // Throws an exception for invalid (negative) amounts.
    }
    else
    {
        accountBalance += amount; // Adds the deposit amount to the balance.
        setBalance(accountBalance); // Updates the account with the new balance.
    }
}