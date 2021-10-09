#pragma once

#include "IFirebaseRtDbApi.h"

class QNetworkAccessManager;

class FirebaseRtDbAPI : public IFirebaseRtDbApi{

public:

    using JsonFuture = QFuture<QJsonObject>;

    FirebaseRtDbAPI() = delete;
    FirebaseRtDbAPI(QNetworkAccessManager * nam, const QString & dbUrl, const QString & accessToken);
    JsonFuture getObject(const QString & path) override;
    JsonFuture addObject(const QString & root, const QJsonObject & object) override;
    JsonFuture updateObjectByID(const QString &root, const QString &id, const QJsonObject &patch) override;

private:
    QNetworkAccessManager * m_nam = nullptr;
    QString m_dbUrl;
    QString m_token;

};
