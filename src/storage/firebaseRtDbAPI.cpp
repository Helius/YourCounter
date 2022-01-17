#include "firebaseRtDbAPI.h"
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QNetworkReply>

FirebaseRtDbAPI::FirebaseRtDbAPI(QNetworkAccessManagerPtr nam, INetworkSettingsRepoPtr settings)
    : m_nam(nam)
    , m_settings(settings)
{
    Q_ASSERT(m_nam);
    Q_ASSERT(m_settings);
}

FirebaseRtDbAPI::JsonFuture FirebaseRtDbAPI::getObject(const QString& path)
{
    QUrl url;
    url.setUrl(m_settings->getDbUrl());
    url.setPath(path + ".json");

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
    url.setUrl(m_settings->getDbUrl());
    url.setPath(root + ".json");

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
    url.setUrl(m_settings->getDbUrl());
    url.setPath(root + "/" + id + ".json");

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
    return QtFuture::makeReadyFuture(QJsonObject());
}

QJsonObject FirebaseRtDbAPI::handler(QNetworkReply* reply)
{
    auto data = reply->readAll();
    qDebug() << "Got smth from network:" << data;

    auto errorStr = reply->errorString();
    auto err = reply->error();
    reply->deleteLater();

    if (err != QNetworkReply::NoError) {
        qWarning() << "NetworkError: " << err << errorStr;
        return QJsonObject();
    }
    return QJsonDocument::fromJson(data).object();
}
