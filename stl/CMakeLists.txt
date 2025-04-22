cmake_minimum_required(VERSION 3.00)
project(KuBig2025_STL)

# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED True)
# set(CMAKE_BUILD_TYPE Debug)

# set(CMAKE_C_COMPILER "/usr/bin/gcc")

# set(CMAKE_C_STANDARD 99)
# set(CMAKE_C_STANDARD_REQUIRED ON)

# set(EXECUTABLES)

file(GLOB EXECUTABLES "${CMAKE_CURRENT_LIST_DIR}/*.cpp")

foreach(EXECUTABLE ${EXECUTABLES})
    get_filename_component(EXE_NAME ${EXECUTABLE} NAME_WE)
    add_executable(${EXE_NAME} ${EXECUTABLE})
endforeach()

#add_executable(ex1_vector ex1_vector.cpp)
