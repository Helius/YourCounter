#pragma once

#include <QSettings>
#include <repos/INetworkSettingsRepo.h>

class NetworkSettingsRepoImpl
    : public INetworkSettingsRepo {

public:
    NetworkSettingsRepoImpl() = default;
    ~NetworkSettingsRepoImpl() = default;

    // INetworkSettingsRepo interface
public:
    NetworkSettings get() override;
    void set(const NetworkSettings&) override;

private:
    QString getDbUrl();
    QString getAccessToken();
    void setDbUrl(const QString&);
    void setAppToken(const QString&);

private:
    QSettings m_settings;
};
