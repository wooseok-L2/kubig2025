cmake_minimum_required(VERSION 3.00)
project(date)


#include_directories((${CMAKE_CURRENT_LIST_DIR}/include)) //when you need some files
set(SOURCES 
    main.c
    date.c)

add_executable(carSerial main.c date.c)