#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include "BankAccount.h"
#include "Exceptions.h"
#include "Constants.h"

// Constructor to initialize a BankAccount with a Person object and balance.
// Throws an InsufficientBalanceException if the balance is below the minimum.
BankAccount::BankAccount(const Person& personArgument, double balanceArgument)
{
    setPerson(personArgument); // Sets the person associated with the account.
    setBalance(balanceArgument); // Sets the balance, validating it against the minimum.
    setAccountID(0); // Initializes the account ID to 0.
    setCreationDateTime(); // Sets the account creation date and time.
}

// Default constructor to initialize a BankAccount with default values.
// Uses a default Person object and minimum balance.
BankAccount::BankAccount()
{
    setCreationDateTime(); // Sets the account creation date and time.
    setPerson(Person()); // Initializes with a default Person object.
    setBalance(MIN_BALANCE); // Sets the balance to the minimum allowed value.
    setAccountID(0); // Initializes the account ID to 0.
}

// Sets the account balance, ensuring it meets the minimum balance requirement.
// Throws an InsufficientBalanceException if the balance is too low.
void BankAccount::setBalance(double balanceArgument)
{
    if (balanceArgument < MIN_BALANCE)
    {
        throw InsufficientBalanceException(); // Throws an exception if the balance is below the minimum.
    }
    else
    {
        balance = balanceArgument; // Assigns the valid balance to the account.
    }
}

// Sets the account ID.
void BankAccount::setAccountID(int accountIDArgument)
{
    accountID = accountIDArgument; // Assigns the provided account ID.
}

// Sets the Person object associated with the account.
void BankAccount::setPerson(const Person& personArgument)
{
    person = personArgument; // Assigns the provided Person object to the account.
}

// Sets the creation date and time of the account using the current system time.
// Formats the timestamp as a string in the format "year-month-day-hour-minute-second".
void BankAccount::setCreationDateTime()
{
    time_t timestamp = time(NULL); // Gets the current timestamp.
    struct tm datetime = *localtime(&timestamp); // Converts the timestamp to a local time structure.
    dateTimeField = ""; // Initializes the date-time string.
    dateTimeField.append(to_string(datetime.tm_year)); // Appends the year.
    dateTimeField.push_back('-'); // Adds a separator.
    dateTimeField.append(to_string(datetime.tm_mon)); // Appends the month.
    dateTimeField.push_back('-'); // Adds a separator.
    dateTimeField.append(to_string(datetime.tm_mday)); // Appends the day.
    dateTimeField.push_back('-'); // Adds a separator.
    dateTimeField.append(to_string(datetime.tm_hour)); // Appends the hour.
    dateTimeField.push_back('-'); // Adds a separator.
    dateTimeField.append(to_string(datetime.tm_min)); // Appends the minute.
    dateTimeField.push_back('-'); // Adds a separator.
    dateTimeField.append(to_string(datetime.tm_sec)); // Appends the second.
}

// Sets the creation date and time of the account using a provided string in the format "year-month-day-hour-minute-second".
void BankAccount::setTimeDate(string timeDate)
{
    dateTimeField = timeDate; // Assigns the provided date-time string to the account.
}