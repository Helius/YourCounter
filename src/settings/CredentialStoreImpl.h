#pragma once

#include "simplecrypt.h"
#include <QSettings>
#include <repos/ICredentionalStore.h>

class CredentialStoreImpl : public ICredentialStore {
public:
    CredentialStoreImpl();

    Credentials getCredentials() override;
    void setCredentional(const Credentials& credentials) override;
    bool hasCredential() const override;

private:
    QSettings m_settings;
    SimpleCrypt m_crypt;
};
