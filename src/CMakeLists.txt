cmake_minimum_required(VERSION 3.14)
project(src)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -pedantic -Werror)

add_library(src
        main.cpp
        Theme.cpp
        Theme.h
        timelinetablemodel.cpp
        timelinetablemodel.h
        entities/transaction.cpp
        repos/transactionrepo.cpp
        repos/itransactionrepo.cpp
        repos/idatecolumnadapter.h
        repos/datecolumnadapter.h
        repos/datecolumnadapter.cpp
        repos/itransactionprovider.h
        repos/itransactionprovider.cpp
        repos/transactionproviderfromfile.h
        repos/transactionproviderfromfile.cpp
        repos/transactionjsonmapper.h
        repos/transactionjsonmapper.cpp
        )

target_include_directories(src
          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
          )

target_link_libraries(
        src
        PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick
        )
