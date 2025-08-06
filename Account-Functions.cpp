#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include <string>
#include "Person.h"
#include "Person-Functions.h"
#include "Account-Functions.h"
#include "SavingAccount.h"
#include "CertificateAccount.h"
#include "Exceptions.h"
#include "Constants.h"
#include "Conversion-Functions.h"
#include "Program-Data-Functions.h"
#include "Display-Functions.h"

/*
Saves an account to the accounts vector and writes it to a CSV file.
Parameters: Person object to retrieve personNationalID, initial balance, and account type.
*/
static void saveAccount(Person&, double, string);

/*
Prompts the user to select an account type and enter an initial balance,
then creates a new account for the specified person.
*/
void createAccount(Person& person)
{
    string accountType = ""; // Stores the account type.
    double balance; // Stores the initial balance of the account.
    int choice; // Stores the user's account type selection.
    displayPerson(person); // Displays the person's information and accounts in tabular format.
    displayAccountTypes(); // Shows the available account types.
    cout << "Please select an account type: "; // Prompts the user to choose an account type.
    clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
    cin >> choice; // Reads the user's choice.

    // Exits the program if the input is invalid (e.g., non-integer input for an integer).
    if (cin.fail())
    {
        cout << "Error: Invalid input. Please enter a number." << endl;
        clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
        exit(1);
    }

    // Validates that the choice is either 1 or 2, looping until a valid choice is entered.
    while (choice < 1 || choice > 2)
    {
        // Exits the program if the input is invalid (e.g., non-integer input for an integer).
        if (cin.fail())
        {
            cout << "Error: Invalid input. Please enter a number." << endl;
            clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
            exit(1);
        }
        cout << "Error: Invalid choice. Please select 1 or 2." << endl;
        cout << "Please select an account type: ";
        clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
        cin >> choice; // Reads the re-entered choice.
    }

    // Assigns the account type based on the user's choice.
    switch (choice)
    {
    case 1:
        accountType = "SavingAccount";
        break;
    case 2:
        accountType = "CertificateAccount";
        break;
    }

    // Attempts to create an account and handle any balance-related exceptions.
    try
    {
        cout << "Enter the initial balance for the new account: ";
        clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
        cin >> balance; // Reads the initial balance.

        // Exits the program if the input is invalid (e.g., non-numeric input for a number).
        if (cin.fail())
        {
            cout << "Error: Invalid input. Please enter a valid number." << endl;
            clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
            exit(1);
        }

        // Creates the account with the specified type and balance.
        saveAccount(person, balance, accountType);
    }
    catch (InsufficientBalanceException)
    {
        // Handles cases where the initial balance is below the minimum required.
        cout << "Error: The minimum initial balance is $" << MIN_BALANCE << "." << endl;
        cout << "Please enter a valid initial balance: ";
        clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
        cin >> balance; // Reads the re-entered balance.

        // Exits the program if the input is invalid (e.g., non-numeric input for a number).
        if (cin.fail())
        {
            cout << "Error: Invalid input. Please enter a valid number." << endl;
            clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
            exit(1);
        }

        // Loops until a valid balance (above the minimum) is entered.
        while (balance < MIN_BALANCE)
        {
            // Exits the program if the input is invalid (e.g., non-numeric input for a number).
            if (cin.fail())
            {
                cout << "Error: Invalid input. Please enter a valid number." << endl;
                clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
                exit(1);
            }
            cout << "Error: The minimum initial balance is $" << MIN_BALANCE << "." << endl;
            cout << "Please enter a valid initial balance: ";
            clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
            cin >> balance; // Reads the re-entered balance.
        }

        // Creates the account with the valid balance.
        saveAccount(person, balance, accountType);
    }
}

