#include "Customer.h"
#include <utility>

Customer::Customer(string name, string address, string phoneNumber, tm registerDate = tm()) {
    this->name = std::move(name);
    this->address = std::move(address);
    this->phoneNumber = std::move(phoneNumber);
    this->registerDate = registerDate;
}

Customer::Customer(string name, string address, string phoneNumber, tm registerDate = tm(),
                   vector<int> bookIds = vector<int>()) {
    this->name = std::move(name);
    this->address = std::move(address);
    this->phoneNumber = std::move(phoneNumber);
    this->registerDate = registerDate;
    this->borrowedBookIds = std::move(bookIds);
}

bool Customer::_canBorrowMoreBooks() {
    return this->borrowedBookIds.size() < 7;
}

tm Customer::getRegisterDate() {
    return registerDate;
}

string Customer::getPhoneNumber() {
    return this->phoneNumber;
}

string Customer::getAddress() {
    return this->address;
}

string Customer::getName() {
    return this->name;
}

void Customer::setRegisterDate(tm newRegisterDate) {
    this->registerDate = newRegisterDate;
}

void Customer::setPhoneNumber(string newPhoneNumber) {
    this->phoneNumber = std::move(newPhoneNumber);

}

void Customer::_addBookIdToRental(int bookId) {
    borrowedBookIds.push_back(bookId);
}

void Customer::_deleteBookIdFromRental(int bookId) {
    int targetDeletion;
    for (int i = 0; i <= borrowedBookIds.size(); i++) {
        if (borrowedBookIds[i] == bookId) {
            targetDeletion = i;
        }
    }
    borrowedBookIds.erase(borrowedBookIds.begin() + targetDeletion);
}

std::string Customer::getWritableString() {
    string stringBuilder;
    stringBuilder += encryptSpaces(this->name);
    stringBuilder += "_";
    stringBuilder += encryptSpaces(this->address);
    stringBuilder += "_";
    stringBuilder += encryptSpaces(this->phoneNumber);
    stringBuilder += "_";
    stringBuilder +=
            std::to_string(1900 + this->registerDate.tm_year) + "_" + std::to_string(this->registerDate.tm_mon) + "_" +
            std::to_string(this->registerDate.tm_mday);
    stringBuilder += "_";
    stringBuilder += "[";
    for (int i = 0; i < borrowedBookIds.size(); i++) {
        stringBuilder += std::to_string(i);
        if (i != borrowedBookIds.size() - 1) {
            stringBuilder += ",";
        }
    }
    stringBuilder += "]";
    stringBuilder += "\n";


    return stringBuilder;
}

string Customer::encryptSpaces(const string &decryptedString) {
    string encryptedString;
    for (char c : decryptedString) {
        if (c != ' ') {
            encryptedString += c;
        } else {
            encryptedString += '|';
        }
    }
    return encryptedString;

}

string Customer::decryptSpaces(const string &encryptedString) {
    string decryptedString;
    for (char c : encryptedString) {
        if (c != '|') {
            decryptedString += c;
        } else {
            decryptedString += ' ';
        }
    }
    return decryptedString;

}

Customer::Customer(const string &writtenString) {
    string customerLine = Customer::decryptSpaces(writtenString);
    vector<string> dataStrings = vector<string>();
    string dataString;
    for (char i : customerLine) {
        if (i == '_') {
            dataStrings.push_back(dataString);
            dataString = "";
        } else {
            dataString += i;
        }
    }
    dataStrings.push_back(dataString);
    int yearSince1900 = stoi(dataStrings[3]);
    int month = stoi(dataStrings[4]);
    int day = stoi(dataStrings[5]);
    tm targetDate = tm();
    targetDate.tm_year = yearSince1900;
    targetDate.tm_mon = month;
    targetDate.tm_mday = day;

    vector<int> bookIdVector = vector<int>();
    string bookIdString;
    for (char i : dataStrings[6]) {
        if(dataStrings[6] == "[]"){
            break;
        }
        if (i == ',') {
            bookIdVector.push_back(stoi(bookIdString));
        } else if(i=='[' || i == ']'){
            bookIdString += i;
        }
    }


    this->name = dataStrings[0];
    this->address = dataStrings[1];
    this->phoneNumber = dataStrings[2];
    this->registerDate = targetDate;
    this->borrowedBookIds = bookIdVector;

}

