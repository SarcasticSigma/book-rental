//
// Created by coldc on 5/2/2022.
//

#ifndef BOOKRESERVATIONSYSTEM_V0_0_1_BOOK_H
#define BOOKRESERVATIONSYSTEM_V0_0_1_BOOK_H

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


class Book {
public:
    bool isAvailable;
    string borrowedBy = "None";
    string title, author, publisher;
    tm releaseDate{};
    tm dueDate;

    /// Constructor for a book.
    /// \param title The title of the book
    /// \param author The author of the book.
    /// \param publisher The publisher of the book.
    /// \param releaseYear The year the book was released.
    /// \param releaseMonth The month the book was released.
    /// \param releaseDay The day the book was released.
    Book(string title, string author, string publisher, int releaseYear, int releaseMonth, int releaseDay);

    /// Deserializes a serialized version of a book.
    /// \param writtenString The serialized string.
    explicit Book(const string &writtenString);

    /// Gets the borrowedBy field.
    /// \return The name of the customer borrowing the book.
    string getBorrowedBy() const;

    /// Constructs a string representing the book for serialization.
    /// \return A string representing the Book.
    string getWritableString() const;

    /// Gets a string representing some basic data about the Book for printing.
    /// \return A string with the the data, with spaces separating each data item for pretty printing.
    string getOverviewData() const;
};


#endif //BOOKRESERVATIONSYSTEM_V0_0_1_BOOK_H