/*
Saves an account to the accounts vector and writes it to a CSV file.
Parameters: Person object to retrieve personNationalID, initial balance, and account type.
*/
void saveAccount(Person& person, double balance, string accountType)
{
    // Creates and saves the account based on the specified type.
    if (accountType == "SavingAccount")
    {
        // Initializes a SavingAccount object with the person and balance.
        SavingAccount savingAccountObject(person, balance);
        // Converts the SavingAccount object to a vector for storage.
        vector<string> savingAccountVector = convertSavingAccountObjectToAccountVector(savingAccountObject);
        // Assigns a unique account ID based on the current size of the accounts vector.
        savingAccountVector[0] = to_string(accounts.size() + 1);
        // Adds the account vector to the accounts vector.
        accounts.push_back(savingAccountVector);
    }
    else
    {
        // Initializes a CertificateAccount object with the person, balance, current interest rate, and 0 withdrawn amount.
        CertificateAccount certificateAccountObject(person, balance, INTEREST_RATE_PERCENT, 0);
        // Converts the CertificateAccount object to a vector for storage.
        vector<string> certificateAccountVector = convertCertificateAccountObjectToAccountVector(certificateAccountObject);
        // Assigns a unique account ID based on the current size of the accounts vector.
        certificateAccountVector[0] = to_string(accounts.size() + 1);
        // Adds the account vector to the accounts vector.
        accounts.push_back(certificateAccountVector);
    }

    // Writes all accounts in the accounts vector to the CSV file.
    writeAllSavedAccountToCSVFile();
}

/*
Displays all accounts in the system in a tabular format, including account details
such as ID, type, national ID, balance, creation date, and additional fields for certificate accounts.
*/
void listAllAccounts()
{
    // Initializes a table with headers for displaying account information.
    vector<vector<string>> accountsTable = { {"AccountID", "Account Type", "NationalID", "Balance", "Creation Date & Time", "Interest Rate", "Withdrawn Amount", "Saving Balance"} };
    // Iterates through all accounts in the accounts vector.
    for (vector<string> account : accounts)
    {
        // Determines the account type and adds relevant data to the table.
        if (account.back() == "")
        {
            // For saving accounts, adds an empty string for the saving balance field.
            account.push_back("");
            account.insert(account.begin() + 1, "Saving Account"); // Inserts the account type.
        }
        else
        {
            // For certificate accounts, calculates and adds the saving balance.
            CertificateAccount certificateAccountObject = convertAccountVectorToCertificateAccountObject(account);
            account.push_back(to_string(certificateAccountObject.getSavingBalance()));
            account.insert(account.begin() + 1, "Certificate Account"); // Inserts the account type.
        }

        // Formats the creation date and time for display.
        vector<string> dateTimeVector = convertDateTimeStringToDateTimeVector(account[4]);
        account[4] = convertDateTimeVectorToFormattedDateTimeString(dateTimeVector);
        accountsTable.push_back(account); // Adds the modified account vector to the table.
    }

    // Prints the accounts table.
    printTable(accountsTable);
}

