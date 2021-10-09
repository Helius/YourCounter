cmake_minimum_required(VERSION 3.14)
project(storage)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -pedantic -Werror)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick LinguistTools Test REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick LinguistTools Test REQUIRED)

add_library(storage)

target_sources(
        storage
        PRIVATE
        transactionjsonmapper.cpp
        transactionjsonmapper.h
        transactionrepo.cpp
        transactionrepo.h
        firebaseRtDbAPI.cpp
        firebaseRtDbAPI.h
        IFirebaseRtDbApi.h
)

target_include_directories(storage
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(
        storage
        PRIVATE domain
        PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick
)


enable_testing(true)

add_executable(test_storage test/test_transactionrepo.cpp)
add_test(NAME test_storage COMMAND test_storage)
target_link_libraries(test_storage storage domain Qt::Test)

add_executable(test_mapper test/test_transactionjsonmapper.cpp)
add_test(NAME test_mapper COMMAND test_mapper)
target_link_libraries(test_mapper storage domain Qt::Test)

