#include "iqmlobjectcreator.h"

QmlObjectCreator::QmlObjectCreator(Creators&& creators, QObject* parent)
    : QObject(parent)
    , m_creators(std::move(creators))
{
}

std::unique_ptr<QObject> QmlObjectCreator::createObject(QString className)
{
    if (m_creators.contains(className)) {
        return m_creators[className](QVariant());
    } else {
        qCritical() << "No creator not found for " << className;
    }
    return {};
}
