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


    int bookId;
    bool isAvailable;
    string title, author, publisher;
    tm releaseDate{};


public:
    Book(int bookId, string title, string author, string publisher, tm releaseDate, bool isAvailable=true);
int getBookId() const;
    bool Equals(const Book& book) const ;
};


#endif //BOOKRESERVATIONSYSTEM_V0_0_1_BOOK_H
