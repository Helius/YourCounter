#pragma once

#include <QString>
#include <QJsonObject>
#include <QFuture>
#include <QNetworkAccessManager>


class FirebaseRtDbAPI {

public:

    using JsonFuture = QFuture<QJsonObject>;

    FirebaseRtDbAPI() = delete;
    FirebaseRtDbAPI(QNetworkAccessManager * nam, const QString & dbUrl, const QString & accessToken);
    JsonFuture getObject(const QString & path);
    JsonFuture addObject(const QString & root, const QJsonObject & object);
    JsonFuture updateObjectByID(const QString &root, const QString &id, const QJsonObject &patch);

private:
    QNetworkAccessManager * m_nam = nullptr;
    QString m_dbUrl;
    QString m_token;

};

using FirebaseRtDbAPIUnq = std::unique_ptr<FirebaseRtDbAPI>;
