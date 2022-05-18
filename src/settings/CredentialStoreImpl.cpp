#include "CredentialStoreImpl.h"
#include "simplecrypt.h"

QLatin1String nameKey("cred0");
QLatin1String passwdKey("cred1");

CredentialStoreImpl::CredentialStoreImpl()
{
    m_crypt = SimpleCrypt(Q_UINT64_C(0x0ed164a320b9e02a));
}

Credentials CredentialStoreImpl::getCredentials()
{
    Credentials cred;
    cred.name = m_crypt.decryptToString(m_settings.value(nameKey).toString());
    cred.passwd = m_crypt.decryptToString(m_settings.value(passwdKey).toString());
    return cred;
}

void CredentialStoreImpl::setCredentional(const Credentials& credentials)
{
    m_settings.setValue(nameKey, m_crypt.encryptToString(credentials.name));
    m_settings.setValue(passwdKey, m_crypt.encryptToString(credentials.passwd));
}

bool CredentialStoreImpl::hasCredential() const
{
    return !m_settings.value(nameKey).isNull() && !m_settings.value(passwdKey).isNull();
}
