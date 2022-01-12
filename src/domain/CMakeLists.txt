cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -pedantic -Werror)

find_package(QT NAMES Qt6 COMPONENTS Core Quick LinguistTools Test REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick LinguistTools Test REQUIRED)

add_library(domain
	    entities/Transaction.h
		entities/Category.h
		entities/Group.h
		entities/Prediction.h
		entities/interval.h

		usecases/StartUpUsecase.h
		usecases/StartUpUsecase.cpp
		usecases/AddNewTransactionUsecase.h
		usecases/AddNewTransactionUsecase.cpp
		usecases/AddNewGroupUsecase.h
		usecases/AddNewGroupUsecase.cpp
		usecases/AddNewCategoryUsecase.h
		usecases/AddNewCategoryUsecase.cpp
		usecases/CurrentBalanceCalculateUsecase.h
		usecases/CurrentBalanceCalculateUsecase.cpp
		usecases/MonthReportUsecase.h
		usecases/MonthReportUsecase.cpp
		usecases/EditTransactionUsecase.h
		usecases/EditTransactionUsecase.cpp

		repos/ICRUDRepo.h
		repos/ICRUDRepo.cpp
		repos/IEntityRepo.h
		repos/idatecolumnadapter.h
		repos/INetworkSettingsRepo.h
		repos/IPredictionRepo.h
		)

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
