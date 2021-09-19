#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <src/Theme.h>
#include <src/timelinetablemodel.h>
#include <src/repos/transactionrepo.h>
#include <src/repos/datecolumnadapter.h>

int main(int argc, char *argv[])
{
//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;


    auto * dateColumnAdapter = new DateColumnAdapter(&engine);
    auto * transactRepo = new TransactionRepo(dateColumnAdapter, &engine);


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
