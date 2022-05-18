#include "firebaseRtDbAPI.h"
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrlQuery>

FirebaseRtDbAPI::FirebaseRtDbAPI(QNetworkAccessManagerPtr nam, INetworkSettingsRepoPtr settings, IAuthTokenRepoPtr tokenRepo)
    : m_nam(nam)
    , m_settings(settings)
    , m_tokenRepo(tokenRepo)
{
    Q_ASSERT(m_nam);
    Q_ASSERT(m_settings);
    Q_ASSERT(m_tokenRepo);
}

FirebaseRtDbAPI::JsonFuture FirebaseRtDbAPI::getObject(const QString& path)
{
    QUrl url;
    url.setUrl(m_settings->get().dbUrl);
    url.setPath(path + ".json");
    QUrlQuery query;
    query.addQueryItem("auth", m_tokenRepo->getToken());
    url.setQuery(query);

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply* reply = m_nam->get(request);

    QFuture<QJsonObject> future = QtFuture::connect(reply, &QNetworkReply::finished)
                                      .then([this, reply] { return handler(reply); })
                                      .onFailed([] {
                                          qWarning() << "Terrible error happened";
                                          return QJsonObject();
                                      });
    return future;
}

FirebaseRtDbAPI::JsonFuture
FirebaseRtDbAPI::addObject(const QString& root, const QJsonObject& object)
{
    QUrl url;
    url.setUrl(m_settings->get().dbUrl);
    url.setPath(root + ".json");
    QUrlQuery query;
    query.addQueryItem("auth", m_tokenRepo->getToken());
    url.setQuery(query);

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = QJsonDocument(object).toJson();
    QNetworkReply* reply = m_nam->post(request, data);

    QFuture<QJsonObject> future = QtFuture::connect(reply, &QNetworkReply::finished)
                                      .then([this, reply] { return handler(reply); })
                                      .onFailed([] {
                                          qWarning() << "Terrible error happened";
                                          return QJsonObject();
                                      });
    return future;
}

FirebaseRtDbAPI::JsonFuture
FirebaseRtDbAPI::updateObject(const QString& root, const QString& id,
    const QJsonObject& patch)
{
    QUrl url;
    url.setUrl(m_settings->get().dbUrl);
    url.setPath(root + "/" + id + ".json");
    QUrlQuery query;
    query.addQueryItem("auth", m_tokenRepo->getToken());
    url.setQuery(query);

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = QJsonDocument(patch).toJson(QJsonDocument::Compact);
    QNetworkReply* reply = m_nam->sendCustomRequest(request, "PATCH", data);

    QFuture<QJsonObject> future = QtFuture::connect(reply, &QNetworkReply::finished)
                                      .then([this, reply] { return handler(reply); })
                                      .onFailed([] {
                                          qWarning() << "Terrible error happened";
                                          return QJsonObject();
                                      });
    return future;
}

FirebaseRtDbAPI::JsonFuture FirebaseRtDbAPI::deleteObject(const QString&,
    const QString&)
{
    qWarning() << "deleteObject not implemented yet";
    return QtFuture::makeReadyFuture(QJsonObject());
}

QJsonObject FirebaseRtDbAPI::handler(QNetworkReply* reply)
{
    auto data = reply->readAll();

    auto errorStr = reply->errorString();
    auto err = reply->error();
    reply->deleteLater();

    if (err != QNetworkReply::NoError) {
        qWarning() << "NetworkError: " << err << errorStr;
        return QJsonObject();
    }
    return QJsonDocument::fromJson(data).object();
}
