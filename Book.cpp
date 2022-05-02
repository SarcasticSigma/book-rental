//
// Created by coldc on 5/2/2022.
//

#include "Book.h"
#include "DatabaseConnection.h"

#include <utility>

Book::Book(string title, string author, string publisher, int releaseYear, int releaseMonth, int releaseDay,
           bool isAvailable) {



    DatabaseConnection db = DatabaseConnection();
//TODO: Get book ids
    this->bookId = bookId;

    this->author = std::move(author);
    this->title = std::move(title);
    this->publisher = std::move(publisher);
    tm constructedReleaseDate = tm();
    constructedReleaseDate.tm_year = releaseYear;
    constructedReleaseDate.tm_mon = releaseMonth;
    constructedReleaseDate.tm_mday = releaseDay;
    this->releaseDate = constructedReleaseDate;
    this->isAvailable = isAvailable;
}


int Book::getBookId() const {
    return this->bookId;
}

Book::Book(const string &writtenString) {
    vector<string> dataStrings = vector<string>();
    string dataString;
    for (char c : writtenString) {
        if (c != '_') {
            dataStrings.push_back(dataString);
            dataString = "";
        } else {
            dataString += c;
        }
    }
    dataStrings.push_back(dataString);
    this->bookId = stoi(dataStrings[0]);
    this->title = dataStrings[1];
    this->author = dataStrings[2];
    this->publisher = dataStrings[3];
    int yearSince1900 = stoi(dataStrings[4]);
    int month = stoi(dataStrings[5]);
    int day = stoi(dataStrings[6]);
    tm targetDate = tm();
    targetDate.tm_year = yearSince1900;
    targetDate.tm_mon = month;
    targetDate.tm_mday = day;
    this->releaseDate = targetDate;
    if (stoi(dataStrings[7]) == 1) {
        this->isAvailable = true;
    } else {
        this->isAvailable = false;
    }

}

string Book::getWritableString() {
    string stringBuilder;
    stringBuilder += Customer::encryptSpaces(this->title);
    stringBuilder += "_";
    stringBuilder += Customer::encryptSpaces(this->author);
    stringBuilder += "_";
    stringBuilder += Customer::encryptSpaces(this->publisher);
    stringBuilder += "_";
    stringBuilder +=
            std::to_string(1900 + this->releaseDate.tm_year) + "_" +
            std::to_string(this->releaseDate.tm_mon) + "_" +
            std::to_string(this->releaseDate.tm_mday);
    stringBuilder += "_";
    if (isAvailable) {
        stringBuilder += "1";
    } else {
        stringBuilder += "0";
        stringBuilder += "_";
        stringBuilder += borrowedBy;
    }
    stringBuilder += "_";
    stringBuilder += "0";
    stringBuilder += "\n";
    return stringBuilder;
}

int Book::_getNextId() {
    DatabaseConnection db = DatabaseConnection();
    return db.bookList.size() + 1;

}

string Book::getOverviewData() {
    string builderString;
    DatabaseConnection db = DatabaseConnection();
    builderString += title;
    DatabaseConnection myDBCon = DatabaseConnection();
    bool isBorrowed = false;
    vector<string> books;
    for (Customer customer : myDBCon.customerList) {
        books = db.getCustomersBorrowedBooks(customer.getName());
    }
    for(string str : books){

    }
    builderString += isAvailable ? "Yes" : "No";
    builderString += "\n";
    return builderString;
}

void Book::borrowBook(string customerName) {
    this->isAvailable = false;
    this->borrowedBy = std::move(customerName);

}

string Book::getBorrowedBy() {
    return this->borrowedBy;
}
