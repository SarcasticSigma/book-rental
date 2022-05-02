/****************************************
* Student Name: Samuel Wiliams
* Date Due: May 3, 2022
* Date Submitted: May 3, 2022
* Program Name: BookReservationSystem
* Program Description: A book reservation system with a command line GUI.
****************************************/
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <ctime>
#include <chrono>
#include <conio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdio>
#include <cstdlib>
#include "DatabaseConnection.h"
#include <sstream>
#include <sys/stat.h>
// for windows mkdir
#ifdef _WIN32

#include <direct.h>

#endif

#include <sys/stat.h>
#include <sys/stat.h>
#include <string>
#include <fstream>
#include <ctime>
#include "DatabaseConnection.h"

int getTargetFunction();

using std::cout;
using std::cin;
using std::vector;
using std::string;
using std::endl;
using std::ostream;
using std::istream;
using system_clock = std::chrono::system_clock;

tm getCurrentTime() {
    system_clock::time_point now = system_clock::now();
    time_t tt = system_clock::to_time_t(now);
    tm local_tm = *localtime(&tt);
    return local_tm;
}

int main() {










    //    int target = getTargetFunction();
DatabaseConnection db = DatabaseConnection();
db.WriteCustomer(Customer("Robert California", "170 Burrell Road", "1678822999", getCurrentTime()));





/*
    switch (target) {

        case 1:
            string fName, lName, address, phoneNumber;

            cout
                    << "Please enter the follow information: "
                       "First name, "
                       "last name, "
                       "address, "
                       "and phone number pressing enter after each entry.";

            DatabaseConnection db = DatabaseConnection();
            db.WriteCustomer(Customer((fName + " " + lName), address, phoneNumber, getCurrentTime()));

            break;
        case 2:
            db.DeleteCustomer
            break;
        case 3:
            //Add book
            break;
        case 4:
            //Delete book
            break;
        case 5:
            //Rent a book out
            break;
        case 6:
            //Return a book.
            break;
        case 7:
            //List all customers
            break;
        case 8:
            //List all books
            break;
        default:
            throw std::invalid_argument("A function must be chosen!");
    }
*/
}

int getTargetFunction() {
    int userInput;
    cout
            << "What would you like to do? \n1. Add customer\nDelete Customer\n3. Add book\n4.Delete Book\n5. Rent a book out\n6. Return a book\n7. List all customers\n8. List all books";

    while (true) {
        cin >> userInput;
        if (userInput > 0 && userInput <= 8) {
            break;
        } else {
            cout
                    << "Please select an option from the following: \n1. Add customer\nDelete Customer\n3. Add book\n4.Delete Book\n5. Rent a book out\n6. Return a book\n7. List all customers\n8. List all books";
        }
    }
    return userInput;
}
