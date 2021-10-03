#include "qmlinjector.h"
#include <qmlapp/presenters/timescalebuttonpresenter.h>
#include <QTimer>
#include <QQmlEngine>
#include <QQmlContext>
#include "iqmlobjectcreator.h"


QmlInjector::QmlInjector(QQuickItem *parent)
        : QQuickItem(parent) {
}

QmlInjector::~QmlInjector()
{
}

void QmlInjector::setContext(QVariant context)
{
    if (m_context == context)
        return;

    m_context = context;
    emit contextChanged();
}

void QmlInjector::sourceComponent(QQmlComponent * sourceComponent)
{
    if (m_sourceComponent == sourceComponent)
        return;
    m_sourceComponent = sourceComponent;
    emit sourceComponentChanged();
    QTimer::singleShot(0,this, [this]
                       (){
                           loadComponent();
                       });
}

void QmlInjector::loadComponent()
{
    if(m_sourceComponent == nullptr)
        return;

    QQmlEngine * engine = qmlEngine(this);
    QQmlContext * context = engine->rootContext();

    if (!context)
    {
        return;
    }

    QmlObjectCreator * creator = qobject_cast<QmlObjectCreator*>(context->contextObject());

    if (!creator)
    {
        return;
    }

    if (QObject * obj = m_sourceComponent->beginCreate(context))
    {
        obj->setParent(this);
        if (const auto metaObject = obj->metaObject())
        {
            for (int i = 0; i < metaObject->propertyCount(); ++i)
            {
                auto p = metaObject->property(i);
                if (p.name()[0] == '$')
                {
                    QString typeName = p.typeName();
                    if (p.isWritable())
                    {
                        QObject * value = creator->createObject(typeName.remove('*')).release();
                        QVariant val = QVariant::fromValue(value);
                        obj->setProperty(p.name(), val);
                        obj->setProperty("injector", QVariant::fromValue(this));

                    }
                }
            }
        }
        auto view = static_cast<QQuickItem*>(obj);
        if (!view)
            return;
        view->setParentItem(this);
        m_sourceComponent->completeCreate();
    }
}

