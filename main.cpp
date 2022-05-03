/****************************************
* Student Name: Samuel Wiliams
* Date Due: May 3, 2022
* Date Submitted: May 3, 2022
* Program Name: BookReservationSystem
* Program Description: A book reservation system with a command line GUI.
****************************************/
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <ctime>
#include <chrono>
#include <conio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdio>
#include <cstdlib>
#include "DatabaseConnection.h"
#include <sstream>
#include <sys/stat.h>
// for windows mkdir
#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
#ifdef _WIN32

#include <direct.h>

#endif

#include <sys/stat.h>
#include <sys/stat.h>
#include <string>
#include <fstream>
#include <ctime>
#include "DatabaseConnection.h"

int getTargetFunction();

using std::cout;
using std::cin;
using std::vector;
using std::string;
using std::endl;
using std::ostream;
using std::istream;
using system_clock = std::chrono::system_clock;

tm getCurrentTime() {
    system_clock::time_point now = system_clock::now();
    time_t tt = system_clock::to_time_t(now);
    tm local_tm = *localtime(&tt);
    return local_tm;
}

int main() {
    while (true) {
        int target = getTargetFunction();
        DatabaseConnection db = DatabaseConnection();
        //Add Customer
        if (target == 1) {
            cout
                    << "Please enter the follow information pressing enter after each entry: "
                       "Name, "
                       "address, "
                       "and phone number." << endl;
            cin.ignore(1, '\n');
            string name, address, phoneNumber;
            std::getline(cin, name);
            std::getline(cin, address);
            std::getline(cin, phoneNumber);
            db.addCustomer(Customer(name, address, phoneNumber, getCurrentTime()));
        }
            //Delete Customer
        else if (target == 2) {
            do {
                string customerName;
                cout << "What's the name of the customer you would like to delete?";
                cin.ignore(1, '\n');
                std::getline(cin, customerName);
                bool flagCustomerExists = false;
                for (Customer customer : db.customerList) {
                    if (customer.getName() == customerName) {
                        flagCustomerExists = true;
                    }
                }
                if (!flagCustomerExists) {
                    cout << "That customer doesn't exists!";
                    break;
                }
                db.deleteCustomer(customerName);
            } while (false);
        }
            //Add Book
        else if (target == 3) {
            string title, author, publisher;
            string year, month, day;
            cout
                    << "Please enter the following information pressing entry after each entry: "
                       "Book Title, "
                       "Author, "
                       "Publisher, "
                       "Release year (number)"
                       "Release month (number)"
                       "Release day (number)" << endl;
            cin.ignore(1, '\n');
            std::getline(cin, title);
            std::getline(cin, author);
            std::getline(cin, publisher);
            std::getline(cin, year);
            std::getline(cin, month);
            std::getline(cin, day);

            db.addBook(Book(title, author, publisher, stoi(year) - 1900, stoi(month), stoi(day)));
        }
            //Rent Book
        else if (target == 4) {

            string targetBookName, targetCustomerName;
            cout << "Please enter the name of the customer borrowing the book:";
            cin.ignore(1, '\n');
            std::getline(cin, targetCustomerName);
            bool flagCustomerExists = false;
            for (Customer customer : db.customerList) {
                if (customer.getName() == targetCustomerName) {
                    flagCustomerExists = true;
                }
            }
            if (flagCustomerExists) {
                bool flagBookExists = false;
                cout << "Please enter the name of the book you want to borrow (ensure it's available)";

                std::getline(cin, targetBookName);

                for (Book bk : db.bookList) {
                    if (bk.title == targetBookName) {
                        flagBookExists = true;
                    }
                }
                if (flagBookExists) {
                    db.rentBook(targetBookName, targetCustomerName);
                } else { cout << "That book doesn't exists!"; }
            } else {
                cout << "That customer doesn't exists!";
            }

        }


            //Return Book
        else if (target == 5) {
            string targetBookName, targetCustomerName;
            cout << "Please enter the name of the customer you want to return a book from:";
            cin.ignore(1, '\n');
            std::getline(cin, targetCustomerName);
            bool flagCustomerExists = false;
            for (Customer customer : db.customerList) {
                if (customer.getName() == targetCustomerName) {
                    flagCustomerExists = true;
                }
            }

            if (flagCustomerExists && !db.getCustomersBorrowedBooks(targetCustomerName).empty()) {
                bool flagBookExists = false;
                bool flagBookIsRented = false;
                cout << "Please enter the name of the book you want to return:";

                std::getline(cin, targetBookName);

                for (const Book &bk : db.bookList) {
                    if (bk.title == targetBookName) {
                        flagBookExists = true;
                        if (bk.borrowedBy == targetCustomerName) {
                            flagBookIsRented = true;
                        }
                    }
                }
                if (flagBookExists && flagBookIsRented) {
                    db.returnBook(targetBookName, targetCustomerName);
                } else { cout << "That book doesn't exists!"; }
            } else {
                cout << "That customer doesn't exists!";
            }
        }
            //List all customers
        else if (target == 6) {
            cout << "Customer Name               Currently Borrowed Books               Due Date\n";
            vector<Customer> customerList = db.customerList;
            for (Customer c: customerList) {
                cout << c.getOverviewData();
            }
        }
            //List all books
        else if (target == 7) {
            vector<Book> bookList = db.bookList;
            cout << "Book Title              Borrowed By               Is available?\n";
            for (Book b: bookList) {
                cout << b.getOverviewData();

            }
        }
    }
}


int getTargetFunction() {
    int userInput;
    cout
            << "What would you like to do? \n1. Add customer\n2. Delete Customer\n3. Add book\n4. Rent a book out\n5. Return a book\n6. List all customers\n7. List all books"
            << endl;;

    while (true) {
        cin >> userInput;
        if (userInput > 0 && userInput <= 7) {
            break;
        } else {
            cout
                    << "Please select an option from the following: \n1. Add customer\n2. Delete Customer\n3. Add book\n4.Delete Book\n5. Rent a book out\n6. Return a book\n7. List all customers\n8. List all books"
                    << endl;
        }
    }
    cout << endl;
    return userInput;
}

#pragma clang diagnostic pop