#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include <vector>
#include <string>
#include "Person.h"
#include "Program-Data-Functions.h"
#include "CertificateAccount.h"
#include "SavingAccount.h"
#include "BankAccount.h"

// Converts a Person object to a CSV-formatted string.
// Combines national ID, name, age, and phone number with commas.
string convertPersonObjectToCSVString(const Person& personObjectArgument)
{
    string csvString; // Stores the resulting CSV string.
    csvString.append(to_string(personObjectArgument.getNationalID())); // Appends the national ID.
    csvString.push_back(','); // Adds a comma separator.
    csvString.append(personObjectArgument.getName()); // Appends the name.
    csvString.push_back(','); // Adds a comma separator.
    csvString.append(to_string(personObjectArgument.getAge())); // Appends the age.
    csvString.push_back(','); // Adds a comma separator.
    csvString.append(personObjectArgument.getPhoneNumber()); // Appends the phone number.
    return csvString; // Returns the formatted CSV string.
}

// Converts a CSV string to a vector of strings.
// Splits the string at commas to extract individual fields.
vector<string> convertCSVStringToVector(const string& csvString)
{
    vector<string> stringVector; // Stores the resulting vector of fields.
    int startPosition = 0; // Tracks the start of the current substring.
    size_t commaPosition = csvString.find(',', startPosition); // Finds the next comma.
    while (commaPosition != string::npos)
    {
        string tempString = csvString.substr(startPosition, commaPosition - startPosition); // Extracts the substring from startPosition to one position before next comma.
        stringVector.push_back(tempString); // Adds the substring to the vector.
        startPosition = commaPosition + 1; // Updates the start position.
        commaPosition = csvString.find(',', startPosition); // Finds the next comma.
    }

    string tempString = csvString.substr(startPosition, commaPosition - startPosition); // Extracts the final substring.
    stringVector.push_back(tempString); // Adds the final substring to the vector.
    return stringVector; // Returns the vector of fields.
}

// Converts a CSV string representing a person to a Person object.
// Parses the CSV string into a vector and sets the Person object's attributes.
Person convertCSVPersonStringToPersonObject(const string& csvPersonString)
{
    Person person; // Creates a new Person object.
    vector<string> personVector = convertCSVStringToVector(csvPersonString); // Converts the CSV string to a vector.
    person.setNationalID(stoll(personVector[0])); // Sets the national ID.
    person.setName(personVector[1]); // Sets the name.
    person.setAge(stoi(personVector[2])); // Sets the age.
    person.setPhoneNumber(personVector[3]); // Sets the phone number.
    return person; // Returns the initialized Person object.
}

// Converts a SavingAccount object to a vector of strings for storage.
// Includes account ID, national ID, balance, creation date, and placeholders for certificate-specific fields.
vector<string> convertSavingAccountObjectToAccountVector(const SavingAccount& savingAccountObject)
{
    vector<string> accountVector; // Stores the resulting vector of account data.
    accountVector.push_back(to_string(savingAccountObject.getAccountID())); // Adds the account ID.
    accountVector.push_back(to_string(savingAccountObject.getPerson().getNationalID())); // Adds the person's national ID.
    accountVector.push_back(to_string(savingAccountObject.getBalance())); // Adds the balance.
    accountVector.push_back(savingAccountObject.getDateTime()); // Adds the creation date-time.
    accountVector.push_back(""); // Adds an empty string for interest rate (certificate-specific).
    accountVector.push_back(""); // Adds an empty string for withdrawn amount (certificate-specific).
    return accountVector; // Returns the account vector.
}

// Converts a CertificateAccount object to a vector of strings for storage.
// Includes account ID, national ID, balance, creation date, interest rate, and withdrawn amount.
vector<string> convertCertificateAccountObjectToAccountVector(const CertificateAccount& certificateAccountObject)
{
    vector<string> accountVector; // Stores the resulting vector of account data.
    accountVector.push_back(to_string(certificateAccountObject.getAccountID())); // Adds the account ID.
    accountVector.push_back(to_string(certificateAccountObject.getPerson().getNationalID())); // Adds the person's national ID.
    accountVector.push_back(to_string(certificateAccountObject.getBalance())); // Adds the balance.
    accountVector.push_back(certificateAccountObject.getDateTime()); // Adds the creation date-time.
    accountVector.push_back(to_string(certificateAccountObject.getInterestRate())); // Adds the interest rate.
    accountVector.push_back(to_string(certificateAccountObject.getWithdrawnAmount())); // Adds the withdrawn amount.
    return accountVector; // Returns the account vector.
}

