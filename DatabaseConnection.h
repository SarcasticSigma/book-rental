//
// Created by coldc on 5/1/2022.
//

#ifndef BOOKRESERVATIONSYSTEM_V0_0_1_DATABASECONNECTION_H
#define BOOKRESERVATIONSYSTEM_V0_0_1_DATABASECONNECTION_H

#include <iostream>
#include <string>
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <ctime>
#include "Customer.h"

using std::string;
using std::ofstream;
using std::ifstream;


class DatabaseConnection {
private:
    string targetCustomerFile = "data/Customers.txt";
    string targetBookFile = "data/Books.txt";

public:
    vector<Customer> customerList;
    vector<Book> bookList;

    /// Constructor for a database connection.
    DatabaseConnection();

    /// Adds a customer to the database.
    /// \param customer The customer object to add to the database.
    void addCustomer(const Customer &customer);

    /// Adds a book to the database
    /// \param book The book object to add to the database.
    void addBook(const Book &book);

    /// Gets the current bookList from the class and saves it to the targetBookFile.
    void _saveBooks();

    /// Gets the current customerList from the class and saves it to the targetCustomerFile.
    void _saveCustomers();

    /// A method from https://www.systutorials.com/how-to-test-a-file-or-directory-exists-in-c/ to check if a directory exists.
    /// \param s A string representing the path to the directory.
    /// \return Whether the path exists.
    static bool IsPathExist(const std::string &s);

    /// A method from https://stackoverflow.com/a/12774387/14348143 to check if a file exists.
    /// \param name A string representing the path of the file.
    /// \return Whether the file exists.
    inline bool fileExists(const std::string &name);

    /// Loads the books from the relevant datafile.
    void loadBooks();

    /// Loads the customers from the relevant datafile.
    void loadCustomers();

    /// Saves the current book and customer list to the data files and then reloads their contents.
    void reloadData();

    /// Gets a list of the books that a given customer has currently borrowed.
    /// \param customerName The name of the customer.
    /// \return A vector of Book objects that are currently borrowed by the customer.
    vector<Book> getCustomersBorrowedBooks(const string &customerName);

    /// Deletes a customer from the database.
    /// \param customerName The name of the customer to delete.
    void deleteCustomer(const string &customerName);

    /// Rents a book to a customer.
    /// \param bookName The name of the book to rent.
    /// \param customerName The customer that's renting the book.
    void rentBook(string bookName, string customerName);

    /// Returns a book from rental.
    /// \param targetBookName The name of the book.
    /// \param targetCustomerName The name of the customer.
    void returnBook(string targetBookName, string targetCustomerName);
};


#endif //BOOKRESERVATIONSYSTEM_V0_0_1_DATABASECONNECTION_H
