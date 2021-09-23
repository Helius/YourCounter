#ifndef QMLINJECTORBUILDER_H
#define QMLINJECTORBUILDER_H

#include "iqmlobjectcreator.h"

class QmlInjectorBuilder
{
public:

    template<typename T>
    void add(Creator c) {
        QString type(T::staticMetaObject.className());
        m_creators.insert(type.remove("*"), std::move(c));
    }

    QmlObjectCreator * build() {
        return new QmlObjectCreator(std::move(m_creators));
    }


private:
    QHash<QString, Creator> m_creators;
};


#endif // QMLINJECTORBUILDER_H
