#include "StartUpScreenPresenter.h"
#include <QDebug>

StartUpScreenPresenter::StartUpScreenPresenter(StartupUseCaseUnq usecase)
    : m_usecase(std::move(usecase))
{
    Q_ASSERT(m_usecase);
    qDebug() << "StartUpScreenPresenter::ctor";
    //TODO: bullshit, have to update to Qt6.2
    static auto m_notifierHolder = m_usecase->stateProperty.subscribe([this]() {
        StartupUseCase::State state = m_usecase->stateProperty.value();
        if (state == StartupUseCase::State::Finished) {
            emit startUpFinished();
        } else {
            emit stateChanged();
        }
    });
    m_usecase->start();
}

StartUpScreenPresenter::~StartUpScreenPresenter()
{
    qDebug() << "~StartUpScreenPresenter::dtor";
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
