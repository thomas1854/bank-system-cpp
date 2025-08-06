#include <string>
#include "Exceptions.h"
#include "Person.h"
#include "Constants.h"
#include "Program-Data-Functions.h"
using namespace std;

// Default constructor to initialize a Person object with empty or zeroed data members.
Person::Person()
{
    name = ""; // Initializes name as an empty string.
    age = 0; // Initializes age to 0.
    phoneNumber = ""; // Initializes phone number as an empty string.
    nationalID = 0; // Initializes national ID to 0.
}

// Parameterized constructor to initialize a Person object with specific data.
// Uses setters to validate and set the provided arguments.
Person::Person(string nameArgument, int ageArgument, long long int nationalIDArgument, string phoneNumberArgument)
{
    setName(nameArgument); // Sets and validates the name.
    setAge(ageArgument); // Sets and validates the age.
    setNationalID(nationalIDArgument); // Sets and validates the national ID.
    setPhoneNumber(phoneNumberArgument); // Sets and validates the phone number.
}

// Sets the person's name with validation to ensure it is not empty and does not contain commas.
// Throws an EmptyName exception if the name is invalid.
void Person::setName(string nameArgument)
{
    if (nameArgument == "" || nameArgument.find(',') != string::npos)
        throw EmptyName(); // Throws an exception if the name is empty or contains a comma.
    else
        name = nameArgument; // Assigns the valid name to the object.
}

// Sets the person's age with validation to ensure it is within the allowed range.
// Throws an InvalidAgeException if the age is out of range.
void Person::setAge(int ageArgument)
{
    if (ageArgument < MIN_AGE || ageArgument > MAX_AGE)
    {
        throw InvalidAgeException(); // Throws an exception if the age is invalid.
    }
    else
    {
        age = ageArgument; // Assigns the valid age to the object.
    }
}

// Sets the person's national ID with validation to ensure it has the correct length.
// Throws an InvalidNationalIDException if the ID is invalid.
void Person::setNationalID(long long int nationalIDArgument)
{
    int lengthID = lengthOfNumber(nationalIDArgument); // Calculates the number of digits in the national ID.
    if (lengthID == NATIONAL_ID_LENGTH)
    {
        nationalID = nationalIDArgument; // Assigns the valid national ID.
    }
    else
    {
        throw InvalidNationalIDException(); // Throws an exception if the ID length is invalid.
    }
}

// Sets the person's phone number with validation to ensure it is not empty.
// Throws an EmptyPhoneNumber exception if the phone number is empty.
void Person::setPhoneNumber(string phoneNumberArgument)
{
    if (phoneNumberArgument == "" || phoneNumberArgument.find(',') != string::npos)
        throw EmptyPhoneNumber(); // Throws an exception if the phone number is empty.
    else
        phoneNumber = phoneNumberArgument; // Assigns the valid phone number to the object.
}

// Overloads the less-than operator to compare two Person objects based on their national IDs.
// Useful for sorting and searching operations.
bool Person::operator<(Person& personObj)
{
    return nationalID < personObj.nationalID; // Returns true if this object's national ID is less than the other's.
}

// Overloads the equality operator to check if two Person objects are identical.
// Compares name, age, national ID, and phone number for equality.
bool Person::operator==(Person& personObj)
{
    if (name == personObj.name && age == personObj.age && nationalID == personObj.nationalID && phoneNumber == personObj.phoneNumber)
        return true; // Returns true if all attributes match.
    else
        return false; // Returns false if any attribute differs.
}