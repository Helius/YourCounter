#include "StartUpScreenPresenter.h"
#include <QDebug>
#include <QTimer>

StartUpScreenPresenter::StartUpScreenPresenter(StartupUseCaseUnq usecase)
    : QObject()
    , m_usecase(std::move(usecase))
{
    Q_ASSERT(m_usecase);
    static auto m_notifierHolder = m_usecase->stateProperty.addNotifier([this]() {
        StartupUseCase::State state = m_usecase->stateProperty.value();
        if (state == StartupUseCase::State::Finished) {
            QTimer::singleShot(1, this, [this]() { emit startUpFinished(); });
        } else {
            emit stateChanged();
        }
    });

    {
        const auto settings = m_usecase->getNetworkSettings();
        m_dbUrl = settings.dbUrl;
        m_appToken = settings.appToken;
    }
    {
        const auto creds = m_usecase->getCredentials();
        m_userName = creds.name;
        m_passwd = creds.passwd;
    }

    m_usecase->start();
}

QString StartUpScreenPresenter::state() const
{
    switch (m_usecase->stateProperty.value()) {
    case StartupUseCase::State::Loading:
        return m_stateLoading;
    case StartupUseCase::State::Error:
        return m_stateError;
    case StartupUseCase::State::AuthError:
    case StartupUseCase::State::NeedParams:
        return m_stateShowInputs;
    default:
        break;
    }
    return QString();
}

const QStringList& StartUpScreenPresenter::errors() const
{
    return m_usecase->getErrors();
}

bool StartUpScreenPresenter::signEnabled() const
{
    return !m_dbUrl.isEmpty() && !m_appToken.isEmpty() && !m_userName.isEmpty() && !m_passwd.isEmpty();
}

void StartUpScreenPresenter::signIn()
{
    m_usecase->loginWithParams({ m_dbUrl, m_appToken }, { m_userName, m_passwd });
}

void StartUpScreenPresenter::signUp()
{
    m_usecase->signUp({ m_dbUrl, m_appToken }, { m_userName, m_passwd });
}
