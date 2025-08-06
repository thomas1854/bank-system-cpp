#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include "Display-Functions.h"
using namespace std;

// Prints a 2D vector as a formatted table, requiring all inner vectors to have the same size.
// Each inner vector represents a row, and columns are aligned based on the maximum width of each column.
void printTable(vector <vector<string>> table)
{
    vector<int> columnWidth(table[0].size(), 0); // Stores the maximum width of each column.
    int lineWidth = 0; // Stores the total width of the separator line.
    string line; // Stores the separator line string.

    // Iterates through the table to determine the maximum width of each column.
    for (auto& row : table)
    {
        for (int column = 0; column < columnWidth.size(); column++)
        {
            // Updates the column width to the maximum length of the cell content.
            columnWidth[column] = max(columnWidth[column], static_cast<int>(row[column].size()));
        }
    }

    // Calculates the total line width by summing column widths and accounting for vertical bars.
    for (auto& columnWidthField : columnWidth) lineWidth += columnWidthField;
    line = string(lineWidth + columnWidth.size() + 1, '-'); // Creates a separator line with the total width plus vertical bars.

    // Iterates through the table to print each row.
    for (auto& row : table)
    {
        cout << line << endl; // Prints a separator line before each row.
        cout << left << '|'; // Prints a vertical bar at the start of the row.
        for (int column = 0; column < columnWidth.size(); column++)
        {
            cout << setw(columnWidth[column]) << row[column] << '|'; // Prints the cell content with proper width and a vertical bar.
        }
        cout << endl; // Moves to the next line after printing the row.
    }

    // Prints a separator line after the last row.
    cout << line << endl;
}

// Creates and displays a table of program options.
void displayOptionsList()
{
    vector<vector<string>> list =
    { {"No.", "Option"},
        {"1.", "Add new person"},
        {"2.", "Create new account"},
        {"3.", "Search person"},
        {"4.", "Update person"},
        {"5.", "Update account"},
        {"6.", "List all persons"},
        {"7.", "List all accounts"},
        {"8.", "Delete person"},
        {"9.", "Delete account"},
    };

    // Prints the table of program options.
    printTable(list);
}

// Creates and displays a table of available account types.
void displayAccountTypes()
{
    vector<vector<string>> list =
    { {"No.", "Account Type"},
        {"1.", "Saving Account"},
        {"2.", "Certificate Account"},
    };

    cout << "A savings account is a bank account that allows deposits and withdrawals, maintaining a minimum balance, with no interest rate or withdrawal limits." << endl;
    cout << "A certificate account sets a base balance, earns annual interest based on a fixed interest rate percent at creation, and stores returns in the saving balance." << endl;
    // Prints the table of account types.
    printTable(list);
}

// Creates and displays a table of update options for accounts.
void displayUpdateChoices()
{
    vector<vector<string>> list =
    { {"No.", "Update Option"},
        {"1.", "Deposit"},
        {"2.", "Withdraw"},
    };

    // Prints the table of account update options.
    printTable(list);
}