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
    if (!getCustomersBorrowedBooks(customerName).empty()) {
        cout << "Can't delete a user who still has books!";
        return;
    }
    int targetIndex;
    //TODO: Don't allow deletion unless no books are borrowed.
    for (int i = 0; i < customerList.size(); i++) {
        if (customerName == customerList[i].getName()) {
            targetIndex = i;
        }
    }
    customerList.erase(customerList.begin() + targetIndex);
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
    if (getCustomersBorrowedBooks(customerName).size() >= 7) {
        cout << "Can't rent a book, already has 7";
        return;
    }

    int targetIndex = -1;
    for (int i = 0; i < bookList.size(); i++) {
        if (bookName == bookList[i].title) {
            targetIndex = i;
        }
    }
    Book updatedBook = bookList[targetIndex];
    updatedBook.borrowedBy = customerName;
    std::chrono::system_clock::time_point tp = std::chrono::system_clock::now();
    std::chrono::system_clock::time_point newTimePoint = tp + (7 * 24h);
    time_t tt = std::chrono::system_clock::to_time_t(newTimePoint);
    tm local_tm = *localtime(&tt);
    updatedBook.dueDate = local_tm;
    updatedBook.isAvailable = false;

    bookList.erase(bookList.begin() + targetIndex);

    if (targetIndex == 0) {
        bookList.insert(bookList.begin() + targetIndex, updatedBook);
    } else {
        bookList.insert(bookList.begin() + targetIndex - 1, updatedBook);
    }
    reloadData();

}


/// Returns a book from a customer.
/// \param targetBookName The name of the book to be returned.
/// \param targetCustomerName The name of the customer from which the book is being returned.
/// \return A double representing a price in USD that the rental of the book cost.
void DatabaseConnection::returnBook(string targetBookName, string targetCustomerName) {
    int targetIndex = -1;
    for (int i = 0; i < bookList.size(); i++) {
        if (targetBookName == bookList[i].title) {
            targetIndex = i;
        }
    }
    std::chrono::system_clock::time_point tp = std::chrono::system_clock::now();
    time_t tt = std::chrono::system_clock::to_time_t(tp);
    tm currentTime = *localtime(&tt);

    double owedFees = 0.0;
    int years, months, days;
    Book finalCopy = bookList[targetIndex];
    const int monthDays[12] = {31, 28, 31, 30, 31, 30,
                               31, 31, 30, 31, 30, 31};
    int dueDateMonth, dueDateDay, dueDateYear;

    dueDateDay = finalCopy.dueDate.tm_mday;

    dueDateMonth = finalCopy.dueDate.tm_mon;

    dueDateYear = finalCopy.dueDate.tm_year;

    int totalLateDaysElapsed = 0;
    int monthdaysElapsed = currentTime.tm_mday - dueDateDay;
    int monthsElapsed = currentTime.tm_mon - dueDateMonth;
    int yearsElapsed = (currentTime.tm_year + 1900) - dueDateYear;
    totalLateDaysElapsed += monthdaysElapsed;
    for (int i = dueDateMonth; i < currentTime.tm_mon; i++) {
        totalLateDaysElapsed += monthDays[i];

    }
    totalLateDaysElapsed += yearsElapsed * 365;

    if (totalLateDaysElapsed > 1) {
        owedFees = 3 * (totalLateDaysElapsed);
    } else if (totalLateDaysElapsed <= 0) {
        owedFees = 0;
    }
    Book updatedBook = bookList[targetIndex];
    updatedBook.borrowedBy = "None";
    updatedBook.dueDate = tm();
    updatedBook.dueDate.tm_year = 0;
    updatedBook.dueDate.tm_mon = 0;
    updatedBook.dueDate.tm_mday = 0;
    updatedBook.isAvailable = true;
    bookList.erase(bookList.begin() + targetIndex);
    if (targetIndex == 0) {
        bookList.insert(bookList.begin() + targetIndex, updatedBook);
    } else {
        bookList.insert(bookList.begin() + targetIndex - 1, updatedBook);
    }
    reloadData();


    //Detail Report:
    cout<< "Customer Name: " << targetCustomerName << '\n';
    cout << "Book Title" + string(40, ' ') + "Number Of Days Borrowed" +  string(27, ' ') + "Days Overdue" + string(32, ' ') + "Late Fee" << endl;
    int SIZE_GAP = 50;
    string builderString;
    builderString += targetBookName + string(SIZE_GAP-(targetBookName.length()), ' ');
    builderString += std::to_string(totalLateDaysElapsed+7) + string( SIZE_GAP - std::to_string(totalLateDaysElapsed+7).length(), ' ');
    string overdueDays = totalLateDaysElapsed >= 0 ? std::to_string(totalLateDaysElapsed) : "0";
    builderString += totalLateDaysElapsed>= 0 ? std::to_string(totalLateDaysElapsed) : "0";
    builderString += string( (SIZE_GAP-std::to_string(SIZE_GAP - totalLateDaysElapsed+7).length())-5, ' ');
    builderString += "$"+std::to_string(owedFees);
    cout << builderString;
}

void DatabaseConnection::getBook(string bookName) {
    for (Book bk : bookList) {
        if (bk.title == bookName) {
            return;
        }
    }
    }

void DatabaseConnection::getCustomer(string customerName) {
    for (Customer cust : customerList) {
        if (cust.getName() == customerName) {
            return;
        }
    }
    return;
}

