#pragma once

#include <QSettings>
#include <repos/ISettingsRepo.h>

class SettingsRepoImpl
    : public ISettingsRepo {

    SettingsRepoImpl() = default;

    // ISettingsRepo interface
public:
    QString getDbUrl() override;
    QString getAccessToken() override;
    QString getOwnerName() override;
    void setDbUrl(const QString&) override;
    void setAccessToken(const QString&) override;
    void setOwnerName(const QString&) override;

private:
    QSettings m_settings;
};
