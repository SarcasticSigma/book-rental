//
// Created by coldc on 5/1/2022.
//

#ifndef BOOKRESERVATIONSYSTEM_V0_0_1_CUSTOMER_H
#define BOOKRESERVATIONSYSTEM_V0_0_1_CUSTOMER_H

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <ctime>

using std::cout;
using std::cin;
using std::vector;
using std::string;
using std::endl;
using std::ostream;
using std::istream;

class Customer {
private:
    string name, address, phoneNumber;
    tm registerDate;
    vector<int> borrowedBookIds;
public:
    Customer(string name, string address, string phoneNumber, tm registerDate);\
    void setName(string
    name);
    void setAddress(string
    address);
    void setPhoneNumber(string phoneNumber);
    void setRegisterDate();

};


#endif //BOOKRESERVATIONSYSTEM_V0_0_1_CUSTOMER_H
