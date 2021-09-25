cmake_minimum_required(VERSION 3.14)

project(YourCounter LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick LinguistTools Test REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick LinguistTools Test REQUIRED)

set(TS_FILES src/app/YourCounter_prg_001.ts)

add_compile_options(-Wall -Wextra -pedantic -Werror)

add_subdirectory(src)

add_executable(YourCounter
        qml.qrc
        ${TS_FILES}
        )

add_executable(tests
        test/test_main.cpp
        test/AutoTest.h
        test/test_datecolumnadapter.cpp
        test/test_transactionrepo.cpp
        )

target_link_libraries(tests src Qt::Test)

target_compile_definitions(YourCounter
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(YourCounter
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick src)
