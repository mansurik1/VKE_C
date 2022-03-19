project(HW1 C)
set(CMAKE_C_STANDARD 99)
cmake_minimum_required(VERSION 3.14)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wpedantic -Wextra -Werror")

option(BUILD_TESTS "Build test program")
if (BUILD_TESTS)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )
endif(BUILD_TESTS)

add_subdirectory(flight_lib)

add_executable(${PROJECT_NAME} main.c)

target_include_directories(${PROJECT_NAME} PUBLIC ${FLIGHT_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${FLIGHT_LIB_LIBRARIES})

add_subdirectory(tests)
