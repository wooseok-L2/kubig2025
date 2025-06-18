cmake_minimum_required(VERSION 3.0)
project(OpenCV_part7)

find_package(OpenCV REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(ZMQ REQUIRED libzmq)

add_executable(59_mnist_cnn 59_mnist_cnn.cpp)
target_link_libraries(59_mnist_cnn PRIVATE zmq ${OpenCV_LIBS})
# target_link_libraries(59_mnist_cnn ${OpenCV_LIBS})

add_executable(60_google_vision 60_google_vision.cpp)
target_link_libraries(60_google_vision ${OpenCV_LIBS})

add_executable(61_google_cam 61_google_cam.cpp)
target_link_libraries(61_google_cam ${OpenCV_LIBS})

add_executable(62_dnnface 62_dnnface.cpp)
target_link_libraries(62_dnnface ${OpenCV_LIBS})