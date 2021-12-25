#pragma once

#include "IFirebaseRtDbApi.h"
#include <repos/INetworkSettingsRepo.h>

class QNetworkAccessManager;
using QNetworkAccessManagerPtr = std::shared_ptr<QNetworkAccessManager>;
class QNetworkReply;

class FirebaseRtDbAPI : public IFirebaseRtDbApi {

public:
    using JsonFuture = QFuture<QJsonObject>;

    FirebaseRtDbAPI() = delete;
    FirebaseRtDbAPI(QNetworkAccessManagerPtr nam, INetworkSettingsRepoPtr settings);
    JsonFuture getObject(const QString& path) override;
    JsonFuture addObject(const QString& root, const QJsonObject& object) override;
    JsonFuture updateObject(const QString& root, const QString& id, const QJsonObject& patch) override;
    JsonFuture deleteObject(const QString& root, const QString& id) override;

private:
    QJsonObject handler(QNetworkReply* reply);

private:
    QNetworkAccessManagerPtr m_nam;
    INetworkSettingsRepoPtr m_settings;
};
