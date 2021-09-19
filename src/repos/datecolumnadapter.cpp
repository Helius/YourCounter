#include "datecolumnadapter.h"
#include <QDateTime>

DateColumnAdapter::DateColumnAdapter(QObject * parent)
    : IDateColumnAdapter(parent)
{}

bool DateColumnAdapter::isCurrent(int column)
{
    return isSame(column, QDateTime::currentDateTime());
}

bool DateColumnAdapter::isSame(int column, const QDateTime & dateTime)
{
    switch (m_scale) {
    case TimeScale::Month:
        return dateTime.date().month() - 1 == column;

    case TimeScale::Week:
        return dateTime.date().weekNumber() - 1 == column;

    case TimeScale::Day:
        return dateTime.daysTo(colToDate(column)) == 0;
    }

    return false;
}

int DateColumnAdapter::dateToColumn(const QDateTime &)
{
    return 0;
}

QDateTime DateColumnAdapter::colToDate(int column)
{
    switch (m_scale) {
    case TimeScale::Month:
        return QDateTime(QDate(m_year, 1, 1), QTime(0,0,0)).addMonths(column);
        break;

    case TimeScale::Week:
        return QDateTime(QDate(m_year, 1, 1), QTime(0,0,0)).addDays(7*column);
        break;

    case TimeScale::Day:
        return QDateTime(QDate(m_year, 1, 1), QTime(0,0,0)).addDays(column);
        break;
    }
    return QDateTime();
}

void DateColumnAdapter::setScale(IDateColumnAdapter::TimeScale scale)
{
    if(scale != m_scale) {
        m_scale = scale;
        emit scaleChanged();
    }
}

QString DateColumnAdapter::columnName(int column)
{
    const auto date = colToDate(column);

    switch (m_scale) {
    case TimeScale::Month:
        return date.toString("MMM");
    case TimeScale::Week:
        return date.toString("dd MM");
    case TimeScale::Day:
        return date.toString("dd MMM");
    }
    return QString();
}

int DateColumnAdapter::columnCount()
{
    switch (m_scale) {
    case TimeScale::Month:
        return 12;
    case TimeScale::Week:
        return 4*12;
    case TimeScale::Day:
        return 365;
    }
}
