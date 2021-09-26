cmake_minimum_required(VERSION 3.14)
project(src)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -pedantic -Werror)

add_library(src
    di.hpp
    app/main.cpp
    app/Theme.cpp
    app/Theme.h

    qmlinjector/qmlinjector.h
    qmlinjector/qmlinjector.cpp
    qmlinjector/qmlinjectorbuilder.h
    qmlinjector/iqmlobjectcreator.h
    qmlinjector/iqmlobjectcreator.cpp

    domain/entities/transaction.h
    domain/entities/transaction.cpp

    domain/usecases/startupusecase.h
    domain/usecases/startupusecase.cpp
    domain/usecases/addnewtransactionusecase.h
    domain/usecases/addnewtransactionusecase.cpp

    domain/repos/itransactionrepo.h
    domain/repos/itransactionrepo.cpp
    domain/repos/isettingsrepository.h
    domain/repos/isettingsrepository.cpp

    app/repos/idatecolumnadapter.h
    app/repos/itransactionprovider.h
    app/repos/itransactionprovider.cpp

    app/repos/transactionrepo.h
    app/repos/transactionrepo.cpp
    app/repos/datecolumnadapter.h
    app/repos/datecolumnadapter.cpp
    app/repos/transactionproviderfromfile.h
    app/repos/transactionproviderfromfile.cpp
    app/repos/transactionjsonmapper.h
    app/repos/transactionjsonmapper.cpp
    app/repos/settingsrepositoryimpl.h
    app/repos/settingsrepositoryimpl.cpp

    app/presenters/timescalebuttonpresenter.h
    app/presenters/timescalebuttonpresenter.cpp
    app/presenters/timelinetablemodel.cpp
    app/presenters/timelinetablemodel.h
    app/presenters/addtransactionbuttonpresenter.h
    app/presenters/addtransactionbuttonpresenter.cpp
    app/presenters/transactionlistmodel.h
    app/presenters/transactionlistmodel.cpp

    )

target_include_directories(src
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
    )

target_link_libraries(
    src
    PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick
    )
