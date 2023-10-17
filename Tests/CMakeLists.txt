cmake_minimum_required(VERSION 3.5)

project(DBMS LANGUAGES CXX)

enable_testing()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Test)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Test)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(DBMS tst_dbms.cpp
    ../column.h ../column.cpp

    ../column_int.h ../column_int.cpp
    ../column_real.h ../column_real.cpp
    ../cartesian_product.h)
add_test(NAME DBMS COMMAND DBMS)

target_link_libraries(DBMS PRIVATE Qt${QT_VERSION_MAJOR}::Test)
target_link_libraries(DBMS PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

