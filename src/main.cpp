#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <Theme.h>
#include <timelinetablemodel.h>
#include <repos/transactionrepo.h>
#include <repos/datecolumnadapter.h>
#include <repos/transactionproviderfromfile.h>

int main(int argc, char *argv[])
{
//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;


    auto * dateColumnAdapter = new DateColumnAdapter(&engine);
    auto * transactionProvider = new TransactionProviderFromFile("/home/eugene/project/YourCounter/test/testdata/transactions.json", &engine);
    auto * transactRepo = new TransactionRepo(dateColumnAdapter, transactionProvider, &engine);


    qmlRegisterSingletonType<Theme>("Ui", 1, 0, "Theme", [](QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject * {
        Q_UNUSED(engine)
        Q_UNUSED(scriptEngine)

        return new Theme(engine);
    });

    qmlRegisterSingletonType<TimeLineTableModel>("Models", 1, 0, "TimeTable",
                                                 [dateColumnAdapter, transactRepo]
                                                 (QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject * {
        Q_UNUSED(engine)
        Q_UNUSED(scriptEngine)

        return new TimeLineTableModel(transactRepo, dateColumnAdapter, engine);
    });

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
