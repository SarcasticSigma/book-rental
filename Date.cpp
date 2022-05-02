//
// Created by coldc on 5/2/2022.
//

#include "Date.h"

std::string Date::getStringDate() {
    std::string buildString;
    buildString += this->month;
    buildString += " ";
    buildString += this->day;
    buildString += " ";
    buildString += this->year;
    return buildString;
}

Date::Date(int year, int month, int day) {
    this->year = year;
    this->month = month;
    this->day = day;
}
