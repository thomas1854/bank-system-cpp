#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include "BankAccount.h"
#include "CertificateAccount.h"
#include "Exceptions.h"
#include "Constants.h"
#include "Conversion-Functions.h"

// Calculates the number of years since the account's creation based on the provided date-time string in the format "Year-Month-Day-Hour-Minute-Second".
static int getYearsAfterCreation(string);

// Default constructor for CertificateAccount, initializing with default BankAccount values.
// Sets interest rate and withdrawn amount to 0.
CertificateAccount::CertificateAccount() : BankAccount()
{
    setInterestRatePercent(0); // Initializes the interest rate to 0.
    setWithdrawnAmount(0); // Initializes the withdrawn amount to 0.
}

// Parameterized constructor for CertificateAccount, initializing with a Person, balance, interest rate, and withdrawn amount.
// Inherits from BankAccount to set person and balance.
CertificateAccount::CertificateAccount(const Person& personArgument, double balanceArgument, double interestRatePercentArgument, double withdrawnAmountArgument) : BankAccount(personArgument, balanceArgument)
{
    setInterestRatePercent(interestRatePercentArgument); // Sets the specified interest rate.
    setWithdrawnAmount(withdrawnAmountArgument); // Sets the specified withdrawn amount.
}

// Withdraws the specified amount from the certificate account's saving balance.
// Throws exceptions for invalid amounts or insufficient balance.
// Overriden the withdraw pure virtual declaration in the BankAccount base class.
void CertificateAccount::withdraw(double amount)
{
    if (amount < 0)
    {
        throw InvalidAmountException(); // Throws an exception if the withdrawal amount is negative.
    }
    else
    {
        double balance = getBalance(); // Retrieves the base account balance.
        double savingBalance = getSavingBalance(); // Calculates the available saving balance.
        if (amount > savingBalance)
        {
            throw InsufficientBalanceException(); // Throws an exception if the withdrawal amount exceeds the saving balance.
        }
        else
        {
            withdrawnAmount += amount; // Updates the total withdrawn amount.
            setWithdrawnAmount(withdrawnAmount); // Sets the updated withdrawn amount.
        }
    }
}

// Sets the interest rate percentage for the certificate account.
void CertificateAccount::setInterestRatePercent(double interestRatePercentArgument)
{
    interestRatePercent = interestRatePercentArgument; // Assigns the provided interest rate.
}

// Sets the total withdrawn amount for the certificate account.
void CertificateAccount::setWithdrawnAmount(double withdrawnAmountArgument)
{
    withdrawnAmount = withdrawnAmountArgument; // Assigns the provided withdrawn amount.
}

// Calculates the available saving balance by subtracting the withdrawn amount from the total returns.
double CertificateAccount::getSavingBalance() const
{
    double totalProfit = getTotalReturns(); // Calculates the total returns based on interest.
    return totalProfit - withdrawnAmount; // Returns the remaining balance after withdrawals.
}

// Calculates the number of years since the account's creation based on the provided date-time string.
int getYearsAfterCreation(string dateTimeString)
{
    time_t now; // Stores the current time.
    time_t creationYear; // Stores the account's creation timestamp.
    struct tm datetime; // Structure to hold the broken-down time.
    vector<string> dateTimeVector = convertDateTimeStringToDateTimeVector(dateTimeString); // Converts the date-time string to a vector of time components.
    now = time(NULL); // Gets the current timestamp.
    datetime.tm_year = stoi(dateTimeVector[0]); // Sets the year from the date-time vector.
    datetime.tm_mon = stoi(dateTimeVector[1]); // Sets the month.
    datetime.tm_mday = stoi(dateTimeVector[2]); // Sets the day.
    datetime.tm_hour = stoi(dateTimeVector[3]); // Sets the hour.
    datetime.tm_min = stoi(dateTimeVector[4]); // Sets the minute.
    datetime.tm_sec = stoi(dateTimeVector[5]); // Sets the second.
    creationYear = mktime(&datetime); // Converts the time structure to a timestamp.
    int yearsAfterCreation = difftime(now, creationYear) / SECONDS_IN_A_YEAR; // Calculates the years since creation.
    return yearsAfterCreation; // Returns the number of years.
}

// Calculates the total returns for the certificate account based on the base balance, years since creation, and interest rate.
double CertificateAccount::getTotalReturns() const
{
    double baseBalance = getBalance(); // Retrieves the initial account balance.
    string dateTimeString = getDateTime(); // Gets the account's creation date-time string.
    int yearsAfterCreation = getYearsAfterCreation(dateTimeString); // Calculates the years since creation.
    return (baseBalance * yearsAfterCreation * (static_cast<double>(interestRatePercent) / 100)); // Returns the total returns using the interest formula.
}