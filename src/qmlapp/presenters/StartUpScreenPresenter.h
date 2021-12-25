#pragma once

#include <QObject>
#include <QStringList>
#include <usecases/startupusecase.h>

class StartUpScreenPresenter : public QObject {

    Q_OBJECT

    Q_PROPERTY(QString state READ state NOTIFY stateChanged FINAL)
    Q_PROPERTY(QStringList errors READ errors NOTIFY stateChanged)

    Q_PROPERTY(QString StateError MEMBER m_stateError CONSTANT FINAL)
    Q_PROPERTY(QString StateLoading MEMBER m_stateLoading CONSTANT FINAL)
    Q_PROPERTY(QString StateShowDbUrlInput MEMBER m_stateShowDbUrlInput CONSTANT FINAL)

public:
    explicit StartUpScreenPresenter(StartupUseCaseUnq usecase);

public:
    QString state() const;
    const QStringList& errors() const;
    Q_INVOKABLE void setDbUrl(const QString& url);

signals:
    void startUpFinished();
    void stateChanged();

private:
    StartupUseCaseUnq m_usecase;
    QString m_state;
    const QString m_stateError { "stateError" };
    const QString m_stateLoading { "stateLoading" };
    const QString m_stateShowDbUrlInput { "stateShowDbUrlInput" };
};

using StartUpScreenPresenterUnq = std::unique_ptr<StartUpScreenPresenter>;