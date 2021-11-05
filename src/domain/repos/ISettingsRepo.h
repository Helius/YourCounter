#pragma once

#include <QString>

class ISettingsRepo {
public:
    virtual QString getDbUrl() = 0;
    virtual QString getAccessToken() = 0;
    virtual QString getOwnerName() = 0;

    virtual void setDbUrl(const QString&) = 0;
    virtual void setAccessToken(const QString&) = 0;
    virtual void setOwnerName(const QString&) = 0;
};

using ISettingsRepoPtr = std::shared_ptr<ISettingsRepo>;
