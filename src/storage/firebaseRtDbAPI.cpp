#include "firebaseRtDbAPI.h"
#include <QNetworkReply>
#include <QJsonDocument>

FirebaseRtDbAPI::FirebaseRtDbAPI(QNetworkAccessManager *nam, const QString &dbUrl, const QString &accessToken)
    : m_nam(nam)
    , m_dbUrl(dbUrl)
    , m_token(accessToken)
{
    Q_ASSERT(!m_dbUrl.isEmpty());
    Q_ASSERT(m_nam);
}

FirebaseRtDbAPI::JsonFuture FirebaseRtDbAPI::getObject(const QString & path)
{
    QUrl url;
    url.setUrl(m_dbUrl);
    url.setPath(path + ".json");

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply * reply = m_nam->get(request);

    QFuture<QJsonObject> future = QtFuture::connect(reply, &QNetworkReply::finished)
            .then([reply]{
                auto data = reply->readAll();
                qDebug() << "got smth from network:" << data;
                reply->deleteLater();
                return data;
            }).then([](const QByteArray & data){
                qDebug() << "try to parse:" << data;
                return QJsonDocument::fromJson(data).object();
            }).onFailed([](QNetworkReply::NetworkError error) {
                qWarning() << "error happened:" << error;
                return QJsonObject();
            }).onFailed([] {
                // handle any other error
                qDebug() << "terrible error happened";
                return QJsonObject();
            });;

    return future;
}

FirebaseRtDbAPI::JsonFuture FirebaseRtDbAPI::addObject(const QString &root, const QJsonObject &object) {
    QUrl url;
    url.setUrl(m_dbUrl);
    url.setPath(root  + ".json");

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = QJsonDocument(object).toJson();
    QNetworkReply * reply = m_nam->post(request, data);

    QFuture<QJsonObject> future = QtFuture::connect(reply, &QNetworkReply::finished)
            .then([reply]{
                auto data = reply->readAll();
                qDebug() << "got smth from network:" << data;
                reply->deleteLater();
                return data;
            }).then([](const QByteArray & data){
                qDebug() << "try to parse:" << data;
                return QJsonDocument::fromJson(data).object();
            }).onFailed([](QNetworkReply::NetworkError error) {
                qDebug() << "error happened:" << error;
                return QJsonObject();
            }).onFailed([] {
                // handle any other error
                qDebug() << "terrible error happened";
                return QJsonObject();
            });;

    return future;
}

FirebaseRtDbAPI::JsonFuture FirebaseRtDbAPI::updateObjectByID(const QString & root, const QString & id, const QJsonObject &patch) {
    QUrl url;
    url.setUrl(m_dbUrl);
    url.setPath(root + "/" + id + ".json");

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = QJsonDocument(patch).toJson();
    QNetworkReply * reply = m_nam->sendCustomRequest(request, "patch", data);

    QFuture<QJsonObject> future = QtFuture::connect(reply, &QNetworkReply::finished)
            .then([reply] {
                auto data = reply->readAll();
                qDebug() << "got smth from network:" << data;
                reply->deleteLater();
                return data;
            }).then([](const QByteArray &data) {
                return QJsonDocument::fromJson(data).object();
                qDebug() << "try to parse:" << data;
            }).onFailed([](QNetworkReply::NetworkError error) {
                qDebug() << "error happened:" << error;
                return QJsonObject();
            }).onFailed([] {
                // handle any other error
                qDebug() << "terrible error happened";
                return QJsonObject();
            });;

    return future;
}
