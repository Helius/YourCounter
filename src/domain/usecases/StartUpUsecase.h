#pragma once

#include <QObject>
#include <QProperty>
#include <repos/IEntityRepo.h>
#include <repos/INetworkSettingsRepo.h>
#include <repos/IPredictionRepo.h>

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
    StartupUseCase(INetworkSettingsRepoPtr settings, IEntityRepoPtr repo, IPredictionRepoPtr predictions);
    void setDbUrl(const QString& url);

    QProperty<State> stateProperty;

public slots:
    void start();
    const QStringList& getErrors() const;

private:
    void checkReadyness();
    void setError(const QString&);

private:
    INetworkSettingsRepoPtr m_settings;
    IEntityRepoPtr m_repo;
    IPredictionRepoPtr m_predictions;
    QStringList m_errors;
};

using StartupUseCaseUnq = std::unique_ptr<StartupUseCase>;
