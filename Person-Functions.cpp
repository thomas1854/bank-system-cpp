#include "Person-Functions.h"
#include "Person.h"
#include "Program-Data-Functions.h"
#include "Exceptions.h"
#include "Constants.h"
#include "Display-Functions.h"
#include "Conversion-Functions.h"

using namespace std;

// Creates a new person with the provided national ID, validates it, and checks for duplicates.
// Prompts the user to enter additional person details if the ID is valid and not already in use.
void createPerson(long long nationalID)
{
    if (lengthOfNumber(nationalID) == NATIONAL_ID_LENGTH) // Verifies if the national ID has the correct length.
    {
        Person personObject = searchPerson(nationalID); // Searches for a person with the given national ID; returns a default Person if not found.
        if (!isDefaultPerson(personObject)) // Checks if the person already exists in the system.
            cout << "Error: This client already exists in the system." << endl; // Informs the user if the person is already registered.
        else
        {
            personObject = fillPerson(nationalID); // Prompts the user to fill in the new person's details.
            persons.push_back(personObject); // Adds the new person to the persons vector.
            writeAllSavedPersonsToTheCSVFile(); // Saves all persons to the CSV file to persist the new person.
        }
    }
    else
    {
        cout << "Error: Invalid national ID. It must be " << NATIONAL_ID_LENGTH << " digits long." << endl; // Informs the user if the national ID length is invalid.
    }
}

