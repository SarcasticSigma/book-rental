//
// Created by coldc on 5/2/2022.
//

#include "Book.h"
#include "DatabaseConnection.h"
#include <chrono>
#include <utility>
using namespace std::literals;

Book::Book(string title, string author, string publisher, int releaseYear, int releaseMonth, int releaseDay) {
    this->author = std::move(author);
    this->title = std::move(title);
    this->publisher = std::move(publisher);
    tm constructedReleaseDate = tm();
    constructedReleaseDate.tm_year = releaseYear;
    constructedReleaseDate.tm_mon = releaseMonth;
    constructedReleaseDate.tm_mday = releaseDay;
    this->releaseDate = constructedReleaseDate;
    this->isAvailable = true;
    this->dueDate = tm();
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
    //TODO Get proper offset
    int yearSince1900 = stoi(dataStrings[3])-1900;
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
    this->borrowedBy = dataStrings[7];

    this->dueDate = tm();
    dueDate.tm_year = stoi(dataStrings[8]);
    dueDate.tm_mon = stoi(dataStrings[9]);
    dueDate.tm_mday = stoi(dataStrings[10]);
}

string Book::getWritableString() const {
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
    } else  {
        stringBuilder += "0";
        stringBuilder += "_";
        stringBuilder += borrowedBy;
        stringBuilder += "_";
        stringBuilder += std::to_string(dueDate.tm_year+1900);
        stringBuilder += "_";
        stringBuilder += std::to_string(dueDate.tm_mon);
        stringBuilder += "_";
        stringBuilder += std::to_string(dueDate.tm_mday);
        stringBuilder += "\n";
        return stringBuilder;
    }
    stringBuilder += "_";
    stringBuilder += borrowedBy;
    stringBuilder += "_";
    stringBuilder += std::to_string(dueDate.tm_year);
    stringBuilder += "_";
    stringBuilder += std::to_string(dueDate.tm_mon);
    stringBuilder += "_";
    stringBuilder += std::to_string(dueDate.tm_mday);
    stringBuilder += "\n";
    return stringBuilder;
}

string Book::getOverviewData() const {
    int SIZE_GAP = 50;
    string builderString;
    DatabaseConnection db = DatabaseConnection();
    builderString += title + string(SIZE_GAP-(title.length()), ' ');
    builderString += this-> borrowedBy + string(SIZE_GAP-(borrowedBy.length()), ' ');
    builderString += isAvailable ? "Yes" : "No";
    builderString += "\n";
    return builderString;
}

string Book::getBorrowedBy() const {
    return this->borrowedBy;
}


