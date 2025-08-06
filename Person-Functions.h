// This file contains the declarations of the Person-related functions,
// including create, read, update, and delete operations.

// These are the include guards
#pragma once
#ifndef PERSONFUNCTIONS_H
#define PERSONFUNCTIONS_H

#include <iostream>
#include "Person.h"
using namespace std;

/*
	Creates a new person.
	Takes a national ID as an argument, validates it,
	checks if the person already exists, and if not,
	prompts the user to input the remaining data and creates the person.
*/
void createPerson(long long);

/*
	Fills a Person object.
	Takes a national ID as an argument and prompts the user to input
	the remaining data (name, age, phone number) with validation.
	Returns the fully constructed Person object.
*/
Person fillPerson(long long);

/*
	Lists all persons currently stored in the system.
	Displays the information in a tabular format.
*/
void listAllPersons();

/*
	Displays a specific person's details and their associated accounts.
	- Takes a Person object as an argument
	- Shows one table for the person's data
	- Shows another table for the person’s accounts (retrieved by national ID)
*/
void displayPerson(Person&);

/*
	Reads and displays a specific person's information.
	Asks the user to input a national ID, validates it,
	and if the person exists, displays their information.
*/
void readPerson();

/*
	Updates a person's information.
	Asks the user to input a national ID, validates it,
	checks if the person exists, and then allows updating
	the name, age, or phone number if any of them have changed.
*/
void updatePerson();

/*
	Deletes a person and all related account data from the system.
	Ensures complete removal based on national ID.
*/
void deletePerson();

#endif