// Prompts the user to input details for a new person with the given national ID.
// Validates the input and handles any exceptions thrown during validation.
Person fillPerson(long long personNationalID)
{
    string personName, personPhoneNumber; // Stores the person's name and phone number.
    int personAge = 0; // Stores the person's age.
    try
    {
        cout << "Please enter the person's name: "; // Prompts the user to enter the person's name.
        clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
        getline(cin, personName); // Reads the full name, including spaces.
        cin.putback('\n'); // Inserts a newline into the input buffer to prevent issues with empty buffer checks.
        cout << "Please enter the person's age: "; // Prompts the user to enter the person's age.
        cin >> personAge; // Reads the age.
        if (cin.fail())
        {
            cout << "Error: Invalid input. Please enter a valid number." << endl; // Exits the program if the input is invalid (e.g., non-integer input for an integer).
            clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
            exit(1);
        }
        cout << "Please enter the person's phone number: "; // Prompts the user to enter the phone number.
        clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
        cin >> personPhoneNumber; // Reads the phone number.
        if (cin.fail())
        {
            cout << "Error: Invalid input. Please enter a valid phone number." << endl; // Exits the program if the input is invalid (e.g., non-integer input for an integer).
            clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
            exit(1);
        }
        Person personObject(personName, personAge, personNationalID, personPhoneNumber); // Creates a Person object with the provided details.
        return personObject; // Returns the initialized Person object.
    }
    catch (InvalidAgeException)
    {
        cout << "Error: Invalid age entered. The valid age must be between " << MIN_AGE << " and " << MAX_AGE << "." << endl; // Informs the user of the valid age range.
        cout << "Please enter a valid age: ";
        clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
        cin >> personAge; // Reads the re-entered age.
        if (cin.fail())
        {
            cout << "Error: Invalid input. Please enter a valid number." << endl; // Exits the program if the input is invalid (e.g., non-integer input for an integer).
            clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
            exit(1);
        }
        while (personAge < MIN_AGE || personAge > MAX_AGE)
        {
            if (cin.fail())
            {
                cout << "Error: Invalid input. Please enter a valid number." << endl; // Exits the program if the input is invalid (e.g., non-integer input for an integer).
                clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
                exit(1);
            }
            cout << "Error: Invalid age entered. The valid age must be between " << MIN_AGE << " and " << MAX_AGE << "." << endl; // Prompts again for a valid age.
            cout << "Please enter a valid age: ";
            clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
            cin >> personAge; // Reads the re-entered age.
        }
        Person personObject(personName, personAge, personNationalID, personPhoneNumber); // Creates a Person object with the valid age.
        return personObject; // Returns the initialized Person object.
    }
    catch (InvalidNationalIDException)
    {
        cout << "Error: Invalid national ID. It must be " << NATIONAL_ID_LENGTH << " digits long." << endl; // Informs the user of the valid ID length.
        cout << "Please enter a valid national ID: ";
        clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
        cin >> personNationalID; // Reads the re-entered national ID.
        if (cin.fail())
        {
            cout << "Error: Invalid input. Please enter a valid number." << endl; // Exits the program if the input is invalid (e.g., non-integer input for an integer).
            clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
            exit(1);
        }
        while (lengthOfNumber(personNationalID) != NATIONAL_ID_LENGTH)
        {
            if (cin.fail())
            {
                cout << "Error: Invalid input. Please enter a valid number." << endl; // Exits the program if the input is invalid (e.g., non-integer input for an integer).
                clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
                exit(1);
            }
            cout << "Error: Invalid national ID. It must be " << NATIONAL_ID_LENGTH << " digits long." << endl; // Prompts again for a valid ID.
            cout << "Please enter a valid national ID: ";
            clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
            cin >> personNationalID; // Reads the re-entered national ID.
        }
        Person personObject(personName, personAge, personNationalID, personPhoneNumber); // Creates a Person object with the valid national ID.
        return personObject; // Returns the initialized Person object.
    }
    catch (EmptyPhoneNumber)
    {
        cout << "Error: The phone number cannot be empty." << endl; // Informs the user that an empty phone number is invalid.
        cout << "Please enter the person's phone number: ";
        clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
        cin >> personPhoneNumber; // Reads the re-entered phone number.
        if (cin.fail())
        {
            cout << "Error: Invalid input. Please enter a valid phone number." << endl; // Exits the program if the input is invalid (e.g., non-integer input for an integer).
            clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
            exit(1);
        }
        while (personPhoneNumber == "")
        {
            if (cin.fail())
            {
                cout << "Error: Invalid input. Please enter a valid phone number." << endl; // Exits the program if the input is invalid (e.g., non-integer input for an integer).
                clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
                exit(1);
            }
            cout << "Error: The phone number cannot be empty." << endl; // Prompts again for a non-empty phone number.
            cout << "Please enter the person's phone number: ";
            clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
            cin >> personPhoneNumber; // Reads the re-entered phone number.
        }
        Person personObject(personName, personAge, personNationalID, personPhoneNumber); // Creates a Person object with the valid phone number.
        return personObject; // Returns the initialized Person object.
    }
    catch (EmptyName)
    {
        cout << "Error: The name cannot be empty or contain commas." << endl; // Informs the user that an empty name or one with commas is invalid.
        cout << "Please enter the person's name: ";
        clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
        getline(cin, personName); // Reads the re-entered name, allowing spaces.
        cin.putback('\n'); // Inserts a newline into the input buffer to prevent issues with empty buffer checks.
        if (cin.fail())
        {
            cout << "Error: Invalid input. Please enter a valid name." << endl; // Exits the program if the input is invalid (e.g., non-integer input for an integer).
            clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
            exit(1);
        }
        while (personName == "")
        {
            if (cin.fail())
            {
                cout << "Error: Invalid input. Please enter a valid name." << endl; // Exits the program if the input is invalid (e.g., non-integer input for an integer).
                clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
                exit(1);
            }
            cout << "Error: The name cannot be empty or contain commas." << endl; // Prompts again for a non-empty name.
            cout << "Please enter the person's name: ";
            clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
            getline(cin, personName); // Reads the re-entered name.
            cin.putback('\n'); // Inserts a newline into the input buffer to prevent issues with empty buffer checks.
        }
        Person personObject(personName, personAge, personNationalID, personPhoneNumber); // Creates a Person object with the valid name.
        return personObject; // Returns the initialized Person object.
    }
}

// Displays all persons' information in a tabular format.
void listAllPersons()
{
    vector<vector<string>> personsTable = { {"NationalID", "Name", "Age", "Phone Number"} }; // Initializes the table with headers.
    for (Person& person : persons) // Iterates through each person in the persons vector.
    {
        string personCSV = convertPersonObjectToCSVString(person); // Converts the Person object to a CSV string.
        vector<string> personVector = convertCSVStringToVector(personCSV); // Converts the CSV string to a vector.
        personsTable.push_back(personVector); // Adds the person's data to the table.
    }
    printTable(personsTable); // Prints the persons' data in a tabular format.
}

