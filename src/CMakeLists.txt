cmake_minimum_required(VERSION 3.14)
project(src)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -pedantic -Werror)

add_library(src
    di.hpp
        qmlapp/main.cpp
        qmlapp/Theme.cpp
        qmlapp/Theme.h

    qmlinjector/qmlinjector.h
    qmlinjector/qmlinjector.cpp
    qmlinjector/qmlinjectorbuilder.h
    qmlinjector/iqmlobjectcreator.h
    qmlinjector/iqmlobjectcreator.cpp

    domain/entities/transaction.h
    domain/entities/interval.h
    domain/entities/transaction.cpp



    domain/usecases/startupusecase.h
    domain/usecases/startupusecase.cpp
    domain/usecases/addnewtransactionusecase.h
    domain/usecases/addnewtransactionusecase.cpp

    domain/repos/itransactionrepo.h
    domain/repos/itransactionrepo.cpp
    domain/repos/isettingsrepository.h
    domain/repos/isettingsrepository.cpp

        qmlapp/repos/idatecolumnadapter.h
        qmlapp/repos/itransactionprovider.h
        qmlapp/repos/itransactionprovider.cpp

        qmlapp/repos/transactionrepo.h
        qmlapp/repos/transactionrepo.cpp
        qmlapp/repos/datecolumnadapter.h
        qmlapp/repos/datecolumnadapter.cpp
        qmlapp/repos/transactionproviderfromfile.h
        qmlapp/repos/transactionproviderfromfile.cpp
        qmlapp/repos/transactionjsonmapper.h
        qmlapp/repos/transactionjsonmapper.cpp
        qmlapp/repos/settingsrepositoryimpl.h
        qmlapp/repos/settingsrepositoryimpl.cpp

        qmlapp/presenters/timescalebuttonpresenter.h
        qmlapp/presenters/timescalebuttonpresenter.cpp
        qmlapp/presenters/timelinetablemodel.cpp
        qmlapp/presenters/timelinetablemodel.h
        qmlapp/presenters/addtransactionbuttonpresenter.h
        qmlapp/presenters/addtransactionbuttonpresenter.cpp
        qmlapp/presenters/transactionlistmodel.h
        qmlapp/presenters/transactionlistmodel.cpp

    )

target_include_directories(src
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
    )

target_link_libraries(
    src
    PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick
    )
