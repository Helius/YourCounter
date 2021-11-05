#include "SettingsImpl.h"

namespace {

QLatin1String dbUrlKey("dbUrl");
QLatin1String ATKey("AT");
QLatin1String OwnerNameKey("OwnerName");

}

QString SettingsRepoImpl::getDbUrl()
{
    return m_settings.value(dbUrlKey).toString();
}

QString SettingsRepoImpl::getAccessToken()
{
    return m_settings.value(ATKey).toString();
}

QString SettingsRepoImpl::getOwnerName()
{
    return m_settings.value(OwnerNameKey).toString();
}

void SettingsRepoImpl::setDbUrl(const QString& value)
{
    m_settings.setValue(dbUrlKey, value);
    m_settings.sync();
}

void SettingsRepoImpl::setAccessToken(const QString& value)
{
    m_settings.setValue(ATKey, value);
    m_settings.sync();
}

void SettingsRepoImpl::setOwnerName(const QString& value)
{
    m_settings.setValue(OwnerNameKey, value);
    m_settings.sync();
}
