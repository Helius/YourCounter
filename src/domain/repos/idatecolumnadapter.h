#ifndef IDATEADAPTERREPO_H
#define IDATEADAPTERREPO_H

#include <QObject>

class IDateColumnAdapter
    : public QObject {
    Q_OBJECT

public:
    enum class TimeScale : int {
        Month = 0,
        Week,
        Day,
    };

public:
    virtual bool isCurrent(int column) = 0;
    virtual bool isSame(int column, const QDateTime& dateTime) = 0;
    virtual QString columnName(int column) = 0;
    virtual int columnCount() = 0;
    virtual void setScale(TimeScale scale) = 0;
    virtual TimeScale scale() = 0;
    virtual bool insideFromNow(int column, QDate date) = 0;

signals:
    void scaleChanged();

public:
    using QObject::QObject;
    ~IDateColumnAdapter() = default;
};

#endif // IDATEADAPTERREPO_H
