#pragma once

#include <QObject>
#include <QStringList>
#include <usecases/StartUpUsecase.h>

class StartUpScreenPresenter : public QObject {

    Q_OBJECT

    Q_PROPERTY(QString state READ state NOTIFY stateChanged FINAL)
    Q_PROPERTY(QStringList errors READ errors NOTIFY stateChanged)

    Q_PROPERTY(QString StateError MEMBER m_stateError CONSTANT FINAL)
    Q_PROPERTY(QString StateLoading MEMBER m_stateLoading CONSTANT FINAL)
    Q_PROPERTY(QString StateShowInputs MEMBER m_stateShowInputs CONSTANT FINAL)

    Q_PROPERTY(QString dbUrl MEMBER m_dbUrl NOTIFY inputDataChanged FINAL)
    Q_PROPERTY(QString appToken MEMBER m_appToken NOTIFY inputDataChanged FINAL)
    Q_PROPERTY(QString userName MEMBER m_userName NOTIFY inputDataChanged FINAL)
    Q_PROPERTY(QString passwd MEMBER m_passwd NOTIFY inputDataChanged FINAL)

    Q_PROPERTY(bool signEnabled READ signEnabled NOTIFY inputDataChanged FINAL)

public:
    explicit StartUpScreenPresenter(StartupUseCaseUnq usecase);

public:
    QString state() const;
    const QStringList& errors() const;
    bool signEnabled() const;

    Q_INVOKABLE void signIn();
    Q_INVOKABLE void signUp();

signals:
    void startUpFinished();
    void stateChanged();

    void inputDataChanged();

private:
    StartupUseCaseUnq m_usecase;
    QString m_state;
    const QString m_stateError { "stateError" };
    const QString m_stateLoading { "stateLoading" };
    const QString m_stateShowInputs { "stateShowInputs" };

    QString m_dbUrl;
    QString m_appToken;
    QString m_userName;
    QString m_passwd;
};

using StartUpScreenPresenterUnq = std::unique_ptr<StartUpScreenPresenter>;