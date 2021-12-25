#ifndef QMLOBJECTCREATOR_H
#define QMLOBJECTCREATOR_H

#include <QHash>
#include <QObject>
#include <QVariant>
#include <functional>

using Creator = std::function<std::unique_ptr<QObject>(QVariant)>;
using Creators = QHash<QString, Creator>;

class QmlObjectCreator
    : public QObject {
    Q_OBJECT

public:
    QmlObjectCreator(Creators&& creators, QObject* parent = nullptr);

    std::unique_ptr<QObject> createObject(QString className);

private:
    Creators m_creators;
};

#endif // QMLOBJECTCREATOR_H
