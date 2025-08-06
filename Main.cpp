#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include "Program-Data-Functions.h"
using namespace std;

// Entry point of the program, orchestrating the main application loop.
int main(void)
{
    // Loads all persons from the Persons.csv file into the persons vector.
    readAllSavedPersonsToThePersonsVector();
    // Loads all accounts from the Accounts.csv file into the accounts vector.
    readAllSavedAccountsToTheAccountsVector();
    char choice = 'Y'; // Stores the user's choice to continue or exit the program.
    // Displays a welcome message and the current local date and time.
    cout << "Welcome to the Banking System!" << endl;
    time_t timestamp = time(NULL);
    cout << ctime(&timestamp) << endl;
    cin.putback('\n'); // Inserts a newline into the input buffer to prevent issues with empty buffer checks.

    // Continues the program loop as long as the user chooses to proceed.
    while (toupper(choice) == 'Y')
    {
        // Exits the program if the input is invalid (e.g., non-integer input for an integer).
        if (cin.fail())
        {
            cout << "Error: Invalid input. Please enter a valid character." << endl;
            clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
            return 0;
        }
        // Displays the program menu and processes the user's selected option.
        startMenu();
        // Prompts the user to choose whether to continue or exit.
        cout << "Would you like to perform another operation? (Y/y for yes, any other key to exit): ";
        clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
        cin >> choice; // Reads the user's choice to continue or exit.
    }

    // Saves all accounts in the accounts vector to the Accounts.csv file to persist changes.
    writeAllSavedAccountToCSVFile();
    // Saves all persons in the persons vector to the Persons.csv file to persist changes.
    writeAllSavedPersonsToTheCSVFile();
    return 0; // Exits the program successfully.
}