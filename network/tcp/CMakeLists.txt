cmake_minimum_required(VERSION 3.10)
project(network_tcp)

# 모든 .cpp 파일 자동 감지/home/aa/kuBig2025/stl/studnet.txt
file(GLOB EXECUTABLES "${CMAKE_CURRENT_LIST_DIR}/*.c")

foreach(EXECUTABLE ${EXECUTABLES})
    get_filename_component(EXE_NAME ${EXECUTABLE} NAME_WE)
    add_executable(${EXE_NAME} ${EXECUTABLE})
endforeach()

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
    file(GLOB EXECUTABLES "${SUBDIR}/main.c")
    foreach(EXECUTABLE ${EXECUTABLES})
        get_filename_component(EXECUTABLE_NAME ${SUBDIR} NAME_WE)
        get_filename_component(EXECUTABLE_DIR ${EXECUTABLE} DIRECTORY)
        file(GLOB_RECURSE SOURCES "${EXECUTABLE_DIR}/*.c")
        add_executable(${EXECUTABLE_NAME} ${SOURCES})
    endforeach()
endforeach()