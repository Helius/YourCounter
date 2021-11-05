#include <../thirdparty/di.hpp>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "repos/datecolumnadapter.h"
//#include <transactionproviderfromfile.h>
//#include <transactionrepo.h>

//#include "presenters/timelinetablemodel.h"
//#include "presenters/timescalebuttonpresenter.h"

//#include "presenters/addtransactionbuttonpresenter.h"
//#include "presenters/transactionlistmodel.h"
#include "qmlinjector/iqmlobjectcreator.h"
#include "qmlinjector/qmlinjector.h"
#include "qmlinjector/qmlinjectorbuilder.h"
#include <firebaseRtDbAPI.h>

int main(int argc, char* argv[])
{
    namespace di = boost::di;

    //    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setOrganizationName("ghelius");
    QCoreApplication::setOrganizationDomain("ghelius@gmail.com");
    QCoreApplication::setApplicationName("YourCounter");

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    QmlInjectorBuilder builder;

    const auto injector = di::make_injector(
        di::bind<IDateColumnAdapter>.to<DateColumnAdapter>(),
        di::bind<QString>.to("/home/eugene/project/YourCounter/test/testdata/transactions.json"));

    //    builder.add<TimeScaleButtonPresenter>([&injector](const QVariant&) -> std::unique_ptr<TimeScaleButtonPresenter> {
    //        return injector.create<std::unique_ptr<TimeScaleButtonPresenter>>();
    //    });
    //    builder.add<TimeLineTableModel>([&injector](const QVariant&) -> std::unique_ptr<TimeLineTableModel> {
    //        return injector.create<std::unique_ptr<TimeLineTableModel>>();
    //    });
    //    builder.add<AddTransactionButtonPresenter>([&injector](const QVariant&) -> AddTransactionButtonPresenterUnq {
    //        return injector.create<AddTransactionButtonPresenterUnq>();
    //    });
    //    builder.add<TransactionSortedListModel>([&injector](const QVariant&) -> TransactionSortedListModelUnq {
    //        return injector.create<TransactionSortedListModelUnq>();
    //    });

    qmlRegisterType<QmlInjector>("injector", 1, 0, "QmlInjector");
    //    qmlRegisterSingletonType<TimeLineTableModel>("Models", 1, 0, "TimeTable",
    //        [&injector](QQmlEngine*, QJSEngine*) -> QObject* {
    //            return injector.create<std::unique_ptr<TimeLineTableModel>>().release();
    //        });

    engine.rootContext()->setContextObject(builder.build());

    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject* obj, const QUrl& objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
