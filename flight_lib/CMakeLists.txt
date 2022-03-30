project(flight_library)
set(CMAKE_C_STANDARD 99)
cmake_minimum_required(VERSION 3.14)

if (BUILD_TESTS)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage -fPIC -O0")
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2")
endif()

file(GLOB SOURCES *.c)
file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

add_library(${PROJECT_NAME} ${SOURCES})

set(FLIGHT_LIB_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
set(FLIGHT_LIB_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)