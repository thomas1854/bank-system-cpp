// This file includes the declarations of conversion functions.
// These functions are used to convert between different data types
// to simplify logic and facilitate storage and processing across the program.

#pragma once
#ifndef CONVERSIONFUNCTIONS_H
#define CONVERSIONFUNCTIONS_H

#include <vector>
#include <string>
#include "Person.h"
#include "SavingAccount.h"
#include "CertificateAccount.h"
using namespace std;

/*
	Converts a vector of strings into a single CSV-formatted string.
	Useful for writing structured data to a CSV file.
*/
string convertVectorToCSVString(vector<string>&);

/*
	Converts a Person object into a CSV-formatted string.
	Format: nationalID, name, age, phoneNumber
	Used for storing person data in CSV files.
*/
string convertPersonObjectToCSVString(const Person&);

/*
	Converts a CSV-formatted string into a vector of strings,
	where each vector element represents a field.
	Useful for parsing data read from a CSV file.
*/
vector<string> convertCSVStringToVector(const string&);

/*
	Converts a CSV-formatted string containing person data
	into a Person object.
*/
Person convertCSVPersonStringToPersonObject(const string&);

/*
	Converts a SavingAccount object into a vector of strings.
	Format: {accountID, nationalID, balance, formatted date, (Empty), (Empty)} 
	Empty fields to make the account vector of saving account to be as the same size as the certificate accounts (simplify printing process).
	Used for storing account data in a structured form.
*/
vector<string> convertSavingAccountObjectToAccountVector(const SavingAccount&);

/*
	Converts a CertificateAccount object into a vector of strings.
	Format: {accountID, nationalID, balance, formatted date,
			 interestRatePercent, withdrawnAmount}
*/
vector<string> convertCertificateAccountObjectToAccountVector(const CertificateAccount&);

/*
	Converts a vector of strings containing certificate account data
	into a CertificateAccount object.
	Also uses protected base class methods to set internal fields (setAccountID, setTimeDate).
*/
CertificateAccount convertAccountVectorToCertificateAccountObject(vector<string>&);

/*
	Converts a formatted date-time string into a vector of strings.
	Format: "Year-Month-Day-Hour-Minute-Second" becomes {Year, Month, Day, Hour, Minute, Second}
	Note: Year is years since 1900; Month, Day, Hour, Minute, and Second start from 0.
*/
vector<string> convertDateTimeStringToDateTimeVector(string&);

/*
	Converts a date-time vector (as strings) back into a single formatted string.
	Format: {Year, Month, Day, Hour, Minute, Second} becomes "Year-Month-Day-Hour-Minute-Second"
*/
string convertDateTimeVectorToFormattedDateTimeString(vector<string>);

/*
	Converts a vector of strings containing saving account data
	into a SavingAccount object.
	Also uses protected base class methods to set internal fields (setAccountID, setTimeDate).
*/
SavingAccount convertAccountVectorToSavingAccountObject(vector<string>&);

#endif
