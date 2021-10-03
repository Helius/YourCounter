#ifndef INTERVAL_H
#define INTERVAL_H

#include <QDateTime>

class Interval {

public:
    Interval() = default;
    Interval(QDateTime start, size_t days)
        : start(start)
        , days(days)
    {}

    bool contains(const QDateTime & dateTime) const
    {
        return (dateTime >= start) && (dateTime < start.addDays(days));
    }

    bool isEmpty() const { return !start.isValid() || days == 0; }

private:
    QDateTime start;
    size_t days;
};



#endif // INTERVAL_H
