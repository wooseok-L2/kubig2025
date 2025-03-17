cmake_minimum_required(VERSION 3.10)
project(bowling)

set(SOURCES
    src/bowling.c
    src/board.c
    src/main.c
    src/bowlingsql.c

)

add_executable(bowling ${SOURCES})
target_include_directories(bowling PRIVATE include)

# library setting
target_include_directories(bowling PRIVATE /usr/include/mysql)
target_link_directories(bowling PRIVATE /usr/lib/mysql)
target_link_libraries(bowling PRIVATE mysqlclient)