// Displays a person's information and their associated accounts in two separate tables.
// Takes a Person object and retrieves their national ID for account matching.
void displayPerson(Person& personObject)
{
    string personCSV = convertPersonObjectToCSVString(personObject); // Converts the Person object to a CSV string.
    vector<string> personVector = convertCSVStringToVector(personCSV); // Converts the CSV string to a vector.
    vector<vector<string>> personTable = { {"NationalID", "Name", "Age", "Phone Number"}, personVector }; // Creates a table for the person's information.
    vector<vector<string>> accountsTable = { {"AccountID", "Account Type", "NationalID", "Balance", "Creation Date & Time", "Interest Rate", "Withdrawn Amount", "Saving Balance"} }; // Initializes the accounts table with headers.
    for (vector<string> account : accounts) // Iterates through all accounts.
    {
        if (account[1] == personVector[0]) // Checks if the account's national ID matches the person's national ID.
        {
            if (account.back() == "") // Determines if the account is a Saving Account (empty interest rate field).
            {
                account.push_back(""); // Adds an empty field for certificate-specific data.
                account.insert(account.begin() + 1, "Saving Account"); // Inserts the account type.
            }
            else // Handles Certificate Account.
            {
                CertificateAccount certificateAccountObject = convertAccountVectorToCertificateAccountObject(account); // Converts the account vector to a CertificateAccount object.
                account.push_back(to_string(certificateAccountObject.getSavingBalance())); // Calculates and adds the saving balance.
                account.insert(account.begin() + 1, "Certificate Account"); // Inserts the account type.
            }
            vector<string> dateTimeVector = convertDateTimeStringToDateTimeVector(account[4]); // Converts the account's date-time string to a vector.
            account[4] = convertDateTimeVectorToFormattedDateTimeString(dateTimeVector); // Formats the date-time for display.
            accountsTable.push_back(account); // Adds the modified account to the accounts table.
        }
    }
    cout << "Client Information:" << endl; // Displays a header for the person's information.
    printTable(personTable); // Prints the person's information table.
    cout << "Client Accounts:" << endl; // Displays a header for the accounts table.
    printTable(accountsTable); // Prints the accounts table.
}

// Searches for a person by their national ID and displays their information and accounts.
void readPerson()
{
    long long nationalID; // Stores the national ID to search for.
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
    if (isDefaultPerson(personObject)) // Checks if the returned person is a default (indicating not found).
    {
        cout << "Error: This person is not registered in the bank." << endl; // Informs the user if no person is found.
        return;
    }
    else
    {
        displayPerson(personObject); // Displays the person's information and accounts.
    }
}

