#pragma once

#include <QDate>

class Interval {
public:
    enum Scale {
        Day,
        Week,
        Month
    };
    Interval(QDate from, Scale scale, uint number)
    {
        if (scale == Month) {
            start = number == 0 ? from : QDate(from.year(), from.month(), 1).addMonths(number);
            end = QDate(from.year(), from.month(), 1).addMonths(1 + number);
        } else if (scale == Week) {
            start = number == 0 ? from : from.addDays(8 - from.dayOfWeek() + 7 * (number - 1));
            end = number == 0 ? from.addDays(8 - from.dayOfWeek()) : start.addDays(7);
        }
    }
    bool inside(QDate date) const
    {
        return ((date >= start) && (date < end));
    }

private:
    QDate start;
    QDate end;
};
