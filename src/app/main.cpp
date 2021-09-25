#include <di.hpp>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <app/Theme.h>

#include <app/repos/transactionrepo.h>
#include <app/repos/datecolumnadapter.h>
#include <app/repos/transactionproviderfromfile.h>

#include <app/presenters/timescalebuttonpresenter.h>
#include <app/presenters/timelinetablemodel.h>

#include <qmlinjector/qmlinjector.h>
#include <qmlinjector/iqmlobjectcreator.h>
#include <qmlinjector/qmlinjectorbuilder.h>
#include <app/presenters/addtransactionbuttonpresenter.h>

int main(int argc, char *argv[])
{
    namespace di = boost::di;

//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    QmlInjectorBuilder builder;

    const auto injector = di::make_injector(
            di::bind<IDateColumnAdapter>.to<DateColumnAdapter>(),
            di::bind<ITransactionRepo>.to<TransactionRepo>(),
            di::bind<ITransactionProvider>.to<TransactionProviderFromFile>(),
            di::bind<QString>.to("/home/eugene/project/YourCounter/test/testdata/transactions.json")
    );

    builder.add<TimeScaleButtonPresenter>([&injector](const QVariant& )->std::unique_ptr<TimeScaleButtonPresenter>{
        return injector.create<std::unique_ptr<TimeScaleButtonPresenter>>();
    });

    builder.add<TimeLineTableModel>([&injector](const QVariant &)->std::unique_ptr<TimeLineTableModel>{
        return injector.create<std::unique_ptr<TimeLineTableModel>>();
    });
    builder.add<AddTransactionButtonPresenter>([&injector](const QVariant &)->AddTransactionButtonPresenterUnq{
        return injector.create<AddTransactionButtonPresenterUnq>();
    });

    qmlRegisterType<QmlInjector>("injector", 1, 0, "QmlInjector");
    qmlRegisterSingletonType<TimeLineTableModel>("Models", 1, 0, "TimeTable",
                                             [&injector]
                                             (QQmlEngine *, QJSEngine *) -> QObject * {
        return injector.create<std::unique_ptr<TimeLineTableModel>>().release();
    });


    engine.rootContext()->setContextObject(builder.build());

    const QUrl url(QStringLiteral("qrc:/src/app/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}