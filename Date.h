//
// Created by coldc on 5/2/2022.
//

#ifndef BOOKRESERVATIONSYSTEM_V0_0_1_DATE_H
#define BOOKRESERVATIONSYSTEM_V0_0_1_DATE_H


class Date {
private:
    int year, month, day;
public:
    Date(int year, int month, int day);

    std::string getStringDate();
};


#endif //BOOKRESERVATIONSYSTEM_V0_0_1_DATE_H
