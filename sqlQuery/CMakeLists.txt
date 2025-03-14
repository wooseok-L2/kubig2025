cmake_minimum_required(VERSION 3.00)
project(bookSql)

set(SOURCES 
    src/main.c
    src/bookSql.c)

# /home/lws/kulws2025/sqlQuery/bookSql.c
add_executable(bookSql ${SOURCES})
target_include_directories(bookSql PRIVATE include)


# library
target_include_directories(bookSql PRIVATE /usr/include/mysql)
target_link_directories(bookSql PRIVATE /usr/lib/mysql)
target_link_libraries(bookSql PRIVATE mysqlclient)