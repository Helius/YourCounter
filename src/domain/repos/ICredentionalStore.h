#pragma once

#include <QString>

struct Credentials {
    QString name;
    QString passwd;
    operator bool() const
    {
        return !name.isEmpty() && !passwd.isEmpty();
    }
};

class ICredentialStore {
public:
    virtual Credentials getCredentials() = 0;
    virtual void setCredentional(const Credentials& credentials) = 0;
    virtual bool hasCredential() const = 0;
    virtual ~ICredentialStore() = default;
};

using ICredentialStorePtr = std::shared_ptr<ICredentialStore>;