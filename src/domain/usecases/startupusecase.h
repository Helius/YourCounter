#pragma once

#include <QObject>
#include <QProperty>
#include <repos/IEntityRepo.h>
#include <repos/ISettingsRepo.h>

class StartupUseCase
    : public QObject {
    Q_OBJECT

public:
    enum class State {
        Loading = 0,
        NeedDbUrl,
        Error,
        Finished
    };

public:
    StartupUseCase() = delete;
    StartupUseCase(ISettingsRepoPtr settings, IEntityRepoPtr repo);
    void setDbUrl(const QString& url);

    QProperty<State> stateProperty;

public slots:
    void start();
    const QStringList& getErrors() const;

private:
    void checkReadyness();
    void setError(const QString&);

private:
    ISettingsRepoPtr m_settings;
    IEntityRepoPtr m_repo;
    QStringList m_errors;
};

using StartupUseCaseUnq = std::unique_ptr<StartupUseCase>;
