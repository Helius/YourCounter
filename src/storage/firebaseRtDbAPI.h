#pragma once

#include <QString>
#include <QJsonObject>
#include <QFuture>
#include <QNetworkAccessManager>


class FirebaseRtDbAPI {
public:
    FirebaseRtDbAPI() = delete;
    FirebaseRtDbAPI(QNetworkAccessManager * nam, const QString & dbUrl, const QString & accessToken);
    QFuture<QJsonObject> getObject(const QString & path);
//    QFuture<QJsonObject> getObjectsById(const QString & id);
    QFuture<struct QString> addObject(const QString & root, const QJsonObject & object);
//    QFuture<void> updateObjectByID(const QString & id, const QJsonObject & patch);
//    QFuture<void> deleteObjectByID(const QString & id);

private:
    QNetworkAccessManager * m_nam = nullptr;
    QString m_dbUrl;
    QString m_token;
};

using FirebaseRtDbAPIUnq = std::unique_ptr<FirebaseRtDbAPI>;
