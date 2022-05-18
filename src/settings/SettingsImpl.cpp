#include "SettingsImpl.h"

namespace {

QLatin1String dbUrlKey("dbUrl");
QLatin1String ATKey("AppToken");

}

QString NetworkSettingsRepoImpl::getDbUrl()
{
    return m_settings.value(dbUrlKey).toString();
}

QString NetworkSettingsRepoImpl::getAccessToken()
{
    return m_settings.value(ATKey).toString();
}

void NetworkSettingsRepoImpl::setDbUrl(const QString& value)
{
    m_settings.setValue(dbUrlKey, value);
    m_settings.sync();
}

void NetworkSettingsRepoImpl::setAppToken(const QString& value)
{
    m_settings.setValue(ATKey, value);
    m_settings.sync();
}

NetworkSettings NetworkSettingsRepoImpl::get()
{
    return { getDbUrl(), getAccessToken() };
}

void NetworkSettingsRepoImpl::set(const NetworkSettings& settings)
{
    setDbUrl(settings.dbUrl);
    setAppToken(settings.appToken);
}
