cmake_minimum_required(VERSION 3.00)
project(bbowling)

set(SOURCES 
    src/main.c
    src/bbowling.c)

# /home/lws/kulws2025/sqlQuery/bookSql.c
add_executable(bbowling ${SOURCES})
target_include_directories(bbowling PRIVATE include)


# library
target_include_directories(bbowling PRIVATE /usr/include/mysql)
target_link_directories(bbowling PRIVATE /usr/lib/mysql)
target_link_libraries(bbowling PRIVATE mysqlclient)