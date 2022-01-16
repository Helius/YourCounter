#include "LocalFileDbApi.h"
#include <QJsonArray>
#include <QUuid>

LocalFileDbApi::LocalFileDbApi()
{
    m_storage = {
        { "/groups",
            QJsonObject { { "gid1",
                QJsonObject { { "name", "gorup1" } } } } },
        { "/categories",
            { QJsonObject {
                { "cid1", QJsonObject { { "name", "book" }, { "groupId", "gid1" } } },
                { "cid2", QJsonObject { { "name", "food" }, { "groupId", "gid1" } } } } } },
        { "/transaction",
            QJsonObject { { "tid1",
                QJsonObject {
                    { "amount", -1000 },
                    { "categoryId", "cid1" },
                    { "who", "pc" },
                    { "comment", "bla-bla" },
                    { "when", "20220101" } } } } },

    };
}

IFirebaseRtDbApi::JsonFuture LocalFileDbApi::getObject(const QString& path)
{
    qDebug() << "getObject with path:" << path;
    return QtFuture::makeReadyFuture<QJsonObject>(m_storage.value(path).toObject());
}

IFirebaseRtDbApi::JsonFuture LocalFileDbApi::addObject(const QString& root, const QJsonObject& object)
{
    QString key = QUuid::createUuid().toString(QUuid::StringFormat::WithoutBraces);
    QJsonObject r = m_storage.value(root).toObject();
    r.insert(key, object);
    m_storage.insert(root, r);
    return QtFuture::makeReadyFuture(QJsonObject({ { "name", key } }));
}

IFirebaseRtDbApi::JsonFuture LocalFileDbApi::updateObject(const QString& root, const QString& id, const QJsonObject& patch)
{
    QJsonObject r = m_storage.value(root).toObject();
    QJsonObject obj = r.value(id).toObject();
    r.insert(id, patch);
    return QtFuture::makeReadyFuture<QJsonObject>();
}

IFirebaseRtDbApi::JsonFuture LocalFileDbApi::deleteObject(const QString& root, const QString& id)
{
    QJsonObject r = m_storage.value(root).toObject();
    r.remove(id);
    m_storage.insert(root, r);
    return QtFuture::makeReadyFuture<QJsonObject>();
}
