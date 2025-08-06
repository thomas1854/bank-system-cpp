#include <string>
#include <fstream>
#include <limits>
#include "Program-Data-Functions.h"
#include "Exceptions.h"
#include "Display-Functions.h"
#include <iostream>
#include "Person-Functions.h"
#include "Account-Functions.h"
using namespace std;

// Defines a global vector to store all Person objects, shared across translation units.
vector<Person> persons;
// Defines a global vector to store all account data as vectors of strings, shared across translation units.
vector<vector<string>> accounts;

// Writes all Person objects in the persons vector to the Persons.csv file for persistent storage.
void writeAllSavedPersonsToTheCSVFile()
{
    ofstream csvPersonsFile("./CSVs/Persons.csv", ios::out); // Opens the Persons.csv file in write mode.
    if (csvPersonsFile) // Checks if the file was opened successfully.
    {
        for (Person& person : persons) // Iterates through each Person object in the persons vector.
        {
            string csvPerson = convertPersonObjectToCSVString(person); // Converts the Person object to a CSV string.
            csvPersonsFile << csvPerson << endl; // Writes the CSV string to the file.
        }
        csvPersonsFile.close(); // Closes the file.
    }
    else
    {
        throw InvalidFileException(); // Throws an exception if the file failed to open, causing program termination.
    }
}

// Reads all person data from the Persons.csv file into the persons vector.
void readAllSavedPersonsToThePersonsVector()
{
    ifstream csvPersonsFile("./CSVs/Persons.csv", ios::in); // Opens the Persons.csv file in read mode.
    if (csvPersonsFile) // Checks if the file was opened successfully.
    {
        string csvStringPerson; // Stores each person's CSV string.
        while (getline(csvPersonsFile, csvStringPerson)) // Reads each line from the file.
        {
            Person person = convertCSVPersonStringToPersonObject(csvStringPerson); // Converts the CSV string to a Person object.
            persons.push_back(person); // Adds the Person object to the persons vector.
        }
        csvPersonsFile.close(); // Closes the file.
    }
    else
    {
        ofstream newCSVPersonsFile("./CSVs/Persons.csv", ios::out); // Creates the Persons.csv file if it does not exist.
        newCSVPersonsFile.close(); // Closes the newly created file.
    }
}

// Checks if a Person object is a default-constructed object (indicating it was not found or initialized).
bool isDefaultPerson(Person& person)
{
    Person defaultPerson = Person(); // Creates a default Person object for comparison.
    if (defaultPerson.getName() != person.getName() && defaultPerson.getAge() != person.getAge() &&
        defaultPerson.getNationalID() != person.getNationalID() && defaultPerson.getPhoneNumber() != person.getPhoneNumber())
        return false; // Returns false if any attribute differs from the default.
    else
        return true; // Returns true if the person matches the default.
}

// Searches for a person in the persons vector by national ID using a binary search algorithm.
// Returns the matching Person object or a default Person if not found.
Person searchPerson(long long int nationalID)
{
    Person person; // Initializes a default Person object to return if not found.
    sort(persons.begin(), persons.end()); // Sorts the persons vector by national ID for binary search.
    int left = 0, right = persons.size() - 1; // Sets the search boundaries.
    while (left <= right && left >= 0 && right <= persons.size() - 1)
    {
        int mid = (left + right) / 2; // Calculates the middle index.
        if (persons[mid].getNationalID() == nationalID)
            return persons[mid]; // Returns the matching Person object.
        else if (persons[mid].getNationalID() < nationalID)
            left = mid + 1; // Adjusts the search to the right half.
        else
            right = mid - 1; // Adjusts the search to the left half.
    }
    return person; // Returns a default Person object if no match is found.
}

// Searches for a person in the persons vector by national ID using a binary search algorithm.
// Returns the index of the person in the vector or -1 if not found.
int searchPersonIndex(long long int nationalID)
{
    sort(persons.begin(), persons.end()); // Sorts the persons vector by national ID for binary search.
    int left = 0, right = persons.size() - 1; // Sets the search boundaries.
    while (left <= right)
    {
        int mid = (left + right) / 2; // Calculates the middle index.
        if (persons[mid].getNationalID() == nationalID)
            return mid; // Returns the index of the matching person.
        else if (persons[mid].getNationalID() < nationalID)
            left = mid + 1; // Adjusts the search to the right half.
        else
            right = mid - 1; // Adjusts the search to the left half.
    }
    return -1; // Returns -1 if no match is found.
}

// Calculates the number of digits in a given number.
int lengthOfNumber(long long number)
{
    int lengthID = 0; // Stores the count of digits.
    while (number > 0)
    {
        lengthID++; // Increments the digit count.
        number /= 10; // Removes the last digit.
    }
    return lengthID; // Returns the total number of digits.
}

// Writes all account vectors in the accounts vector to the Accounts.csv file for persistent storage.
void writeAllSavedAccountToCSVFile()
{
    ofstream csvAccountsFile("./CSVs/Accounts.csv", ios::out); // Opens the Accounts.csv file in write mode.
    if (csvAccountsFile) // Checks if the file was opened successfully.
    {
        for (int id = 0; id < accounts.size(); id++) // Iterates through each account in the accounts vector.
        {
            accounts[id][0] = to_string(id + 1); // Updates the account ID based on its position.
            string accountCSVString = convertVectorToCSVString(accounts[id]); // Converts the account vector to a CSV string.
            csvAccountsFile << accountCSVString << endl; // Writes the CSV string to the file.
        }
        csvAccountsFile.close(); // Closes the file.
    }
    else
    {
        throw InvalidFileException(); // Throws an exception if the file failed to open.
    }
}

