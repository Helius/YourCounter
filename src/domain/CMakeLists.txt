cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -pedantic -Werror)

find_package(QT NAMES Qt6 COMPONENTS Core Quick LinguistTools Test REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick LinguistTools Test REQUIRED)

add_library(domain
	    entities/transaction.h
		entities/interval.h
		entities/Category.h

		usecases/startupusecase.h
		usecases/startupusecase.cpp
#		usecases/addnewtransactionusecase.h
#		usecases/addnewtransactionusecase.cpp

        repos/ICRUDRepo.h
		repos/ICRUDRepo.cpp
		repos/IEntityRepo.h
		repos/idatecolumnadapter.h
		repos/INetworkSettingsRepo.h
		entities/CategoryRequest.h
		entities/TransactionRequest.h
		entities/Group.h
		entities/GroupRequest.h)

target_include_directories(domain
	    INTERFACE
		    ${CMAKE_CURRENT_SOURCE_DIR}
			PRIVATE
			${CMAKE_CURRENT_SOURCE_DIR}
			)

target_link_libraries(
	    domain
		PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick
)
