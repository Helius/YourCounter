cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -pedantic -Werror)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Test REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Test REQUIRED)

add_library(settings
	SettingsImpl.cpp
	SettingsImpl.h
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
