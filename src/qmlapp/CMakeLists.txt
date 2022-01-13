cmake_minimum_required(VERSION 3.14)

set(TS_FILES YourCounter_prg_001.ts)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick LinguistTools Test REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick LinguistTools Test REQUIRED)

set(SRC
	    ../thirdparty/di.hpp
		main.cpp
		Theme.cpp
		Theme.h

		qmlinjector/qmlinjector.h
		qmlinjector/qmlinjector.cpp
		qmlinjector/qmlinjectorbuilder.h
		qmlinjector/iqmlobjectcreator.h
		qmlinjector/iqmlobjectcreator.cpp

#		repos/datecolumnadapter.h
#		repos/datecolumnadapter.cpp

        presenters/StartUpScreenPresenter.h
		presenters/StartUpScreenPresenter.cpp
#		presenters/timescalebuttonpresenter.h
#		presenters/timescalebuttonpresenter.cpp
#		presenters/timelinetablemodel.cpp
#		presenters/timelinetablemodel.h
        presenters/AddTransactionPresenter.h
		presenters/AddTransactionPresenter.cpp
		presenters/AddGroupPresenter.h
		presenters/AddGroupPresenter.cpp
		presenters/AddCategoryPresenter.h
		presenters/AddCategoryPresenter.cpp
		presenters/TransactionListModel.h
		presenters/TransactionListModel.cpp
		presenters/CategoryListModel.h
		presenters/CategoryListModel.cpp
		presenters/CurentBalancePresenter.h
		presenters/CurentBalancePresenter.cpp
		presenters/MonthReportModel.h
		presenters/MonthReportModel.cpp
		presenters/EditTransactionPresenter.h
		presenters/EditTransactionPresenter.cpp

		viewmodel/AmountVm.h
		viewmodel/AmountVm.cpp
		viewmodel/TransactionFeildsVm.h
		viewmodel/TransactionFeildsVm.cpp
		)


add_executable(YourCounter
	    qml.qrc
		${TS_FILES}
		${SRC}
		)

target_compile_definitions(YourCounter
	    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(YourCounter
	    PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick
		domain
		settings
		storage
		)
