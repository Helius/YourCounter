#include <../thirdparty/di.hpp>
#include <QGuiApplication>
#include <QNetworkAccessManager>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "repos/datecolumnadapter.h"
//#include <transactionproviderfromfile.h>
//#include <transactionrepo.h>

//#include "presenters/timelinetablemodel.h"
//#include "presenters/timescalebuttonpresenter.h"

//#include "presenters/addtransactionbuttonpresenter.h"
//#include "presenters/transactionlistmodel.h"
#include "presenters/StartUpScreenPresenter.h"
#include "qmlinjector/iqmlobjectcreator.h"
#include "qmlinjector/qmlinjector.h"
#include "qmlinjector/qmlinjectorbuilder.h"
#include <EntityRepoImpl.h>
#include <firebaseRtDbAPI.h>
#include <usecases/startupusecase.h>

#include <SettingsImpl.h>
#include <repos/INetworkSettingsRepo.h>

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
        //        di::bind<IDateColumnAdapter>.to<DateColumnAdapter>(),
        //        di::bind<QString>.to("/home/eugene/project/YourCounter/test/testdata/transactions.json"),
        di::bind<QNetworkAccessManager>.to(std::make_shared<QNetworkAccessManager>()),
        di::bind<INetworkSettingsRepo>.to<NetworkSettingsRepoImpl>(),
        di::bind<IFirebaseRtDbApi>.to<FirebaseRtDbAPI>(),
        di::bind<IEntityRepo>.to<EntityRepoImpl>(),
        di::bind<StartupUseCase>.to<StartupUseCase>()
        //di::bind<StartUpScreenPresenter>.to<StartUpScreenPresenter>()
    );

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

    //    builder.add<StartUpScreenPresenter>([&injector](const QVariant&) -> StartUpScreenPresenterUnq {
    //        qDebug() << "try to inject StartUpPresenter";
    //        auto result = injector.create<StartUpScreenPresenter*>();
    //        //        qDebug() << "finally we created" << !!result;
    //        return std::unique_ptr<StartUpScreenPresenter>(result);
    //    });

    //    auto usecase = injector.create<StartupUseCaseUnq>();

    builder.add<StartUpScreenPresenter>([&injector](const QVariant&) -> StartUpScreenPresenterUnq {
        return injector.create<StartUpScreenPresenterUnq>();
    });

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
