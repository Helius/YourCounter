#pragma once

#include <QString>
#include <QFuture>
#include <QJsonObject>

class IFirebaseRtDbApi {
public:
    using JsonFuture = QFuture<QJsonObject>;

    virtual JsonFuture getObject(const QString & path) = 0;
    virtual JsonFuture addObject(const QString & root, const QJsonObject & object) = 0;
    virtual JsonFuture updateObjectByID(const QString &root, const QString &id, const QJsonObject &patch) = 0;

    virtual ~IFirebaseRtDbApi() = default;
};
using IFirebaseRtDbAPIUnq = std::unique_ptr<IFirebaseRtDbApi>;
