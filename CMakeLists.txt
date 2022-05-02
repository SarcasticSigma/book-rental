cmake_minimum_required(VERSION 3.20)
project(BookReservationSystem_v0_0_1)

set(CMAKE_CXX_STANDARD 14)

add_executable(BookReservationSystem_v0_0_1 main.cpp Customer.cpp Customer.h DatabaseConnection.cpp DatabaseConnection.h cmake-build-debug/GUI.cpp cmake-build-debug/GUI.h Book.cpp Book.h)
