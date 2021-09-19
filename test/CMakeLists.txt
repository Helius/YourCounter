cmake_minimum_required(VERSION 3.5)

project(test_unit LANGUAGES CXX)


find_package(Qt6Test REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
enable_testing()

add_subdirectory(.. src)
add_executable(test_unit test_datecolumnadapter.cpp)
add_test(NAME test_unit COMMAND test_unit)

target_link_libraries(test_unit PRIVATE Qt6::Test src)

