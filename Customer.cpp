#include "Customer.h"
#include "DatabaseConnection.h"
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
            std::to_string(this->registerDate.tm_year + 1900) + "_" + std::to_string(this->registerDate.tm_mon) + "_" +
            std::to_string(this->registerDate.tm_mday);
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

Customer::Customer(string writtenString) {
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
    int yearSince1900 = stoi(dataStrings[3]) - 1900;
    int month = stoi(dataStrings[4]);
    int day = stoi(dataStrings[5]);
    tm targetDate = tm();
    targetDate.tm_year = yearSince1900;
    targetDate.tm_mon = month;
    targetDate.tm_mday = day;

    this->name = dataStrings[0];
    this->address = dataStrings[1];
    this->phoneNumber = dataStrings[2];
    this->registerDate = targetDate;

}

string Customer::getOverviewData() {
    int SPACE_GAP = 50;
    string builderString;
    DatabaseConnection db = DatabaseConnection();


    vector<Book> borrowedList = db.getCustomersBorrowedBooks(this->name);
    if (!borrowedList.empty()) {
        for (const Book &borrowed : borrowedList) {
            string customerName = this->name;
            builderString +=  customerName + string(SPACE_GAP-(customerName.length()), ' ');
            string bookTitle = borrowed.title;
            builderString += bookTitle + string(SPACE_GAP-(bookTitle.length()), ' ');
            builderString +=  " " + std::to_string(borrowed.dueDate.tm_mon+1);
            builderString += '/';
            builderString += std::to_string(borrowed.dueDate.tm_mday);
            builderString += '/';
            builderString += std::to_string(borrowed.dueDate.tm_year);
            builderString += "\n";
        }
    } else {
        string customerName = this->name;
        builderString +=  customerName + string(SPACE_GAP-(customerName.length()), ' ');
        builderString += "-" + string(SPACE_GAP, ' ');
        builderString += "-\n";
    }


    return builderString;
}
