// This is the specification file for the Person class,
// which represents a person with identity and contact details.

// These are the include guards
#pragma once
#ifndef PERSON_H
#define PERSON_H

#include <string>
using namespace std;

class Person
{
private:
	string name;              // Stores the person's full name
	int age;                  // Stores the person's age
	long long int nationalID; // Stores the national ID number (unique identifier)
	string phoneNumber;       // Stores the person's phone number

public:
	// Default constructor
	Person();

	/*
		Parameterized constructor to initialize all fields:
		- name
		- age
		- national ID
		- phone number
	*/
	Person(string, int, long long int, string);

	// Sets the person's name
	void setName(string);

	// Sets the person's age with validation
	void setAge(int);

	// Sets the national ID with validation
	void setNationalID(long long int);

	// Sets the phone number
	void setPhoneNumber(string);

	/*
		Overloaded less-than operator.
		Used to compare two Person objects based on national ID,
		mainly for sorting and binary search purposes.
	*/
	bool operator<(Person&);

	/*
		Overloaded equality operator.
		Checks if two Person objects are identical in all fields.
	*/
	bool operator==(Person&);

	// Inline getter for the name
	string getName() const
	{
		return name;
	}

	// Inline getter for the phone number
	string getPhoneNumber() const
	{
		return phoneNumber;
	}

	// Inline getter for the age
	int getAge() const
	{
		return age;
	}

	// Inline getter for the national ID
	long long int getNationalID() const
	{
		return nationalID;
	}
};

#endif
