#pragma once

#include <QObject>
#include <QProperty>
#include <repos/IAuthService.h>
#include <repos/ICredentionalStore.h>
#include <repos/IEntityRepo.h>
#include <repos/INetworkSettingsRepo.h>
#include <repos/IPredictionRepo.h>

class StartupUseCase
    : public QObject {

    Q_OBJECT

public:
    enum class State {
        Loading = 0,
        NeedParams,
        AuthError,
        Error,
        Finished
    };

public:
    StartupUseCase() = delete;
    StartupUseCase(
        INetworkSettingsRepoPtr settings,
        IEntityRepoPtr repo,
        ICredentialStorePtr cred,
        IAuthServicePtr auth);

    void loginWithParams(const NetworkSettings& settings, const Credentials& creds);
    NetworkSettings getNetworkSettings();
    Credentials getCredentials();
    const QStringList& getErrors() const;

    QProperty<State> stateProperty;

public slots:
    void start();
    void signUp(const NetworkSettings& settings, const Credentials& creds);

private:
    void checkReadyness();
    void setError(const QString&);

private:
    INetworkSettingsRepoPtr m_settings;
    IEntityRepoPtr m_repo;
    ICredentialStorePtr m_credentialStore;
    IAuthServicePtr m_auth;
    QStringList m_errors;
};

using StartupUseCaseUnq = std::unique_ptr<StartupUseCase>;
