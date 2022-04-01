project(flight_test)
set(CMAKE_CXX_STANDARD 11)
cmake_minimum_required(VERSION 3.14)

if (BUILD_TESTS)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fprofile-arcs -ftest-coverage -O0")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
endif()

file(GLOB SOURCES *.cc)

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${FLIGHT_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${FLIGHT_LIB_LIBRARIES} GTest::gtest_main)