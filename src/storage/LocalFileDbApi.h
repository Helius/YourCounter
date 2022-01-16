#pragma once
#include "IFirebaseRtDbApi.h"

class LocalFileDbApi : public IFirebaseRtDbApi
{
public:
    LocalFileDbApi();

    // IFirebaseRtDbApi interface
public:
    JsonFuture getObject(const QString &path) override;
    JsonFuture addObject(const QString &root, const QJsonObject &object) override;
    JsonFuture updateObject(const QString &root, const QString &id, const QJsonObject &patch) override;
    JsonFuture deleteObject(const QString &root, const QString &id) override;
private:
    QJsonObject m_storage;
};

