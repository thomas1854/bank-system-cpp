// This is the specification file for the CertificateAccount class

/*
	This class inherits from BankAccount because a CertificateAccount
	is a specialized type of BankAccount with additional behaviors and data.
*/

// These are the include guards
#pragma once
#ifndef CERTIFICATEACCOUNT_H
#define CERTIFICATEACCOUNT_H

#include <vector>
#include "BankAccount.h"
#include "Constants.h"

class CertificateAccount : public BankAccount
{
private:
	double interestRatePercent;  // Stores the interest rate as a percentage (e.g., 50% is stored as 50.0)
	double withdrawnAmount;      // Stores the total amount already withdrawn from the account's returns

	// Sets the interest rate percentage
	void setInterestRatePercent(double);

	// Sets the withdrawn amount (with validation)
	void setWithdrawnAmount(double);

public:
	// Default constructor
	CertificateAccount();

	/*
		Parameterized constructor that initializes:
		- the associated Person,
		- the initial deposit,
		- the interest rate,
		- and the already withdrawn amount
	*/
	CertificateAccount(const Person&, double, double, double);

	// Inline getter for the interest rate
	double getInterestRate() const
	{
		return interestRatePercent;
	}

	// Inline getter for the withdrawn amount
	double getWithdrawnAmount() const
	{
		return withdrawnAmount;
	}

	/*
		Calculates the total interest earned since the account was created.
		Formula: (years since creation) * (initial deposit) * (interestRatePercent / 100)
	*/
	double getTotalReturns() const;

	/*
		Calculates the remaining available interest (savings) by subtracting
		the withdrawn amount from the total interest returns.
		Formula: totalReturns - withdrawnAmount
	*/
	double getSavingBalance() const;

	/*
		Overrides the pure virtual withdraw function from BankAccount.
		Withdraws from the available interest balance (with validation).
	*/
	void withdraw(double) override;

	/*
		Friend function declaration to allow access to the protected members of the base class
		(setAccountID and setDateTime). Used to convert a vector of strings (data of the account) into a CertificateAccount object.
	*/
	friend CertificateAccount convertAccountVectorToCertificateAccountObject(vector<string>&);
};

#endif
