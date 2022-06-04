#include <../thirdparty/di.hpp>
#include <QGuiApplication>
#include <QNetworkAccessManager>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "qmlinjector/iqmlobjectcreator.h"
#include "qmlinjector/qmlinjector.h"
#include "qmlinjector/qmlinjectorbuilder.h"

#include <WalletBallanceProviderImpl.h>
#include <repos/IAuthService.h>
#include <repos/ICredentionalStore.h>
#include <repos/INetworkSettingsRepo.h>
#include <repos/IPredictionRepo.h>
#include <repos/IWalletBallanceProvider.h>
//#include <repos/datecolumnadapter.h>

//#include "presenters/timelinetablemodel.h"
//#include "presenters/timescalebuttonpresenter.h"
#include <usecases/AddNewTransactionUsecase.h>
#include <usecases/CurrentBalanceCalculateUsecase.h>
#include <usecases/EditTransactionUsecase.h>
#include <usecases/MonthReportUsecase.h>
#include <usecases/StartUpUsecase.h>
#include <usecases/wallets/AddNewWalletUsecase.h>

#include "presenters/AddCategoryPresenter.h"
#include "presenters/AddGroupPresenter.h"
#include "presenters/AddTransactionPresenter.h"
#include "presenters/CategoryListModel.h"
#include "presenters/CurentBalancePresenter.h"
#include "presenters/EditTransactionPresenter.h"
#include "presenters/MonthReportModel.h"
#include "presenters/StartUpScreenPresenter.h"
#include "presenters/TransactionListModel.h"
#include "presenters/wallets/AddNewWalletPresenter.h"
#include "presenters/wallets/NewTransferPresenter.h"
#include "presenters/wallets/WalletListModel.h"

#include <EntityRepoImpl.h>
#include <LocalFileDbApi.h>
//#include <PredictionRepoimpl.h>
#include <firebaseRtDbAPI.h>

#include <AuthServiceImpl.h>
#include <CredentialStoreImpl.h>
#include <SettingsImpl.h>

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
        di::bind<QNetworkAccessManager>.to(std::make_shared<QNetworkAccessManager>()),
        di::bind<INetworkSettingsRepo>.to<NetworkSettingsRepoImpl>(),
        di::bind<ICredentialStore>.to<CredentialStoreImpl>(),
        di::bind<IAuthService>.to<AuthServiceImpl>(),
        di::bind<IAuthTokenRepo>.to<AuthServiceImpl>(),
        di::bind<IFirebaseRtDbApi>.to<FirebaseRtDbAPI>(),
        //        di::bind<IFirebaseRtDbApi>.to<LocalFileDbApi>(),
        di::bind<IEntityRepo>.to<EntityRepoImpl>(),
        di::bind<IWalletBallanceProvider>.to<WalletBallanceProviderImpl>(),
        di::bind<AddNewTransactionUseCase>.to<AddNewTransactionUseCase>(),
        di::bind<AddNewGroupUseCase>.to<AddNewGroupUseCase>(),
        di::bind<StartupUseCase>.to<StartupUseCase>(),
        di::bind<CurrentBalanceCalculateUsecase>.to<CurrentBalanceCalculateUsecase>(),
        di::bind<EditTransactionUsecase>.to<EditTransactionUsecase>(),
        di::bind<MonthReportUsecase>.to<MonthReportUsecase>(),
        di::bind<AddNewWalletUseCase>.to<AddNewWalletUseCase>());

    //    builder.add<TimeScaleButtonPresenter>([&injector](const QVariant&) -> std::unique_ptr<TimeScaleButtonPresenter> {
    //        return injector.create<std::unique_ptr<TimeScaleButtonPresenter>>();
    //    });
    //    builder.add<TimeLineTableModel>([&injector](const QVariant&) -> std::unique_ptr<TimeLineTableModel> {
    //        return injector.create<std::unique_ptr<TimeLineTableModel>>();
    //    });

    builder.add<StartUpScreenPresenter>([&injector](const QVariant&) -> StartUpScreenPresenterUnq {
        return injector.create<StartUpScreenPresenterUnq>();
    });
    builder.add<TransactionSortedListModel>([&injector](const QVariant&) -> TransactionSortedListModelUnq {
        return injector.create<TransactionSortedListModelUnq>();
    });
    builder.add<GroupListModel>([&injector](const QVariant&) -> GroupListModelUnq {
        return injector.create<GroupListModelUnq>();
    });
    builder.add<CategorySortedListModel>([&injector](const QVariant& arg) -> CategorySortedListModelUnq {
        auto model = injector.create<CategorySortedListModelUnq>();
        //todo: probably bullshit
        model->setGroupId(arg.toString());
        return model;
    });
    builder.add<CategorySuggestModel>([&injector](const QVariant&) -> CategorySuggestModelUnq {
        return injector.create<CategorySuggestModelUnq>();
    });
    builder.add<AddTransactionPresenter>([&injector](const QVariant&) -> AddTransactionPresenterUnq {
        return injector.create<AddTransactionPresenterUnq>();
    });
    builder.add<AddCategoryPresenter>([&injector](const QVariant&) -> AddCategoryPresenterUnq {
        return injector.create<AddCategoryPresenterUnq>();
    });
    builder.add<AddGroupPresenter>([&injector](const QVariant&) -> AddGroupPresenterUnq {
        return injector.create<AddGroupPresenterUnq>();
    });
    builder.add<CurentBalancePresenter>([&injector](const QVariant&) -> CurentBalancePresenterUnq {
        return injector.create<CurentBalancePresenterUnq>();
    });
    builder.add<MonthReportSortedModel>([&injector](const QVariant&) -> MonthReportSortedModelUnq {
        return injector.create<MonthReportSortedModelUnq>();
    });
    builder.add<EditTransactionPresenter>([&injector](const QVariant& context) -> EditTransactionPresenterUnq {
        auto builder = injector.create<EditTransactionBuilderUnq>();
        return builder->build(context.toString());
    });
    builder.add<WalletListModel>([&injector](const QVariant&) -> WalletListModelUnq {
        return injector.create<WalletListModelUnq>();
    });
    builder.add<AddNewWalletPresenter>([&injector](const QVariant&) -> AddNewWalletPresenterUnq {
        return injector.create<AddNewWalletPresenterUnq>();
    });
    builder.add<NewTransferPresenter>([&injector](const QVariant&) -> NewTransferPresenterUnq {
        return injector.create<NewTransferPresenterUnq>();
    });

    qmlRegisterType<QmlInjector>("injector", 1, 0, "QmlInjector");

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
