//
// Created by coldc on 5/1/2022.
//

#ifndef BOOKRESERVATIONSYSTEM_V0_0_1_DATABASECONNECTION_H
#define BOOKRESERVATIONSYSTEM_V0_0_1_DATABASECONNECTION_H

#include <iostream>
#include <string>
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <ctime>

using std::string;
using std::ofstream;
using std::ifstream;



class DatabaseConnection {
private:
ofstream writeStream;
ifstream readStream;
string targetCustomerFile;
string targetBookFile;
string targetRentalRecordFile;


public:
    DatabaseConnection();
};


#endif //BOOKRESERVATIONSYSTEM_V0_0_1_DATABASECONNECTION_H
