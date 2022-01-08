#ifndef DATECOLUMNADAPTER_H
#define DATECOLUMNADAPTER_H

#include <QObject>
#include <repos/idatecolumnadapter.h>

class DateColumnAdapter
    : public IDateColumnAdapter {
    Q_OBJECT

public:
    DateColumnAdapter() = default;

    // IDateColumnAdapter interface
public:
    bool isCurrent(int column) override;
    bool isSame(int column, const QDateTime& dateTime) override;
    void setScale(TimeScale scale) override;
    TimeScale scale() override { return m_scale; }
    QString columnName(int column) override;
    int columnCount() override;
    bool insideFromNow(int column, QDate date) override;

private:
    QDateTime colToDate(int column);

private:
    TimeScale m_scale = TimeScale::Week;
    int m_year = 2022; //TODO
};

#endif // DATECOLUMNADAPTER_H
