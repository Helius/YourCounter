cmake_minimum_required(VERSION 3.14)
project(storage)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -pedantic -Werror)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick LinguistTools Test REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick LinguistTools Test REQUIRED)

add_library(storage jsonMappers/IJsonMapper.h)

target_sources(
	    storage
		PRIVATE
		CrudRepoImpl.h
		firebaseRtDbAPI.cpp
		firebaseRtDbAPI.h
		IFirebaseRtDbApi.h
		EntityRepoImpl.h
		EntityRepoImpl.cpp
#		PredictionRepoimpl.h
#		PredictionRepoimpl.cpp
        LocalFileDbApi.h # for test purpose mostly
		LocalFileDbApi.cpp
		jsonMappers/TransactionMapper.cpp
		jsonMappers/TransactionMapper.h
		jsonMappers/CategoryMapper.cpp
		jsonMappers/CategoryMapper.h
		jsonMappers/GroupMappers.cpp
		jsonMappers/GroupMappers.h
		jsonMappers/PredictionMapper.h
		jsonMappers/PredictionMapper.cpp
		jsonMappers/WalletMapper.h
		jsonMappers/WalletMapper.cpp
		AuthServiceImpl.h
		AuthServiceImpl.cpp
)

target_include_directories(storage
	    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
		)

target_link_libraries(
	    storage
		PRIVATE domain
		PRIVATE settings
		PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick
)


enable_testing(true)

add_executable(test_storage test/test_CrudRepo.cpp)
add_test(NAME test_storage COMMAND test_storage)
target_link_libraries(test_storage storage domain Qt::Test)

add_executable(test_transaction_mapper test/test_TransactionMapper.cpp)
add_test(NAME test_transaction_mapper COMMAND test_transaction_mapper)
target_link_libraries(test_transaction_mapper storage domain Qt::Test)

add_executable(test_category_mapper test/test_CategoryMapper.cpp)
add_test(NAME test_category_mapper COMMAND test_category_mapper)
target_link_libraries(test_category_mapper storage domain Qt::Test)

add_executable(test_group_mapper test/test_GroupMapper.cpp)
add_test(NAME test_group_mapper COMMAND test_group_mapper)
target_link_libraries(test_group_mapper storage domain Qt::Test)

add_executable(test_prediction_mapper test/test_PredictionMapper.cpp)
add_test(NAME test_prediction_mapper COMMAND test_prediction_mapper)
target_link_libraries(test_prediction_mapper storage domain Qt::Test)