// Updates a person's name, age, or phone number based on user input.
// Prompts for the national ID and new values, allowing unchanged fields to be skipped with '0'.
void updatePerson()
{
    long long nationalID; // Stores the national ID to search for.
    cout << "Please enter the person's national ID: "; // Prompts the user to input the national ID.
    clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
    cin >> nationalID; // Reads the national ID.
    if (cin.fail())
    {
        cout << "Error: Invalid input. Please enter a valid number." << endl; // Exits the program if the input is invalid (e.g., non-integer input for an integer).
        clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
        exit(1);
    }
    int personObjectIndex = searchPersonIndex(nationalID); // Searches for the person's index in the persons vector.
    if (personObjectIndex == -1) // Checks if the person was not found.
    {
        cout << "Error: This person is not registered in the bank." << endl; // Informs the user if no person is found.
        return;
    }

    Person personObject = persons[personObjectIndex]; // Retrieves the Person object.
    displayPerson(personObject); // Displays the person's current information and accounts.
    string newPersonName, newPhoneNumber; // Stores the new name and phone number.
    int newAge = 1; // Stores the new age, initialized to a non-zero value.

    cout << "Please enter the new name (or 0 to keep unchanged): "; // Prompts for a new name or 0 to skip.
    clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
    getline(cin, newPersonName); // Reads the new name, allowing spaces.
    cin.putback('\n'); // Inserts a newline into the input buffer to prevent issues with empty buffer checks.
    cout << "Please enter the new age (or 0 to keep unchanged): "; // Prompts for a new age or 0 to skip.
    cin >> newAge; // Reads the new age.
    if (cin.fail())
    {
        cout << "Error: Invalid input. Please enter a valid number." << endl; // Exits the program if the input is invalid (e.g., non-integer input for an integer).
        clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
        exit(1);
    }
    while ((newAge < MIN_AGE || newAge > MAX_AGE) && newAge != 0)
    {
        if (cin.fail())
        {
            cout << "Error: Invalid input. Please enter a valid number." << endl; // Exits the program if the input is invalid (e.g., non-integer input for an integer).
            clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
            exit(1);
        }
        cout << "Error: Invalid age entered. The valid age must be between " << MIN_AGE << " and " << MAX_AGE << "." << endl; // Prompts for a valid age.
        cout << "Please enter the new age (or 0 to keep unchanged): ";
        clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
        cin >> newAge; // Reads the re-entered age.
    }

    cout << "Please enter the new phone number (or 0 to keep unchanged): "; // Prompts for a new phone number or 0 to skip.
    clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
    cin >> newPhoneNumber; // Reads the new phone number.
    if (cin.fail())
    {
        cout << "Error: Invalid input. Please enter a valid phone number." << endl; // Exits the program if the input is invalid (e.g., non-integer input for an integer).
        clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
        exit(1);
    }

    try
    {
        if (newPersonName != "0") personObject.setName(newPersonName); // Updates the name if changed.
        if (newAge != 0) personObject.setAge(newAge); // Updates the age if changed.
        if (newPhoneNumber != "0") personObject.setPhoneNumber(newPhoneNumber); // Updates the phone number if changed.
        persons[personObjectIndex] = personObject; // Updates the person in the persons vector.
        writeAllSavedPersonsToTheCSVFile(); // Saves all persons to the CSV file to persist changes.
    }
    catch (EmptyName)
    {
        cout << "Error: The name cannot be empty or contain commas." << endl; // Informs the user that an empty name or one with commas is invalid.
        cout << "Please enter the person's name: ";
        clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
        getline(cin, newPersonName); // Reads the re-entered name.
        cin.putback('\n'); // Inserts a newline into the input buffer to prevent issues with empty buffer checks.
        if (cin.fail())
        {
            cout << "Error: Invalid input. Please enter a valid name." << endl; // Exits the program if the input is invalid (e.g., non-integer input for an integer).
            clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
            exit(1);
        }
        while (newPersonName == "")
        {
            if (cin.fail())
            {
                cout << "Error: Invalid input. Please enter a valid name." << endl; // Exits the program if the input is invalid (e.g., non-integer input for an integer).
                clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
                exit(1);
            }
            cout << "Error: The name cannot be empty or contain commas." << endl; // Prompts again for a non-empty name.
            cout << "Please enter the person's name: ";
            clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
            getline(cin, newPersonName); // Reads the re-entered name.
            cin.putback('\n'); // Inserts a newline into the input buffer to prevent issues with empty buffer checks.
        }
        if (newPersonName != "0") personObject.setName(newPersonName); // Updates the name if changed.
        if (newAge != 0) personObject.setAge(newAge); // Updates the age if changed.
        if (newPhoneNumber != "0") personObject.setPhoneNumber(newPhoneNumber); // Updates the phone number if changed.
        persons[personObjectIndex] = personObject; // Updates the person in the persons vector.
        writeAllSavedPersonsToTheCSVFile(); // Saves all persons to the CSV file to persist changes.
    }
    catch (InvalidAgeException)
    {
        cout << "Error: Invalid age entered. The valid age must be between " << MIN_AGE << " and " << MAX_AGE << "." << endl; // Informs the user of the valid age range.
        cout << "Please enter a valid age: ";
        clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
        cin >> newAge; // Reads the re-entered age.
        if (cin.fail())
        {
            cout << "Error: Invalid input. Please enter a valid number." << endl; // Exits the program if the input is invalid (e.g., non-integer input for an integer).
            clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
            exit(1);
        }
        while (newAge < MIN_AGE || newAge > MAX_AGE)
        {
            if (cin.fail())
            {
                cout << "Error: Invalid input. Please enter a valid number." << endl; // Exits the program if the input is invalid (e.g., non-integer input for an integer).
                clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
                exit(1);
            }
            cout << "Error: Invalid age entered. The valid age must be between " << MIN_AGE << " and " << MAX_AGE << "." << endl; // Prompts again for a valid age.
            cout << "Please enter a valid age: ";
            clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
            cin >> newAge; // Reads the re-entered age.
        }
        if (newPersonName != "0") personObject.setName(newPersonName); // Updates the name if changed.
        if (newAge != 0) personObject.setAge(newAge); // Updates the age if changed.
        if (newPhoneNumber != "0") personObject.setPhoneNumber(newPhoneNumber); // Updates the phone number if changed.
        persons[personObjectIndex] = personObject; // Updates the person in the persons vector.
        writeAllSavedPersonsToTheCSVFile(); // Saves all persons to the CSV file to persist changes.
    }
}

