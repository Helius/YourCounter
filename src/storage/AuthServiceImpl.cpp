#include "AuthServiceImpl.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>

namespace {

QLatin1String singUpEndPoint("https://identitytoolkit.googleapis.com/v1/accounts:signUp?key=%1");
QLatin1String singInEndPoint("https://identitytoolkit.googleapis.com/v1/accounts:signInWithPassword?key=%1");

QByteArray getPayload(const QString& name, const QString& passwd)
{
    return QJsonDocument(
        { { "email", name },
            { "password", passwd },
            { "returnSecureToken", true } })
        .toJson();
}

}

AuthServiceImpl::AuthServiceImpl(
    INetworkSettingsRepoPtr settings,
    std::shared_ptr<QNetworkAccessManager> nam)
    : m_settings(settings)
    , m_nam(nam)
{
    Q_ASSERT(m_settings);
    Q_ASSERT(m_nam);
}

QFuture<AuthResult> AuthServiceImpl::signUp(const Credentials& credentials)
{
    QString url = singUpEndPoint.arg(m_settings->get().appToken);
    return makeRequest(url, credentials);
}

QFuture<AuthResult> AuthServiceImpl::signIn(const Credentials& credentials)
{
    QString url = singInEndPoint.arg(m_settings->get().appToken);
    return makeRequest(url, credentials);
}

void AuthServiceImpl::signOut()
{
    qWarning() << "signOut not implemented yet";
}

QString AuthServiceImpl::getToken()
{
    return m_token;
}

QFuture<AuthResult> AuthServiceImpl::makeRequest(const QString& url, const Credentials& credentials)
{
    Q_ASSERT(!!credentials);

    const auto payload = getPayload(credentials.name, credentials.passwd);

    QNetworkRequest newRequest((QUrl(url)));
    newRequest.setHeader(QNetworkRequest::ContentTypeHeader, QString("application/json"));
    auto reply = m_nam->post(newRequest, payload);
    auto future = QtFuture::connect(reply, &QNetworkReply::readyRead)
                      .then([this, reply] {
                          return handleReply(reply);
                      });

    return future;
}

AuthResult AuthServiceImpl::handleReply(QNetworkReply* reply)
{
    AuthResult result;

    auto data = reply->readAll();
    auto errorStr = reply->errorString();
    auto err = reply->error();
    reply->deleteLater();

    if (err != QNetworkReply::NoError) {
        qWarning() << "NetworkError: " << err << errorStr;
        result.code = AuthResult::Code::Error;
        result.msg = errorStr;
    }

    QJsonObject json = QJsonDocument::fromJson(data).object();

    if (json.contains("kind")) {
        QString idToken = json.value("idToken").toString();
        qDebug() << "Obtained user ID Token: " << idToken;
        qDebug() << "User signed in successfully!";
        m_token = idToken;
        result.code = AuthResult::Code::Ok;
    } else {
        result.code = AuthResult::Code::Error;
        result.msg = data;
    }

    return result;
}
