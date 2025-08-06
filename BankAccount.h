// This is the specification file for the BankAccount class (Abstract Class)

// These are the include guards
#pragma once
#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <string>
#include "Person.h"
using namespace std;

class BankAccount
{
private:
	Person person;          // Holds the associated Person object
	double balance;         // Holds the account balance
	int accountID;          // Holds the unique ID of the account
	string dateTimeField;   // Holds the formatted date string [(Years since 1900)-(Months starting from 0)-(Days starting from 1)-(Hours starting from 0)-(Minutes starting from 0)-(Seconds starting from 0)]

protected:
	void setAccountID(int);         // Sets the account ID
	void setCreationDateTime();     // Sets the current local date in formatted form to dateTimeField
	void setTimeDate(string);       // Sets a specific formatted date string to dateTimeField

public:
	BankAccount();                                  // Default constructor
	BankAccount(const Person&, double);             // Parameterized constructor
	void setBalance(double);                        // Sets the balance (with validation)
	void setPerson(const Person&);                  // Sets the Person object

	// Inline getter for balance
	double getBalance() const
	{
		return balance;
	}

	// Inline getter for account ID
	int getAccountID() const
	{
		return accountID;
	}

	// Inline getter for the Person object
	Person getPerson() const
	{
		return person;
	}

	// Inline getter for the formatted date/time string
	string getDateTime() const
	{
		return dateTimeField;
	}

	// Pure virtual function for withdrawing money, 
	// behavior will differ depending on the specific type of account
	virtual void withdraw(double) = 0;
};

#endif
