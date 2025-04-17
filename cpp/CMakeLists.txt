cmake_minimum_required(VERSION 3.10)
project(kuBig2025_CPP CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)

# 모든 폴더 자동 감지
file(GLOB SUBDIRS RELATIVE "${CMAKE_CURRENT_LIST_DIR}" "${CMAKE_CURRENT_LIST_DIR}/*")
set(SUBDIRS_FILTERED "")
foreach(SUBDIR ${SUBDIRS})
    if(IS_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/${SUBDIR}")
        list(APPEND SUBDIRS_FILTERED "${CMAKE_CURRENT_LIST_DIR}/${SUBDIR}")
    endif()
endforeach()
set(SUBDIRS ${SUBDIRS_FILTERED})

# 각 서브디렉토리의 main.cpp 파일을 찾아서 실행 파일 생성

foreach(SUBDIR ${SUBDIRS})
    file(GLOB EXECUTABLES "${SUBDIR}/main.cpp")
    foreach(EXECUTABLE ${EXECUTABLES})
        get_filename_component(EXECUTABLE_NAME ${SUBDIR} NAME_WE)
        get_filename_component(EXECUTABLE_DIR ${EXECUTABLE} DIRECTORY)
        file(GLOB_RECURSE SOURCES "${EXECUTABLE_DIR}/*.cpp")
        add_executable(${EXECUTABLE_NAME} ${SOURCES})
    endforeach()
endforeach()

# 컴파일 플래그 설정
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
endif()