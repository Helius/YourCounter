cmake_minimum_required(VERSION 3.14)

project(YourCounter LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -pedantic -Werror)

enable_testing()

add_subdirectory(src/domain)
add_subdirectory(src/storage)
add_subdirectory(src/settings)
add_subdirectory(src/qmlapp)
