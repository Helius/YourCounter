#pragma once

#include <QString>

class INetworkSettingsRepo {
public:
    virtual QString getDbUrl() = 0;
    virtual QString getAccessToken() = 0;

    virtual void setDbUrl(const QString&) = 0;
    virtual void setAccessToken(const QString&) = 0;

    virtual ~INetworkSettingsRepo() = default;
};

using INetworkSettingsRepoPtr = std::shared_ptr<INetworkSettingsRepo>;