/*
Updates an account based on its type:
- Saving accounts: Allows deposits and withdrawals.
- Certificate accounts: Allows only withdrawals.
Prompts the user to enter the person's national ID, select an account, and provide the account ID.
*/
void updateAccount()
{
    long long nationalID; // Stores the person's national ID.
    cout << "Enter the person's national ID: "; // Prompts the user to input the national ID.
    clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
    cin >> nationalID; // Reads the national ID.

    // Exits the program if the input is invalid (e.g., non-integer input for an integer).
    if (cin.fail())
    {
        cout << "Error: Invalid input. Please enter a valid number." << endl;
        clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
        exit(1);
    }

    // Searches for the person by national ID.
    int personIndex = searchPersonIndex(nationalID);

    // If the person is not found, informs the user and exits the function.
    if (personIndex == -1)
    {
        cout << "Error: This person is not a client of the bank." << endl;
        return;
    }

    // Retrieves the person object and displays their information.
    Person personObject = persons[personIndex];
    displayPerson(personObject);
    int accountID = 1; // Stores the account ID to update.
    cout << "Enter the Account ID to update: "; // Prompts the user to input the account ID.
    clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
    cin >> accountID; // Reads the account ID.

    // Exits the program if the input is invalid (e.g., non-integer input for an integer).
    if (cin.fail())
    {
        cout << "Error: Invalid input. Please enter a valid number." << endl;
        clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
        exit(1);
    }

    // Loops until a valid account ID (within range) is entered.
    while (accountID > accounts.size() || accountID < 1)
    {
        // Exits the program if the input is invalid (e.g., non-integer input for an integer).
        if (cin.fail())
        {
            cout << "Error: Invalid input. Please enter a valid number." << endl;
            clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
            exit(1);
        }
        cout << "Error: Invalid Account ID. Please select a valid ID." << endl;
        cout << "Enter the Account ID to update: ";
        clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
        cin >> accountID; // Reads the re-entered account ID.
    }

    // Retrieves the account vector for the specified account ID.
    vector<string> accountVector = accounts[accountID - 1];
    // Loops until the account nationalID matches the person's national ID.
    while (stoll(accountVector[1]) != nationalID)
    {
        // Exits the program if the input is invalid (e.g., non-integer input for an integer).
        if (cin.fail())
        {
            cout << "Error: Invalid input. Please enter a valid number." << endl;
            clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
            exit(1);
        }
        cout << "Error: Invalid Account ID. Please select an account owned by this person." << endl;
        cout << "Enter the Account ID to update: ";
        clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
        cin >> accountID; // Reads the re-entered account ID.

        // Loops until a valid account ID (within range) is entered.
        while (accountID > accounts.size() || accountID < 1)
        {
            // Exits the program if the input is invalid (e.g., non-integer input for an integer).
            if (cin.fail())
            {
                cout << "Error: Invalid input. Please enter a valid number." << endl;
                clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
                exit(1);
            }
            cout << "Error: Invalid Account ID. Please select a valid ID." << endl;
            cout << "Enter the Account ID to update: ";
            clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
            cin >> accountID; // Reads the re-entered account ID.
        }

        // Updates the account vector with the new account data related to account ID.
        accountVector = accounts[accountID - 1];
    }

    // Determines the account type based on the last element (interest rate).
    if (accountVector.back() == "")
    {
        // Converts the account vector to a SavingAccount object.
        SavingAccount savingAccountObject = convertAccountVectorToSavingAccountObject(accountVector);
        displayUpdateChoices(); // Displays options for deposit or withdrawal.
        cout << "Please select an option: "; // Prompts the user to choose an option.
        int option; // Stores the user's option.
        clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
        cin >> option; // Reads the option.

        // Exits the program if the input is invalid (e.g., non-integer input for an integer).
        if (cin.fail())
        {
            cout << "Error: Invalid input. Please enter a valid number." << endl;
            clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
            exit(1);
        }

        // Loops until a valid option (1 or 2) is entered.
        while (option != 1 && option != 2)
        {
            // Exits the program if the input is invalid (e.g., non-integer input for an integer).
            if (cin.fail())
            {
                cout << "Error: Invalid input. Please enter a valid number." << endl;
                clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
                exit(1);
            }
            cout << "Error: Invalid option. Please select 1 or 2." << endl;
            cout << "Please select an option: ";
            clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
            cin >> option; // Reads the re-entered option.
        }

        double amount = -1; // Stores the deposit or withdrawal amount.

        // Handles deposit operation for option 1.
        if (option == 1)
        {
            cout << "Enter the deposit amount: "; // Prompts the user to enter the deposit amount.
            clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
            cin >> amount; // Reads the deposit amount.

            // Exits the program if the input is invalid (e.g., non-numeric input for a number).
            if (cin.fail())
            {
                cout << "Error: Invalid input. Please enter a valid number." << endl;
                clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
                exit(1);
            }

            // Loops until a positive deposit amount is entered.
            while (amount < 0)
            {
                // Exits the program if the input is invalid (e.g., non-numeric input for a number).
                if (cin.fail())
                {
                    cout << "Error: Invalid input. Please enter a valid number." << endl;
                    clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
                    exit(1);
                }
                cout << "Error: Invalid amount. Please enter a positive value." << endl;
                cout << "Enter the deposit amount: ";
                clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
                cin >> amount; // Reads the re-entered deposit amount.
            }

            // Performs the deposit operation.
            savingAccountObject.deposit(amount);
        }
        else
        {
            // Handles withdrawal operation for option 2.
            cout << "Enter the withdrawal amount: "; // Prompts the user to enter the withdrawal amount.
            clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
            cin >> amount; // Reads the withdrawal amount.

            // Loops until a positive withdrawal amount is entered.
            while (amount < 0)
            {
                // Exits the program if the input is invalid (e.g., non-numeric input for a number).
                if (cin.fail())
                {
                    cout << "Error: Invalid input. Please enter a valid number." << endl;
                    clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
                    exit(1);
                }
                cout << "Error: Invalid amount. Please enter a positive value." << endl;
                cout << "Enter the withdrawal amount: ";
                clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
                cin >> amount; // Reads the re-entered withdrawal amount.

                // Loops until the withdrawal amount is within the available balance.
                while (amount > savingAccountObject.getBalance() - MIN_BALANCE)
                {
                    // Exits the program if the input is invalid (e.g., non-numeric input for a number).
                    if (cin.fail())
                    {
                        cout << "Error: Invalid input. Please enter a valid number." << endl;
                        clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
                        exit(1);
                    }
                    cout << "Error: Insufficient funds. You are trying to withdraw $" << amount
                        << ", but your current balance is $" << savingAccountObject.getBalance()
                        << ". The account balance cannot be less than $" << MIN_BALANCE
                        << ". You can withdraw up to $" << savingAccountObject.getBalance() - MIN_BALANCE << "." << endl;
                    cout << "Enter the withdrawal amount: ";
                    clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
                    cin >> amount; // Reads the re-entered withdrawal amount.
                }
            }

            // Performs the withdrawal operation.
            savingAccountObject.withdraw(amount);
        }

        // Updates the account vector with the modified SavingAccount data.
        accountVector = convertSavingAccountObjectToAccountVector(savingAccountObject);
    }
    else
    {
        // Converts the account vector to a CertificateAccount object.
        CertificateAccount certificateAccountObject = convertAccountVectorToCertificateAccountObject(accountVector);
        double amount; // Stores the withdrawal amount.

        cout << "Enter the withdrawal amount: "; // Prompts the user to enter the withdrawal amount.
        clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
        cin >> amount; // Reads the withdrawal amount.

        // Loops until a positive withdrawal amount is entered.
        while (amount < 0)
        {
            // Exits the program if the input is invalid (e.g., non-numeric input for a number).
            if (cin.fail())
            {
                cout << "Error: Invalid input. Please enter a valid number." << endl;
                clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
                exit(1);
            }
            cout << "Error: Invalid amount. Please enter a positive value." << endl;
            cout << "Enter the withdrawal amount: ";
            clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
            cin >> amount; // Reads the re-entered withdrawal amount.

            // Loops until the withdrawal amount is within the available saving balance.
            while (amount > certificateAccountObject.getSavingBalance())
            {
                // Exits the program if the input is invalid (e.g., non-numeric input for a number).
                if (cin.fail())
                {
                    cout << "Error: Invalid input. Please enter a valid number." << endl;
                    clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
                    exit(1);
                }
                cout << "Error: Insufficient funds. You are trying to withdraw $" << amount
                    << ", but your current saving balance is $" << certificateAccountObject.getSavingBalance() << "." << endl;
                cout << "Enter the withdrawal amount: ";
                clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
                cin >> amount; // Reads the re-entered withdrawal amount.
            }
        }

        // Performs the withdrawal operation.
        certificateAccountObject.withdraw(amount);
        // Updates the account vector with the modified CertificateAccount data.
        accountVector = convertCertificateAccountObjectToAccountVector(certificateAccountObject);
    }

    // Updates the accounts vector with the modified account data.
    accounts[accountID - 1] = accountVector;
    // Saves the updated accounts to the CSV file.
    writeAllSavedAccountToCSVFile();
}

