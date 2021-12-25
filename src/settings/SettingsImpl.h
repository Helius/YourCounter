#pragma once

#include <QSettings>
#include <repos/INetworkSettingsRepo.h>

class NetworkSettingsRepoImpl
    : public INetworkSettingsRepo {

public:
    NetworkSettingsRepoImpl() = default;
    ~NetworkSettingsRepoImpl() = default;

    // ISettingsRepo interface
public:
    QString getDbUrl() override;
    QString getAccessToken() override;
    void setDbUrl(const QString&) override;
    void setAccessToken(const QString&) override;

private:
    QSettings m_settings;
};
