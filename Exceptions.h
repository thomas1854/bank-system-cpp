// This file contains the custom exception types used throughout the program
// to handle various invalid or unexpected situations gracefully.

// These are the include guards
#pragma once
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

/*
	Thrown when the entered age is outside the valid range
	(e.g., below the minimum or above the maximum allowed age).
*/
class InvalidAgeException {};

/*
	Thrown when the provided national ID number has fewer digits
	than the required valid length.
*/
class InvalidNationalIDException {};

/*
	Thrown when the entered balance is invalid,
	such as being negative or below the minimum threshold.
*/
class InvalidBalanceException {};

/*
	Thrown when an attempt is made to withdraw an amount
	exceeding the available balance or savings.
*/
class InsufficientBalanceException {};

/*
	Thrown when an invalid amount is provided for deposit or withdrawal.
	Example: negative values.
*/
class InvalidAmountException {};

/*
	Thrown when trying to create or use a Person object
	that has at least one missing or empty required field.
*/
class IncompletePersonException {};

/*
	Thrown when a file fails to open for reading,
	e.g., due to a missing or inaccessible file.
*/
class InvalidFileException {};

/*
	Thrown when attempting to create a new user with a national ID
	that already exists in the system.
*/
class ExistPersonException {};

/*
	Thrown when the name string is empty during a person update operation.
*/
class EmptyName {};

/*
	Thrown when the phone number string is empty during a person update operation.
*/
class EmptyPhoneNumber {};

#endif