/*
Deletes an account by prompting the user to enter the person's national ID
and the account ID of the account to be deleted.
*/
void deleteAccount()
{
    long long nationalID; // Stores the person's national ID.
    cout << "Enter the person's national ID: "; // Prompts the user to input the national ID.
    clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
    cin >> nationalID; // Reads the national ID.

    // Exits the program if the input is invalid (e.g., non-integer input for an integer).
    if (cin.fail())
    {
        cout << "Error: Invalid input. Please enter a valid number." << endl;
        clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
        exit(1);
    }

    // Searches for the person by national ID.
    int personIndex = searchPersonIndex(nationalID);
    if (personIndex == -1)
    {
        cout << "Error: This person is not a client of the bank." << endl;
        return;
    }

    // Retrieves the person object and displays their information.
    Person personObject = persons[personIndex];
    displayPerson(personObject);
    int accountID; // Stores the account ID to delete.
    cout << "Enter the Account ID to delete: "; // Prompts the user to input the account ID.
    clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
    cin >> accountID; // Reads the account ID.

    // Exits the program if the input is invalid (e.g., non-integer input for an integer).
    if (cin.fail())
    {
        cout << "Error: Invalid input. Please enter a valid number." << endl;
        clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
        exit(1);
    }

    // Loops until a valid account ID (within range) is entered.
    while (accountID > accounts.size() || accountID < 1)
    {
        // Exits the program if the input is invalid (e.g., non-integer input for an integer).
        if (cin.fail())
        {
            cout << "Error: Invalid input. Please enter a valid number." << endl;
            clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
            exit(1);
        }
        cout << "Error: Invalid Account ID. Please select a valid ID." << endl;
        cout << "Enter the Account ID to delete: ";
        clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
        cin >> accountID; // Reads the re-entered account ID.
    }

    // Retrieves the account vector for the specified account ID.
    vector<string> accountVector = accounts[accountID - 1];
    // Loops until the account nationalID matches the person's national ID.
    while (stoll(accountVector[1]) != nationalID)
    {
        cout << "Error: Invalid Account ID. Please select an account owned by this person." << endl;
        cout << "Enter the Account ID to delete: ";
        clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
        cin >> accountID; // Reads the re-entered account ID.

        // Exits the program if the input is invalid (e.g., non-integer input for an integer).
        if (cin.fail())
        {
            cout << "Error: Invalid input. Please enter a valid number." << endl;
            clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
            exit(1);
        }

        // Loops until a valid account ID (within range) is entered.
        while (accountID > accounts.size() || accountID < 1)
        {
            // Exits the program if the input is invalid (e.g., non-integer input for an integer).
            if (cin.fail())
            {
                cout << "Error: Invalid input. Please enter a valid number." << endl;
                clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
                exit(1);
            }
            cout << "Error: Invalid Account ID. Please select a valid ID." << endl;
            cout << "Enter the Account ID to delete: ";
            clearInputBufferFunc(); // Ensures the input buffer is valid and empty for the next input.
            cin >> accountID; // Reads the re-entered account ID.
        }

        // Updates the account vector with the new account ID.
        accountVector = accounts[accountID - 1];
    }

    // Removes the account from the accounts vector.
    accounts.erase(accounts.begin() + (accountID - 1));
    // Saves the updated accounts to the CSV file.
    writeAllSavedAccountToCSVFile();
}