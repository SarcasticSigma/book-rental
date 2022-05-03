#include <conio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdio>
#include <cstdlib>
#include "DatabaseConnection.h"
#include <sstream>
#include <sys/stat.h>
// for windows mkdir
#ifdef _WIN32

#include <direct.h>

#endif

#include <sys/stat.h>
#include <sys/stat.h>
#include <string>
#include <fstream>
#include <chrono>
using namespace std::literals;
DatabaseConnection::DatabaseConnection() {
//Checks if the data path exists, if it doesn't - creates it.
    if (!IsPathExist("data")) {
        _mkdir("data");
    }
    //If there's not a customer file, create a new one.
    if (!fileExists(targetCustomerFile)) {
        ofstream out(targetCustomerFile);
        out.close();
    } else {
        loadCustomers();

    }
    //If there's not a book file, create a new one.
    if (!fileExists(targetBookFile)) {
        ofstream out(targetBookFile);
        out.close();
    } else {
        loadBooks();
    }
}


// From https://www.systutorials.com/how-to-test-a-file-or-directory-exists-in-c/
bool DatabaseConnection::IsPathExist(const string &s) {
    struct stat buffer{};
    return (stat(s.c_str(), &buffer) == 0);
}

// From https://stackoverflow.com/a/12774387/14348143
bool DatabaseConnection::fileExists(const string &name) {
    struct stat buffer{};
    return (stat(name.c_str(), &buffer) == 0);
}


vector<Book> DatabaseConnection::getCustomersBorrowedBooks(const string &customerName) {
    vector<Book> booksBorrowedBy;
    for (Book b : bookList) {
        if (b.getBorrowedBy() == customerName) {
            booksBorrowedBy.push_back(b);
        }
    }
    return booksBorrowedBy;
}

void DatabaseConnection::addCustomer(const Customer &customer) {
    this->customerList.push_back(customer);
    reloadData();
}

void DatabaseConnection::addBook(const Book &book) {
    this->bookList.push_back(book);
    reloadData();
}

void DatabaseConnection::_saveBooks() {
    vector<Book> saveBookList = this->bookList;
    ofstream out(targetBookFile, ofstream::trunc);
    for (Book book : saveBookList) {
        out << book.getWritableString();
    }
    out.close();
}

void DatabaseConnection::_saveCustomers() {
    vector<Customer> saveCustomerList = this->customerList;
    ofstream out(targetCustomerFile, ofstream::trunc);
    for (Customer customer : saveCustomerList) {
        out << customer.getWritableString();
    }
    out.close();
}

void DatabaseConnection::deleteCustomer(const string &customerName) {
    int targetIndex;
    //TODO: Don't allow deletion unless no books are borrowed.
    for(int i =0; i<customerList.size(); i++){
        if(customerName == customerList[i].getName()){
            targetIndex = i;
        }
    }
    customerList.erase(customerList.begin()+targetIndex);
    reloadData();
}

void DatabaseConnection::reloadData() {
    _saveBooks();
    _saveCustomers();
    customerList.clear();
    bookList.clear();
    string serializedCustomer, serializedBook;

    ifstream myFile;
    myFile.open(targetCustomerFile);
    if (myFile.is_open()) {
        while (myFile) {
            std::getline(myFile, serializedCustomer);
            if (!serializedCustomer.empty()) {
                customerList.emplace_back(serializedCustomer);
            }
        }
    }
    myFile.close();
    myFile.open(targetBookFile);
    if (myFile.is_open()) {
        while (myFile) {
            std::getline(myFile, serializedBook);
            if (!serializedBook.empty()) {
                bookList.emplace_back(serializedBook);
            }
        }
    }
}

void DatabaseConnection::loadBooks() {

    bookList.clear();
    string serializedBook;

    ifstream myFile;

    myFile.close();
    myFile.open(targetBookFile);
    if (myFile.is_open()) {
        while (myFile) {
            std::getline(myFile, serializedBook);
            if (!serializedBook.empty()) {
                bookList.emplace_back(serializedBook);
            }
        }
    }

}

void DatabaseConnection::loadCustomers() {
    customerList.clear();
    ifstream myFile;
    string serializedCustomer;
    myFile.open(targetCustomerFile);
    if (myFile.is_open()) {
        while (myFile) {
            std::getline(myFile, serializedCustomer);
            if (!serializedCustomer.empty()) {
                customerList.emplace_back(serializedCustomer);
            }
        }
    }
}

void DatabaseConnection::rentBook(string bookName, string customerName) {
/*
    for(Book b : bookList){
        if(b.title == bookName){
//TODO Validate Rules
            if (true) {
                std::chrono::system_clock::time_point tp = std::chrono::system_clock::now();
                std::chrono::system_clock::time_point newTimePoint = tp + (7 * 24h);
                time_t tt = std::chrono::system_clock::to_time_t(newTimePoint);
                tm local_tm = *localtime(&tt);
                b.dueDate = local_tm;
                b.isAvailable = false;
                b.borrowedBy = customerName;
                Book newBook = b;
            }
        }
    }
//    bookList.at() = newBook;
  //  this->reloadData();*/
}
