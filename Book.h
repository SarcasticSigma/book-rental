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
private:


    int bookId = 0;
    bool isAvailable;
    string title, author, publisher;
    tm releaseDate{};

    static int _getNextId();

public:
    Book(string title, string author, string publisher, int releaseYear, int releaseMonth, int releaseDay,
         bool isAvailable = true);

    Book(const string &writtenString);

    int getBookId() const;

    bool Equals(const Book &book) const;

    string getWritableString();

    string getOverviewData();
};


#endif //BOOKRESERVATIONSYSTEM_V0_0_1_BOOK_H
