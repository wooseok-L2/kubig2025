cmake_minimum_required(VERSION 3.00)
project(bowling)

set(SOURCES 
    src/main.c
    src/bowling.c)

# /home/lws/kulws2025/sqlQuery/bookSql.c
add_executable(bowling ${SOURCES})
target_include_directories(bowling PRIVATE include)


# library
target_include_directories(bowling PRIVATE /usr/include/mysql)
target_link_directories(bowling PRIVATE /usr/lib/mysql)
target_link_libraries(bowling PRIVATE mysqlclient)