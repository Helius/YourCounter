#include "StartUpUsecase.h"

StartupUseCase::StartupUseCase(INetworkSettingsRepoPtr settings, IEntityRepoPtr repo, IPredictionRepoPtr predictions)
    : QObject()
    , m_settings(settings)
    , m_repo(repo)
    , m_predictions(predictions)
{
    Q_ASSERT(m_settings);
    Q_ASSERT(m_repo);
    Q_ASSERT(m_predictions);

    stateProperty.setValue(State::Loading);

    connect(m_repo->categories().get(), &IRepoObserver::dataChanged, this, &StartupUseCase::checkReadyness);
    connect(m_repo->groups().get(), &IRepoObserver::dataChanged, this, &StartupUseCase::checkReadyness);
    connect(m_repo->transactions().get(), &IRepoObserver::dataChanged, this, &StartupUseCase::checkReadyness);

    connect(m_repo->categories().get(), &IRepoObserver::onError, this, &StartupUseCase::setError);
    connect(m_repo->groups().get(), &IRepoObserver::onError, this, &StartupUseCase::setError);
    connect(m_repo->transactions().get(), &IRepoObserver::onError, this, &StartupUseCase::setError);

    connect(m_predictions.get(), &IRepoObserver::dataChanged, this, &StartupUseCase::checkReadyness);
    connect(m_predictions.get(), &IRepoObserver::onError, this, &StartupUseCase::setError);
}

void StartupUseCase::setDbUrl(const QString& url)
{
    if (!url.isEmpty()) {
        m_settings->setDbUrl(url);
    }
    start();
}

void StartupUseCase::start()
{
    m_errors.clear();
    stateProperty.setValue(State::Loading);
    const auto dbUrl
        = m_settings->getDbUrl();
    if (dbUrl.isEmpty()) {
        stateProperty.setValue(State::NeedDbUrl);
        return;
    }
    m_repo->categories()->fetchAll();
    m_repo->groups()->fetchAll();
    m_repo->transactions()->fetchAll();
    m_predictions->fetchAll();
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
        && m_predictions->fetched()) {
        stateProperty.setValue(State::Finished);
    }
}

void StartupUseCase::setError(const QString& error)
{
    m_errors.append(error);
}