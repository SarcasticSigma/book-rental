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

    DatabaseConnection();

    void addCustomer(const Customer &customer);

    void addBook(const Book &book);

    void _saveBooks();

    void _saveCustomers();

    static bool IsPathExist(const std::string &s);

    inline bool fileExists(const std::string &name);

    void loadBooks();

    void loadCustomers();

    void reloadData();

    vector<string> getCustomersBorrowedBooks(const string &customerName);

    void deleteCustomer(const string &customerName);
};


#endif //BOOKRESERVATIONSYSTEM_V0_0_1_DATABASECONNECTION_H
