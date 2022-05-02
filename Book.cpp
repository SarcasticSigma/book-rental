//
// Created by coldc on 5/2/2022.
//

#include "Book.h"
#include "DatabaseConnection.h"
#include <chrono>
#include <utility>
using namespace std::literals;

Book::Book(string title, string author, string publisher, int releaseYear, int releaseMonth, int releaseDay,
           bool isAvailable) {
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


Book::Book(const string &writtenString) {
    string outputString = Customer::decryptSpaces(writtenString);
    vector<string> dataStrings = vector<string>();
    string dataString;
    for (char c : outputString) {
        if (c == '_') {
            dataStrings.push_back(dataString);
            dataString = "";
        } else {
            dataString += c;
        }
    }
    dataStrings.push_back(dataString);
    this->title = dataStrings[0];
    this->author = dataStrings[1];
    this->publisher = dataStrings[2];
    int yearSince1900 = stoi(dataStrings[3]);
    int month = stoi(dataStrings[4]);
    int day = stoi(dataStrings[5]);
    tm targetDate = tm();
    targetDate.tm_year = yearSince1900;
    targetDate.tm_mon = month;
    targetDate.tm_mday = day;
    this->releaseDate = targetDate;
    if (stoi(dataStrings[6]) == 1) {
        this->isAvailable = true;
    } else {
        this->isAvailable = false;
    }
    this->dueDate = tm();
    dueDate.tm_year = stoi(dataStrings[7]);
    dueDate.tm_mon = stoi(dataStrings[8]);
    dueDate.tm_mday = stoi(dataStrings[9]);
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
        stringBuilder += "_";
        stringBuilder += dueDate.tm_year;
        stringBuilder += "_";
        stringBuilder += dueDate.tm_mon;
        stringBuilder += "_";
        stringBuilder += dueDate.tm_mday;

    }
    stringBuilder += "_";
    stringBuilder += "0";
    stringBuilder += "\n";
    return stringBuilder;
}

string Book::getOverviewData() {
    string builderString;
    DatabaseConnection db = DatabaseConnection();
    builderString += title;

    DatabaseConnection myDBCon = DatabaseConnection();
    vector<Book> books;
    for (Customer customer : myDBCon.customerList) {
        books = db.getCustomersBorrowedBooks(customer.getName());
    }
    for(Book book : books){

    }
    builderString += " Available? ";
    builderString += isAvailable ? "Yes" : "No";
    builderString += "\n";
    return builderString;
}

void Book::borrowBook(string customerName) {
    std::chrono::system_clock::time_point tp = std::chrono::system_clock::now();
    std::chrono::system_clock::time_point newTimePoint = tp + (7*24h);
    time_t tt = std::chrono::system_clock::to_time_t(newTimePoint);
    tm local_tm = *localtime(&tt);
    this->dueDate=local_tm;
    this->isAvailable = false;
    this->borrowedBy = std::move(customerName);

}

string Book::getBorrowedBy() {
    return this->borrowedBy;
}

double Book::returnBook(string customerName) {
    //TODO: return the cost of returning the book.
    return 0;
}


