cmake_minimum_required(VERSION 3.00)
project(myRandom)


#include_directories((${CMAKE_CURRENT_LIST_DIR}/include)) //when you need some files
set(SOURCES 
    main.c
    myRandom.c)

add_executable(myRandom main.c myRandom.c)