#ifndef THEME_H
#define THEME_H

#include <QObject>
#include <QColor>

class Theme : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QColor background MEMBER m_background FINAL)

public:
    explicit Theme(QObject *parent = nullptr);

    QColor background() const;

private:
    QColor m_background = QColor("blue");
};

#endif // THEME_H
