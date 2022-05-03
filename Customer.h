//
// Created by coldc on 5/1/2022.
//

#ifndef BOOKRESERVATIONSYSTEM_V0_0_1_CUSTOMER_H
#define BOOKRESERVATIONSYSTEM_V0_0_1_CUSTOMER_H

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include "Book.h"

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
    tm registerDate{};
public:
    /// Creates a customer object.
    /// \param name The name of the customer.
    /// \param address The address of the customer.
    /// \param phoneNumber The phone number of the customer.
    /// \param registerDate The date the customer was registered.
    Customer(string name, string address, string phoneNumber, tm registerDate);

    /// Deserializes a serialized version of a customer.
    /// \param writtenString The serialized string.
    explicit Customer(const string &writtenString);
    /// Changes the spaces in a string into the | character for data serialization.
    /// \param decryptedString The string with spaces in it.
    /// \return The string with |'s in it.
    static string encryptSpaces(const string &decryptedString);

    /// Changes the | characters in a string to spaces for data deserialization.
    /// \param encryptedString The string with |'s in it.
    /// \return The string with spaces in it.
    static string decryptSpaces(const string &encryptedString);

    /// Gets the name of the customer.
    /// \return The name of the customer.
    string getName();

    /// Serializes the customer into a string.
    /// \return A string represnting the customer to be written to the data file.
    std::string getWritableString();

    /// Gets a string representing some basic data about the customer for printing.
    /// \return A string with the the data, with spaces separating each data item for pretty printing.
    string getOverviewData();
};


#endif //BOOKRESERVATIONSYSTEM_V0_0_1_CUSTOMER_H
