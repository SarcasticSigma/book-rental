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

using std::cout;
using std::cin;
using std::vector;
using std::string;
using std::endl;
using std::ostream;
using std::istream;
using system_clock = std::chrono::system_clock;

tm getCurrentTime(){
    system_clock::time_point now = system_clock::now();
    time_t tt = system_clock::to_time_t(now);
    tm local_tm = *localtime(&tt);
    return local_tm;
}

int main() {
    DatabaseConnection myDB = DatabaseConnection();


    myDB.WriteCustomer(Customer("Robert", "Buttril", "1770666999", getCurrentTime()));
    return (0);

}
