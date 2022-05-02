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
#include "Date.h"

using std::cout;
using std::cin;
using std::vector;
using std::string;
using std::endl;
using std::ostream;
using std::istream;


class Book {
private:
    bool isAvailable;
    string title, author, publisher;
    Date releaseDate;
    int borrowedByCustomerId;
public:
    Book(string title, string author, string publisher, tm releaseDate, bool isAvailable = true);

};


#endif //BOOKRESERVATIONSYSTEM_V0_0_1_BOOK_H
