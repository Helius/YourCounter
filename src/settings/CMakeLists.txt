cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -pedantic -Werror)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Test REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Test REQUIRED)

add_library(settings
	SettingsImpl.cpp
	SettingsImpl.h
	CredentialStoreImpl.cpp
	CredentialStoreImpl.h
	simplecrypt.h
	simplecrypt.cpp
	)

target_include_directories(settings
	INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}
	)

target_link_libraries(
	    settings
		PRIVATE domain
		PRIVATE Qt${QT_VERSION_MAJOR}::Core
)

enable_testing(true)

add_executable(test_simplecrypto test/test_simplecrypt.cpp simplecrypt.cpp)
add_test(NAME test_simplecrypto COMMAND test_simplecrypto)
target_link_libraries(test_simplecrypto Qt::Test)