// Reads all account data from the Accounts.csv file into the accounts vector.
void readAllSavedAccountsToTheAccountsVector()
{
    ifstream csvAccountsFile("./CSVs/Accounts.csv", ios::in); // Opens the Accounts.csv file in read mode.
    if (csvAccountsFile) // Checks if the file was opened successfully.
    {
        string csvAccount; // Stores each account's CSV string.
        while (getline(csvAccountsFile, csvAccount)) // Reads each line from the file.
        {
            vector<string> accountVector = convertCSVStringToVector(csvAccount); // Converts the CSV string to a vector.
            accounts.push_back(accountVector); // Adds the account vector to the accounts vector.
        }
        csvAccountsFile.close(); // Closes the file.
    }
    else
    {
        ofstream newCSVAccountsFile("./CSVs/Accounts.csv", ios::out); // Creates the Accounts.csv file if it does not exist.
        newCSVAccountsFile.close(); // Closes the newly created file.
    }
}

// Clears the input buffer to ensure it is valid and ready for the next input.
void clearInputBufferFunc()
{
    std::cin.clear(); // Clears input stream flags.
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignores leftover characters until a newline.
}

// Displays the program menu, processes the user's choice, and directs the program flow accordingly.
void startMenu()
{
    displayOptionsList(); // Displays the list of program options.
    int choice; // Stores the user's menu choice.
    cout << "Please enter your choice (1-9): "; // Prompts the user to select a menu option.
    clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
    cin >> choice; // Reads the user's choice.
    if (cin.fail())
    {
        cout << "Error: Invalid input. Please enter a valid number." << endl; // Exits the program if the input is invalid (e.g., non-integer input for an integer).
        clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
        exit(1);
    }
    while (choice < 1 || choice > 9) // Validates that the choice is between 1 and 9.
    {
        if (cin.fail())
        {
            cout << "Error: Invalid input. Please enter a valid number." << endl; // Exits the program if the input is invalid (e.g., non-integer input for an integer).
            clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
            exit(1);
        }
        cout << "Error: Invalid choice. Please select a number between 1 and 9." << endl; // Prompts for a valid choice.
        cout << "Please enter your choice (1-9): ";
        clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
        cin >> choice; // Reads the re-entered choice.
    }

    switch (choice) // Executes the appropriate function based on the user's choice.
    {
    case 1:
    {
        long long nationalID; // Stores the national ID for creating a person.
        cout << "Please enter the person's national ID: "; // Prompts the user to input the national ID.
        clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
        cin >> nationalID; // Reads the national ID.
        if (cin.fail())
        {
            cout << "Error: Invalid input. Please enter a valid number." << endl; // Exits the program if the input is invalid (e.g., non-integer input for an integer).
            clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
            exit(1);
        }
        createPerson(nationalID); // Creates a new person with the provided national ID.
        break;
    }
    case 2:
    {
        long long nationalID; // Stores the national ID for creating an account.
        cout << "Please enter the person's national ID: "; // Prompts the user to input the national ID.
        clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
        cin >> nationalID; // Reads the national ID.
        if (cin.fail())
        {
            cout << "Error: Invalid input. Please enter a valid number." << endl; // Exits the program if the input is invalid (e.g., non-integer input for an integer).
            clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
            exit(1);
        }
        Person personObject = searchPerson(nationalID); // Searches for the person by national ID.
        if (isDefaultPerson(personObject))
        {
            cout << "Error: This national ID is not registered in the system." << endl; // Informs the user if the person is not found.
        }
        else
        {
            createAccount(personObject); // Creates an account for the found person.
        }
        break;
    }
    case 3:
    {
        long long nationalID; // Stores the national ID for searching a person.
        cout << "Please enter the person's national ID: "; // Prompts the user to input the national ID.
        clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
        cin >> nationalID; // Reads the national ID.
        if (cin.fail())
        {
            cout << "Error: Invalid input. Please enter a valid number." << endl; // Exits the program if the input is invalid (e.g., non-integer input for an integer).
            clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
            exit(1);
        }
        Person personObject = searchPerson(nationalID); // Searches for the person by national ID.
        if (isDefaultPerson(personObject))
        {
            cout << "Error: This national ID is not registered in the system." << endl; // Informs the user if the person is not found.
        }
        else
        {
            displayPerson(personObject); // Displays the found person's information and accounts.
        }
        break;
    }
    case 4:
    {
        updatePerson(); // Updates a person's information.
        break;
    }
    case 5:
    {
        updateAccount(); // Updates an account's (Deposit - Withdraw).
        break;
    }
    case 6:
    {
        listAllPersons(); // Displays all persons in a tabular format.
        break;
    }
    case 7:
    {
        listAllAccounts(); // Displays all accounts in a tabular format.
        break;
    }
    case 8:
    {
        deletePerson(); // Deletes a person and their associated accounts.
        break;
    }
    case 9:
    {
        deleteAccount(); // Deletes a specific account.
        break;
    }
    }
}