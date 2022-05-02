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
