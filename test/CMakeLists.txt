cmake_minimum_required(VERSION 3.5)

project(test_unit LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 CPOMPONENTS Core Test REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Test REQUIRED)

add_compile_options(-Wall -Wextra -pedantic -Werror)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

enable_testing()

add_subdirectory(.. src)
add_executable(test_unit test_datecolumnadapter.cpp)
add_test(NAME test_unit COMMAND test_unit)

target_link_libraries(test_unit PRIVATE Test src)

