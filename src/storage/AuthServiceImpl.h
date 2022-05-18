#pragma once

#include <QNetworkAccessManager>
#include <repos/IAuthService.h>
#include <repos/INetworkSettingsRepo.h>

class AuthServiceImpl : public IAuthService, public IAuthTokenRepo {
public:
    AuthServiceImpl(INetworkSettingsRepoPtr settings, std::shared_ptr<QNetworkAccessManager> nam);

    QFuture<AuthResult> signUp(const Credentials& credentials) override;
    QFuture<AuthResult> signIn(const Credentials& credentials) override;
    void signOut() override;

    // IAuthTokenRepo interface
public:
    QString getToken() override;

private:
    QFuture<AuthResult> makeRequest(const QString& url, const Credentials& credentials);
    AuthResult handleReply(QNetworkReply* reply);

private:
    INetworkSettingsRepoPtr m_settings;
    std::shared_ptr<QNetworkAccessManager> m_nam;
    QString m_token;
};
