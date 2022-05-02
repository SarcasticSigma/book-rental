//
// Created by coldc on 5/1/2022.
//

#include "Customer.h"

#include <utility>


Customer::Customer(string name, string address, string phoneNumber, tm registerDate=tm()) {
this->name = std::move(name);
this->address = std::move(address);
this-> phoneNumber = std::move(phoneNumber);
this->registerDate = registerDate;


}

bool Customer::_canBorrowMoreBooks() {
    return this->borrowedBooks.size()<7;
}

