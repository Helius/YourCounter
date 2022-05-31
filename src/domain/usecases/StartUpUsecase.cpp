#include "StartUpUsecase.h"

StartupUseCase::StartupUseCase(INetworkSettingsRepoPtr settings, IEntityRepoPtr repo, ICredentialStorePtr cred, IAuthServicePtr auth)
    : QObject()
    , m_settings(settings)
    , m_repo(repo)
    , m_credentialStore(cred)
    , m_auth(auth)
{
    Q_ASSERT(m_settings);
    Q_ASSERT(m_repo);

    stateProperty.setValue(State::Loading);

    connect(m_repo->categories().get(), &IRepoObserver::dataChanged, this, &StartupUseCase::checkReadyness);
    connect(m_repo->groups().get(), &IRepoObserver::dataChanged, this, &StartupUseCase::checkReadyness);
    connect(m_repo->transactions().get(), &IRepoObserver::dataChanged, this, &StartupUseCase::checkReadyness);
    connect(m_repo->wallets().get(), &IRepoObserver::dataChanged, this, &StartupUseCase::checkReadyness);

    connect(m_repo->categories().get(), &IRepoObserver::onError, this, &StartupUseCase::setError);
    connect(m_repo->groups().get(), &IRepoObserver::onError, this, &StartupUseCase::setError);
    connect(m_repo->transactions().get(), &IRepoObserver::onError, this, &StartupUseCase::setError);
    connect(m_repo->wallets().get(), &IRepoObserver::onError, this, &StartupUseCase::setError);
}

void StartupUseCase::loginWithParams(const NetworkSettings& settings, const Credentials& creds)
{
    m_settings->set(settings);
    m_credentialStore->setCredentional(creds);
    start();
}

NetworkSettings StartupUseCase::getNetworkSettings()
{
    return m_settings->get();
}

Credentials StartupUseCase::getCredentials()
{
    return m_credentialStore->getCredentials();
}

void StartupUseCase::start()
{
    m_errors.clear();
    stateProperty.setValue(State::Loading);
    const auto settings = m_settings->get();
    if (!settings) {
        qWarning() << "Need network settings to start";
        stateProperty.setValue(State::NeedParams);
        return;
    }

    auto fetch = [this] {
        m_repo->categories()->fetchAll();
        m_repo->groups()->fetchAll();
        m_repo->transactions()->fetchAll();
        m_repo->wallets()->fetchAll();
        checkReadyness();
    };

    if (!m_repo->needLogin()) {
        fetch();
    } else if (!m_credentialStore->hasCredential()) {
        qWarning() << "Need network credentials to start";
        stateProperty.setValue(State::NeedParams);
    } else {
        m_auth->signIn(m_credentialStore->getCredentials())
            .then(this, [this, f = std::move(fetch)](const QFuture<AuthResult> resultFuture) {
                AuthResult res = resultFuture.result();
                if (res.code != AuthResult::Code::Ok) {
                    stateProperty.setValue(State::AuthError);
                    qWarning() << "Auth error: " << res.msg;
                } else {
                    qDebug() << "Successfull auth";
                    f();
                }
            });
    }
}

void StartupUseCase::signUp(const NetworkSettings& settings, const Credentials& creds)
{
    if (!settings || !creds) {
        qWarning() << "Need network params and credentials to sign up";
        return;
    }
    m_settings->set(settings);
    m_auth->signUp(creds)
        .then(this, [this, settings, creds](AuthResult result) {
            if (result.code != AuthResult::Code::Ok) {
                stateProperty.setValue(State::AuthError);
                qWarning() << "Sign up auth error: " << result.msg;
            } else {
                m_credentialStore->setCredentional(creds);
                start();
            }
        });
}

const QStringList& StartupUseCase::getErrors() const
{
    return m_errors;
}

void StartupUseCase::checkReadyness()
{
    if (m_repo->categories()->fetched()
        && m_repo->groups()->fetched()
        && m_repo->transactions()->fetched()
        && m_repo->wallets()->fetched()) {
        stateProperty.setValue(State::Finished);
    }
}

void StartupUseCase::setError(const QString& error)
{
    qWarning() << error;
    m_errors.append(error);
}
