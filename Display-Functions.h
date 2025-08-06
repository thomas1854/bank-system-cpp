// This file contains the declarations of functions
// responsible for displaying tables and lists in the program.

#pragma once
#ifndef DISPLAYFUNCTIONS_H
#define DISPLAYFUNCTIONS_H

#include <vector>
#include <string>
using namespace std;

/*
	Displays the content of a 2D vector in a formatted table layout.
	Each inner vector represents a row.
	Note: All inner vectors must be of the same size for proper alignment.
*/
void printTable(vector<vector<string>>);

/*
	Displays the main menu options to the user.
	Called at the beginning of the program to present available actions.
*/
void displayOptionsList();

/*
	Displays the two account type options:
	- Saving Account
	- Certificate Account
	Used during account creation for user selection.
*/
void displayAccountTypes();

/*
	Displays the update options available for a Saving Account.
	Options include:
	- Deposit
	- Withdraw
*/
void displayUpdateChoices();

#endif