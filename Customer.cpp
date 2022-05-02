//
// Created by coldc on 5/1/2022.
//

#include "Customer.h"

#include <utility>


Customer::Customer(string name, string address, string phoneNumber, tm registerDate = tm()) {
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

void Customer::_addBookToRental(const Book &book) {
}

void Customer::_deleteBookFromRental(const Book &book) {

}

std::string Customer::getWritableString() {
    string stringBuilder;
    stringBuilder += this->name;
    stringBuilder += "_";
    stringBuilder += this->address;
    stringBuilder += "_";
    stringBuilder += this->phoneNumber;
    stringBuilder += "_";
    stringBuilder +=
            std::to_string(1900 + this->registerDate.tm_year) + "-" + std::to_string(this->registerDate.tm_mon) + "-" +
            std::to_string(this->registerDate.tm_mday);
    stringBuilder += "_";
    stringBuilder += this->phoneNumber;
    stringBuilder += "_";
    stringBuilder += "[";
    for (int i = 0; i < borrowedBookIds.size(); i++) {
        stringBuilder += std::to_string(i);
        if (i != borrowedBookIds.size()-1) {
            stringBuilder += ",";
        }
    }
    stringBuilder += "]";
    stringBuilder += "\n";


    return stringBuilder;
}

