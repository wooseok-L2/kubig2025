cmake_minimum_required(VERSION 3.00)
project(part3)

# set(CMAKE_C_COMPILER "/usr/bin/gcc")

# set(CMAKE_C_STANDARD 99)
# set(CMAKE_C_STANDARD_REQUIRED ON)

# set(EXECUTABLES)

file(GLOB EXECUTABLES "${CMAKE_CURRENT_LIST_DIR}/*.c")

foreach(EXECUTABLE ${EXECUTABLES})
    get_filename_component(EXE_NAME ${EXECUTABLE} NAME_WE)
    add_executable(${EXE_NAME} ${EXECUTABLE})
endforeach()

add_subdirectory(carSerial)
add_subdirectory(date)
add_subdirectory(myRandom)
add_subdirectory(str)
