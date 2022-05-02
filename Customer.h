//
// Created by coldc on 5/1/2022.
//

#ifndef BOOKRESERVATIONSYSTEM_V0_0_1_CUSTOMER_H
#define BOOKRESERVATIONSYSTEM_V0_0_1_CUSTOMER_H

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include "Book.h"

using std::cout;
using std::cin;
using std::vector;
using std::string;
using std::endl;
using std::ostream;
using std::istream;

class Customer {
private:
    Customer(string name, string address, string phoneNumber, tm registerDate, vector<int> bookIds);

    string name, address, phoneNumber;
    tm registerDate{};
    vector<int> borrowedBookIds;

    //Checks if the customer can borrow more books.
    bool _canBorrowMoreBooks();

    /// Removes the book from the borrowed book list.
    /// \param book The book to remove.
    /// \return Whether the book was successfully removed.
    void _deleteBookIdFromRental(int bookId);



    /// Adds the book to the borrowed book list.
    /// \param book The book to add.
    void _addBookIdToRental(int bookId);

public:
    Customer(string name, string address, string phoneNumber, tm registerDate);

    Customer(string writtenString);

    static string encryptSpaces(const string &decryptedString);

    static string decryptSpaces(const string &encryptedString);


    //Getters and setters.
    void setName(string
                 name);

    void setAddress(string
                    address);

    void setPhoneNumber(string phoneNumber);

    void setRegisterDate(tm registerDate);

    string getName();

    string getAddress();

    string getPhoneNumber();

    tm getRegisterDate();

    /// Borrows a book to the customer.
    /// \param book The book to borrow.
    /// \return Whether or not the book was succesfully borrowed.
    bool borrowBook(Book book);

    /// Gets the amount the customer owes on a book.
    /// \return
    double getOwedForBook();

/// Sums the total owed for all borrowed books.
/// \return
    double getTotalOwed();

    double returnBook(Book book);

    vector<int> getBorrowedBookIds();

    std::string getWritableString();


    string getOverviewData();
};


#endif //BOOKRESERVATIONSYSTEM_V0_0_1_CUSTOMER_H
