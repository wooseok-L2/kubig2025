cmake_minimum_required(VERSION 3.00)
project(carSerial)


#include_directories((${CMAKE_CURRENT_LIST_DIR}/include)) //when you need some files
set(SOURCES 
    main.c
    serial.c)

add_executable(carSerial main.c serial.c)