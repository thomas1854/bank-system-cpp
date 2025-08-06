// This file contains the declarations of functions that manage
// the core logic and data flow of the program.

// These are the include guards
#pragma once
#ifndef PROGRAMDATA_H
#define PROGRAMDATA_H

#include <vector>
#include <algorithm>
#include "Conversion-Functions.h"
#include "Person.h"
using namespace std;

/*
	Global vector that holds all Person objects in the program.
	- Loaded from a CSV file at the start of the program
	- Written back to the CSV file at the end
	- Declared as 'extern' so it is defined only once and shared across all files
*/
extern vector<Person> persons;

/*
	Global vector that holds all account data as vectors of strings.
	- Loaded from a CSV file at the start of the program
	- Written back to the CSV file at the end
	- Declared as 'extern' so it is defined only once and shared across all files
*/
extern vector<vector<string>> accounts;

/*
	Writes all Person objects in the 'persons' vector to the CSV file.
	This function is typically called at the end of the program to save changes.
*/
void writeAllSavedPersonsToTheCSVFile();

/*
	Reads account data from the CSV file and loads it into the 'accounts' vector.
	This function is called at the beginning of the program.
*/
void readAllSavedAccountsToTheAccountsVector();

/*
	Reads person data from the CSV file and loads it into the 'persons' vector as Person objects.
	This function is called at the beginning of the program.
*/
void readAllSavedPersonsToThePersonsVector();

/*
	Writes all account records from the 'accounts' vector into a CSV file.
	Used to persist changes made during the program execution.
*/
void writeAllSavedAccountToCSVFile();

/*
	Checks whether a given Person object is uninitialized or contains default data.
	Used in search logic to determine if a search result is valid.
*/
bool isDefaultPerson(Person&);

/*
	Performs a binary search on the 'persons' vector using the national ID.
	Returns the matching Person object if found, otherwise returns a default-initialized Person.
*/
Person searchPerson(long long int);

/*
	Returns the number of digits in a given long long integer.
	Used for validating national ID input.
*/
int lengthOfNumber(long long);

/*
	Performs a binary search on the 'persons' vector using the national ID.
	Returns the index of the matching Person object if found, otherwise returns -1.
*/
int searchPersonIndex(long long int);

/*
	Displays the main program menu and manages user navigation and choices.
	This function serves as the entry point for user interaction.
*/
void startMenu();

/*
	Clears the input buffer.
	Used to handle and recover from input stream failures or leftover characters.
*/
void clearInputBufferFunc();

#endif