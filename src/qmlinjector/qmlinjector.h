#ifndef QMLINJECTOR_H
#define QMLINJECTOR_H

#include <QQuickItem>
#include <QQmlComponent>

class QmlInjector : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(QVariant context READ context WRITE setContext NOTIFY contextChanged FINAL)
    Q_PROPERTY(QQmlComponent * sourceComponent READ sourceComponent WRITE sourceComponent NOTIFY sourceComponentChanged FINAL)

public:
    explicit QmlInjector(QQuickItem * parent = nullptr);
    ~QmlInjector();

    QVariant context() const { return m_context; }
    QQmlComponent * sourceComponent() const { return m_sourceComponent; }

    void setContext(QVariant context);
    void sourceComponent(QQmlComponent * sourceComponent);

signals:
    void contextChanged();
    void sourceComponentChanged();

private:
    void loadComponent();

private:
    QVariant m_context;
    QQmlComponent * m_sourceComponent;
};

#endif // QMLINJECTOR_H
