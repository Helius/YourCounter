#include "StartUpScreenPresenter.h"
#include <QDebug>

StartUpScreenPresenter::StartUpScreenPresenter(StartupUseCaseUnq usecase)
    : QObject()
    , m_usecase(std::move(usecase))
{
    Q_ASSERT(m_usecase);
    static auto m_notifierHolder = m_usecase->stateProperty.addNotifier([this]() {
        StartupUseCase::State state = m_usecase->stateProperty.value();
        if (state == StartupUseCase::State::Finished) {
            emit startUpFinished();
        } else {
            emit stateChanged();
        }
    });
    m_usecase->start();
}

QString StartUpScreenPresenter::state() const
{
    switch (m_usecase->stateProperty.value()) {
    case StartupUseCase::State::Loading:
        return m_stateLoading;
    case StartupUseCase::State::Error:
        return m_stateError;
    case StartupUseCase::State::NeedDbUrl:
        return m_stateShowDbUrlInput;
    default:
        break;
    }
    return QString();
}

const QStringList& StartUpScreenPresenter::errors() const
{
    return m_usecase->getErrors();
}

void StartUpScreenPresenter::setDbUrl(const QString& url)
{
    m_usecase->setDbUrl(url);
}
