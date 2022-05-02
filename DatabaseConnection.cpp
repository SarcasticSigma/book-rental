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

DatabaseConnection::DatabaseConnection() {


    if (!IsPathExist("data")) {
        _mkdir("data");
    }

    if (!fileExists(targetCustomerFile)) {
        ofstream out(targetCustomerFile);
        out.close();
    }

    if (!fileExists(targetBookFile)) {
        ofstream out(targetBookFile, ofstream::app);
        out.close();
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

void DatabaseConnection::WriteCustomer(Customer customer) {

    ofstream out(targetCustomerFile, ofstream::app);
    out << customer.getWritableString();
    out.close();
}

void DatabaseConnection::loadCustomers() {
    string line;
    vector<Customer> readCustomers = vector<Customer>();
    ifstream infile("data/Customers.txt");
    while (infile >> line) {
        readCustomers.emplace_back(line);
    }
    this->customerList = readCustomers;
}

vector<Customer> DatabaseConnection::getCustomerList() {
    return this->customerList;
}

bool DatabaseConnection::deleteCustomer(const string &customerName) {
    return false;
}

vector<Book> DatabaseConnection::getBookList() {
    return bookList;
}

void DatabaseConnection::loadBooks() {

    string line;
    vector<Book> readBooks = vector<Book>();
    ifstream infile("data/Customers.txt");
    while (infile >> line) {
        readBooks.emplace_back(line);
    }
    this->bookList = readBooks;
}

void DatabaseConnection::WriteBook(Book book) {
    ofstream out(targetBookFile, ofstream::app);
    out << book.getWritableString();
    out.close();
}

vector<int> DatabaseConnection::getBorrowedBookIds() {
    vector<vector<string>> pairs = vector<vector<string>>();
    DatabaseConnection db = DatabaseConnection();
    vector<Customer> customers = db.getCustomerList();
    vector<Book> books = db.getBookList();
    for (Customer customer : customers) {
        pairs[0].push_back(customer.getName())
        for(int i : customer.getBorrowedBookIds()) {
            pairs[1].push_back(std::to_string(i));
        }
    }

    vector<int> borrowedIds = vector<int>();

    loadBooks();
    for (Book book : bookList) {
        borrowedIds.push_back(book.getBookId());
    }
    return borrowedIds;
}

//Based on https://stackoverflow.com/a/42114477/14348143
void eraseFileLine(std::string path, std::string eraseLine) {
    std::string line;
    std::ifstream fin;

    fin.open(path);
    // contents of path must be copied to a temp file then
    // renamed back to the path file
    std::ofstream temp;
    temp.open("data/temp.txt");

    while (getline(fin, line)) {
        // write all lines to temp other than the line marked for erasing
        if (line != eraseLine)
            temp << line << std::endl;
    }

    temp.close();
    fin.close();

    // required conversion for remove and rename functions
    const char *p = path.c_str();
    remove(p);
    rename("temp.txt", p);
}