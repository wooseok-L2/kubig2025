cmake_minimum_required(VERSION 3.0)
project(01_hello)


find_package(OpenCV REQUIRED)

add_executable(hello 01_helloWorld.cpp)
target_link_libraries(hello ${OpenCV_LIBS})

add_executable(basic_op 02_basicOp.cpp)
target_link_libraries(basic_op ${OpenCV_LIBS})

