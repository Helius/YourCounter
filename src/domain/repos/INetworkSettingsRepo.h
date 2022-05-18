#pragma once

#include <QString>

struct NetworkSettings {
    QString dbUrl;
    QString appToken;

    operator bool() const
    {
        return !dbUrl.isEmpty() && !appToken.isEmpty();
    }
};

class INetworkSettingsRepo {
public:
    virtual NetworkSettings get() = 0;

    virtual void set(const NetworkSettings&) = 0;

    virtual ~INetworkSettingsRepo() = default;
};

using INetworkSettingsRepoPtr = std::shared_ptr<INetworkSettingsRepo>;
