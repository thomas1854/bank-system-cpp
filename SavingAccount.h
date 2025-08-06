// This is the specification file for the SavingAccount class.

/*
	This class inherits from the BankAccount class,
	as a SavingAccount is a specific type of bank account
	with its own behavior for deposit and withdrawal.
*/

// These are the include guards
#pragma once
#ifndef SAVINGACCOUNT
#define SAVINGACCOUNT

#include <vector>
#include "BankAccount.h"
#include "Person.h"

class SavingAccount : public BankAccount
{
public:
	// Default constructor
	SavingAccount();

	/*
		Parameterized constructor that initializes the account
		with a Person object and an initial balance.
	*/
	SavingAccount(const Person&, double);

	/*
		Overrides the pure virtual withdraw function from BankAccount.
		Performs validation on the withdrawal amount and ensures that:
		- the amount is not negative
		- the balance remains above the minimum allowed after withdrawal
	*/
	void withdraw(double) override;

	/*
		Deposits a specified amount into the account.
		Validates the amount to ensure it is not negative.
	*/
	void deposit(double);

	/*
		Friend function declaration to allow access to protected base class methods:
		- setAccountID
		- setTimeDate
		This is used when converting a vector of account data into a SavingAccount object.
	*/
	friend SavingAccount convertAccountVectorToSavingAccountObject(vector<string>&);
};

#endif
