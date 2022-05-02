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
#include <ctime>

using std::cout;
using std::cin;
using std::vector;
using std::string;
using std::endl;
using std::ostream;
using std::istream;


int main() {


        time(&curtime);


        printf("Current time = %s", ctime(&curtime));

        return(0);

}
