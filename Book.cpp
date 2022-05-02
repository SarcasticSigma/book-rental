//
// Created by coldc on 5/2/2022.
//

#include "Book.h"

#include <utility>

Book::Book(int bookId, string title, string author, string publisher, tm releaseDate, bool isAvailable) {
    this->bookId = bookId;
    this->author = std::move(author);
    this->title = std::move(title);
    this->publisher = std::move(publisher);
    this->releaseDate = releaseDate;
    this->isAvailable = isAvailable;
}


int Book::getBookId() const {
    return this->bookId;
}

bool Book::Equals(const Book &book) const {
    return this->bookId == book.getBookId();
}
