#ifndef QMLOBJECTCREATOR_H
#define QMLOBJECTCREATOR_H

#include <QObject>
#include <QHash>
#include <QVariant>
#include <functional>


using Creator = std::function<std::unique_ptr<QObject>(QVariant)>;
using Creators = QHash<QString, Creator>;

class QmlObjectCreator
    : public QObject
{
    Q_OBJECT

public:
    QmlObjectCreator(Creators && creators, QObject * parent = nullptr)
        : QObject(parent)
        , m_creators(std::move(creators))
    {}

    std::unique_ptr<QObject> createObject(QString className) {
        if(m_creators.contains(className)) {
            return m_creators[className](QVariant());
        } else {
            qCritical() << "No creator not found for " << className;
        }
        return {};
    }

    QObject * createObject();

private:
    Creators m_creators;
};

#endif // QMLOBJECTCREATOR_H