// Deletes a person and their associated accounts from the system after user confirmation.
// Prompts for the national ID and confirms deletion before proceeding.
void deletePerson()
{
    long long nationalID; // Stores the national ID to search for.
    cout << "Please enter the person's national ID: "; // Prompts the user to input the national ID.
    clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
    cin >> nationalID; // Reads the national ID.
    if (cin.fail())
    {
        cout << "Error: Invalid input. Please enter a valid number." << endl; // Exits the program if the input is invalid (e.g., non-integer input for an integer).
        clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
        exit(1);
    }
    int personObjectIndex = searchPersonIndex(nationalID); // Searches for the person's index in the persons vector.
    if (personObjectIndex == -1) // Checks if the person was not found.
    {
        cout << "Error: This person is not registered in the bank." << endl; // Informs the user if no person is found.
        return;
    }
    else
    {
        Person personObject = persons[personObjectIndex]; // Retrieves the Person object.
        char choice; // Stores the user's confirmation choice.
        displayPerson(personObject); // Displays the person's information and accounts.
        cout << "Deleting this person will also delete all associated accounts. Confirm with (Y/y): "; // Warns the user about account deletion.
        clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
        cin >> choice; // Reads the confirmation choice.
        if (cin.fail())
        {
            cout << "Error: Invalid input. Please enter a valid character." << endl; // Exits the program if the input is invalid (e.g., non-integer input for an integer).
            clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
            exit(1);
        }
        if (toupper(choice) == 'Y') // Checks if the user confirmed the deletion.
        {
            int first_account = -1; // Stores the index of the person's first account.
            int accounts_number = 0; // Counts the number of accounts associated with the person.
            sort(accounts.begin(), accounts.end(), [&](vector<string>& acc1, vector<string>& acc2) { return stoll(acc1[1]) < stoll(acc2[1]); }); // Sorts accounts by national ID for contiguous grouping.
            for (int i = 0; i < accounts.size(); i++) // Iterates through all accounts.
            {
                if (stoll(accounts[i][1]) == personObject.getNationalID()) // Checks if the account belongs to the person.
                {
                    if (first_account == -1) first_account = i; // Sets the first account index if not yet set.
                    accounts_number++; // Increments the count of the person's accounts.
                }
            }
            accounts.erase(accounts.begin() + first_account, accounts.begin() + first_account + accounts_number); // Removes the person's accounts.
            persons.erase(persons.begin() + personObjectIndex); // Removes the person from the persons vector.
            sort(accounts.begin(), accounts.end(), [&](vector<string>& acc1, vector<string>& acc2) { return stoi(acc1[0]) < stoi(acc2[0]); }); // Re-sorts accounts by accountID.
            cout << "The person and their accounts have been successfully deleted." << endl; // Confirms successful deletion.
            writeAllSavedAccountToCSVFile(); // Saves all accounts to the CSV file.
            writeAllSavedPersonsToTheCSVFile(); // Saves all persons to the CSV file.
        }
        else
            cout << "Deletion canceled. The person and their accounts remain in the system." << endl; // Informs the user if deletion was canceled.
    }
}