// Converts a vector of strings to a CertificateAccount object.
// Retrieves the associated Person object and sets all account attributes.
CertificateAccount convertAccountVectorToCertificateAccountObject(vector<string>& accountVector)
{
    CertificateAccount certificateAccountObject; // Creates a new CertificateAccount object.
    Person person = searchPerson(stoll(accountVector[1])); // Retrieves the Person object by national ID.
    certificateAccountObject.setAccountID(stoi(accountVector[0])); // Sets the account ID.
    certificateAccountObject.setPerson(person); // Sets the associated Person.
    certificateAccountObject.setBalance(stod(accountVector[2])); // Sets the balance.
    certificateAccountObject.setTimeDate(accountVector[3]); // Sets the creation date-time.
    certificateAccountObject.setInterestRatePercent(stod(accountVector[4])); // Sets the interest rate.
    certificateAccountObject.setWithdrawnAmount(stod(accountVector[5])); // Sets the withdrawn amount.
    return certificateAccountObject; // Returns the initialized CertificateAccount object.
}

// Converts a vector of strings to a SavingAccount object.
// Retrieves the associated Person object and sets all account attributes.
SavingAccount convertAccountVectorToSavingAccountObject(vector<string>& accountVector)
{
    SavingAccount savingAccountObject; // Creates a new SavingAccount object.
    savingAccountObject.setAccountID(stoi(accountVector[0])); // Sets the account ID.
    Person person = searchPerson(stoll(accountVector[1])); // Retrieves the Person object by national ID.
    savingAccountObject.setPerson(person); // Sets the associated Person.
    savingAccountObject.setBalance(stod(accountVector[2])); // Sets the balance.
    savingAccountObject.setTimeDate(accountVector[3]); // Sets the creation date-time.
    return savingAccountObject; // Returns the initialized SavingAccount object.
}

// Converts a vector of strings to a CSV-formatted string.
// Joins the vector elements with commas.
string convertVectorToCSVString(vector<string>& vecObject)
{
    string csvString = ""; // Stores the resulting CSV string.
    for (int i = 0; i < vecObject.size(); i++)
    {
        csvString.append(vecObject[i]); // Appends the current element.
        if (i != vecObject.size() - 1)
            csvString.push_back(','); // Adds a comma separator unless it's the last element.
    }
    return csvString; // Returns the formatted CSV string.
}

// Converts a date-time string to a vector of its components.
// Splits the string at dashes to extract year, month, day, hour, minute, and second.
vector<string> convertDateTimeStringToDateTimeVector(string& dateTimeString)
{
    vector<string> dateTimeVector; // Stores the resulting vector of date-time components.
    int startPosition = 0; // Tracks the start of the current substring.
    size_t dashPosition = dateTimeString.find('-', startPosition); // Finds the next dash.
    while (dashPosition != string::npos)
    {
        string tempString = dateTimeString.substr(startPosition, dashPosition - startPosition); // Extracts the substring from startPosition to one position before next dash.
        dateTimeVector.push_back(tempString); // Adds the substring to the vector.
        startPosition = dashPosition + 1; // Updates the start position.
        dashPosition = dateTimeString.find('-', startPosition); // Finds the next dash.
    }

    string tempString = dateTimeString.substr(startPosition, dashPosition - startPosition); // Extracts the final substring.
    dateTimeVector.push_back(tempString); // Adds the final substring to the vector.
    return dateTimeVector; // Returns the vector of date-time components.
}

// Converts a date-time vector to a formatted date-time string.
// Converts the vector components to a time structure and formats it using ctime.
string convertDateTimeVectorToFormattedDateTimeString(vector<string> dateTimeVector)
{
    struct tm datetime; // Structure to hold the broken-down time.
    datetime.tm_year = stoi(dateTimeVector[0]); // Sets the year.
    datetime.tm_mon = stoi(dateTimeVector[1]); // Sets the month.
    datetime.tm_mday = stoi(dateTimeVector[2]); // Sets the day.
    datetime.tm_hour = stoi(dateTimeVector[3]); // Sets the hour.
    datetime.tm_min = stoi(dateTimeVector[4]); // Sets the minute.
    datetime.tm_sec = stoi(dateTimeVector[5]); // Sets the second.
    datetime.tm_isdst = -1; // Indicates daylight saving time is unknown.
    time_t timestamp = mktime(&datetime); // Converts the time structure to a timestamp.
    string dateTime = ctime(&timestamp); // Formats the timestamp as a string.
    dateTime.pop_back(); // Removes the trailing newline.
    return dateTime; // Returns the formatted date-time string.
}