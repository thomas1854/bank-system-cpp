// This file contains the declarations of the account-related functions

// These are the include guards
#pragma once
#ifndef ACCOUNTFUNCTIONS_H
#define ACCOUNTFUNCTIONS_H

#include "Person.h"

/*
This function receives a Person object by reference. It prompts the user to choose an account type,
enter an initial balance, and then creates an account for that person.
*/
void createAccount(Person&);

/*
This function displays all accounts created in the system in a tabular format.
*/
void listAllAccounts();

/*
This function updates account data:
- For saving accounts: allows deposit and withdrawal
- For certificate accounts: allows only withdrawal
The user is prompted to enter the national ID of the person, choose one of their accounts,
and provide the account ID of the selected account to update.
*/
void updateAccount();

/*
This function deletes an account.
It prompts the user to enter the national ID of the person and then choose the account ID of the account to delete.
*/
void deleteAccount();

#endif
