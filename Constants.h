// This file includes all the named constant values used throughout the entire program

#pragma once
#ifndef CONSTANTS_H
#define CONSTANTS_H

/*
	The required length of a valid national ID number.
	Used to validate user input when creating or modifying Person records.
*/
const int NATIONAL_ID_LENGTH = 14;

/*
	Defines the valid age range for a person to be eligible for account creation.
	MIN_AGE: minimum age allowed (18 years)
	MAX_AGE: maximum age allowed (100 years)
*/
const int MIN_AGE = 18, MAX_AGE = 100;

/*
	The minimum initial deposit required to create an account.
	Accounts cannot be created with a balance lower than this value.
*/
const double MIN_BALANCE = 1000;

/*
	The fixed interest rate (as a percentage) applied to all new certificate accounts.
	For example, a value of 50 means 50% interest rate.
*/
const double INTEREST_RATE_PERCENT = 25;

/*
	The number of seconds in a year.
	Used for calculating time-based operations like interest accumulation.
	Note: This accounts for leap years (31622400 seconds = 366 days * 24 * 60 * 60).
*/
const int SECONDS_IN_A_YEAR = 31622400;

#endif
