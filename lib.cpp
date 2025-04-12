#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
using namespace std;

class Library {
private:
    string name;
    string address;
    int accountNumber;
    int booksIssued;
    int booksReturned;
    vector<string> bookNamesIssued;
    vector<string> bookNamesReturned;
    static const int MAX_BOOKS = 5;  // Maximum books a user can issue

public:
    // Constructor with parameters
    Library(string visitorName, string homeAddress, int accNumber)
        : name(visitorName), address(homeAddress), accountNumber(accNumber),
          booksIssued(0), booksReturned(0) {
        if (accNumber <= 0) {
            throw invalid_argument("Account number must be positive");
        }
    }

    // Default constructor
    Library() : name("N/A"), address("N/A"), accountNumber(0),
                booksIssued(0), booksReturned(0) {}

    // Display account details
    void display() const {
        cout << "\n ----- ACCOUNT DETAILS -----" << endl;
        cout << "Name: " << name << endl;
        cout << "Address: " << address << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Number of Books Issued: " << booksIssued << endl;
        cout << "Number of Books Returned: " << booksReturned << endl;

        if (!bookNamesIssued.empty()) {
            cout << "Books Currently Issued: ";
            // Sort books for better readability
            vector<string> sortedIssued = bookNamesIssued;
            sort(sortedIssued.begin(), sortedIssued.end());
            for (const string& book : sortedIssued) {
                cout << book << ", ";
            }
            cout << endl;
        }

        if (!bookNamesReturned.empty()) {
            cout << "Books Returned: ";
            // Sort books for better readability
            vector<string> sortedReturned = bookNamesReturned;
            sort(sortedReturned.begin(), sortedReturned.end());
            for (const string& book : sortedReturned) {
                cout << book << ", ";
            }
            cout << endl;
        }
    }

    // Issue books
    bool issueBook(const string& bookName) {
        if (booksIssued >= MAX_BOOKS) {
            cout << "Error: Maximum number of books (" << MAX_BOOKS << ") already issued." << endl;
            return false;
        }

        if (bookName.empty()) {
            cout << "Error: Book name cannot be empty." << endl;
            return false;
        }

        // Check if book is already issued
        if (find(bookNamesIssued.begin(), bookNamesIssued.end(), bookName) != bookNamesIssued.end()) {
            cout << "Error: This book is already issued to you." << endl;
            return false;
        }

        bookNamesIssued.push_back(bookName);
        booksIssued++;
        cout << "Successfully issued book: " << bookName << endl;
        return true;
    }

    // Return books
    bool returnBook(const string& bookName) {
        auto it = find(bookNamesIssued.begin(), bookNamesIssued.end(), bookName);

        if (it == bookNamesIssued.end()) {
            cout << "Error: This book is not issued to you." << endl;
            return false;
        }

        bookNamesIssued.erase(it);
        bookNamesReturned.push_back(bookName);
        booksIssued--;
        booksReturned++;
        cout << "Successfully returned book: " << bookName << endl;
        return true;
    }

    // Close account and clear all data
    void closeAccount() {
        name = "N/A";
        address = "N/A";
        accountNumber = 0;
        booksIssued = 0;
        booksReturned = 0;
        bookNamesIssued.clear();
        bookNamesReturned.clear();
        cout << "Account closed successfully." << endl;
    }

    // Getters
    string getName() const { return name; }
    string getAddress() const { return address; }
    int getAccountNumber() const { return accountNumber; }
    int getBooksIssued() const { return booksIssued; }
    int getBooksReturned() const { return booksReturned; }
    vector<string> getIssuedBooks() const { return bookNamesIssued; }
    vector<string> getReturnedBooks() const { return bookNamesReturned; }

    // Check if account is active
    bool isActive() const {
        return accountNumber > 0 && name != "N/A";
    }

    // Clear all issued books (useful for account closure)
    void clearIssuedBooks() {
        bookNamesIssued.clear();
        booksIssued = 0;
    }
};

// Main function for interacting with the library system
int main() {
    try {
        // Creating a library account (you can modify this with real user input)
        Library user("Alice", "123 Main St", 1);

        // Display account details
        user.display();

        // Main menu loop
        while (true) {
            int choice;
            cout << "\n --- LIBRARY SYSTEM ---" << endl;
            cout << "1. Issue a book" << endl;
            cout << "2. Return a book" << endl;
            cout << "3. Display account details" << endl;
            cout << "4. Close account" << endl;
            cout << "5. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            if (choice == 1) {
                // Issue a book
                string bookName;
                cout << "Enter the name of the book to issue: ";
                cin.ignore();  // To ignore the newline from previous input
                getline(cin, bookName);
                user.issueBook(bookName);
            } 
            else if (choice == 2) {
                // Return a book
                string bookName;
                cout << "Enter the name of the book to return: ";
                cin.ignore();  // To ignore the newline from previous input
                getline(cin, bookName);
                user.returnBook(bookName);
            } 
            else if (choice == 3) {
                // Display account details
                user.display();
            } 
            else if (choice == 4) {
                // Close the account
                user.closeAccount();
                break;  // Exit after closing account
            } 
            else if (choice == 5) {
                // Exit the program
                break;
            } 
            else {
                cout << "Invalid choice. Please try again." << endl;
            }
        }

    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
