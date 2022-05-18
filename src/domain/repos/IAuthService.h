#pragma once

#include <QFuture>
#include <QString>
#include <repos/ICredentionalStore.h>

struct AuthResult {

public:
    AuthResult() = default;
    enum class Code {
        Ok,
        Error
    };
    Code code = Code::Ok;
    QString msg;
};

class IAuthTokenRepo {
public:
    virtual QString getToken() = 0;

    virtual ~IAuthTokenRepo() = default;
};

class IAuthService {
public:
    virtual QFuture<AuthResult> signUp(const Credentials& credentials) = 0;
    virtual QFuture<AuthResult> signIn(const Credentials& credentials) = 0;
    virtual void signOut() = 0;

    virtual ~IAuthService() = default;
};

using IAuthServicePtr = std::shared_ptr<IAuthService>;
using IAuthTokenRepoPtr = std::shared_ptr<IAuthTokenRepo>;