#include "firebaseRtDbAPI.h"
#include <QJsonDocument>
#include <QNetworkReply>

FirebaseRtDbAPI::FirebaseRtDbAPI(QNetworkAccessManager *nam,
                                 const QString &dbUrl,
                                 const QString &accessToken)
    : m_nam(nam), m_dbUrl(dbUrl), m_token(accessToken) {
  Q_ASSERT(!m_dbUrl.isEmpty());
  Q_ASSERT(m_nam);
}

FirebaseRtDbAPI::JsonFuture FirebaseRtDbAPI::getObject(const QString &path) {
  QUrl url;
  url.setUrl(m_dbUrl);
  url.setPath(path + ".json");

  QNetworkRequest request(url);
  request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
  QNetworkReply *reply = m_nam->get(request);

  QFuture<QJsonObject> future =
      QtFuture::connect(reply, &QNetworkReply::finished)
          .then([this, reply] { return handler(reply); })
          .onFailed([] {
            qWarning() << "Terrible error happened";
            return QJsonObject();
          });

  return future;
}

FirebaseRtDbAPI::JsonFuture
FirebaseRtDbAPI::addObject(const QString &root, const QJsonObject &object) {
  QUrl url;
  url.setUrl(m_dbUrl);
  url.setPath(root + ".json");

  QNetworkRequest request(url);
  request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
  QByteArray data = QJsonDocument(object).toJson();
  QNetworkReply *reply = m_nam->post(request, data);

  QFuture<QJsonObject> future =
      QtFuture::connect(reply, &QNetworkReply::finished)
          .then([this, reply] { return handler(reply); })
          .onFailed([] {
            qWarning() << "Terrible error happened";
            return QJsonObject();
          });

  return future;
}

FirebaseRtDbAPI::JsonFuture
FirebaseRtDbAPI::updateObject(const QString &root, const QString &id,
                              const QJsonObject &patch) {
  QUrl url;
  url.setUrl(m_dbUrl);
  url.setPath(root + "/" + id + ".json");

  QNetworkRequest request(url);
  request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
  QByteArray data = QJsonDocument(patch).toJson();
  QNetworkReply *reply = m_nam->sendCustomRequest(request, "patch", data);

  QFuture<QJsonObject> future =
      QtFuture::connect(reply, &QNetworkReply::finished)
          .then([this, reply] { return handler(reply); })
          .onFailed([] {
            qWarning() << "Terrible error happened";
            return QJsonObject();
          });
  ;

  return future;
}

FirebaseRtDbAPI::JsonFuture FirebaseRtDbAPI::deleteObject(const QString &,
                                                          const QString &) {
  return QtFuture::makeReadyFuture(QJsonObject());
}

QJsonObject FirebaseRtDbAPI::handler(QNetworkReply *reply) {
  auto data = reply->readAll();
  qDebug() << "Got smth from network:" << data;

  auto errorStr = reply->errorString();
  auto err = reply->error();
  reply->deleteLater();

  if (err || !errorStr.isEmpty()) {
    qWarning() << "NetworkError: " << err << errorStr;
    return QJsonObject();
  }
  return QJsonDocument::fromJson(data).object();
}
