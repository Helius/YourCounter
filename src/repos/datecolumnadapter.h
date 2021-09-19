#ifndef DATECOLUMNADAPTER_H
#define DATECOLUMNADAPTER_H

#include <QObject>
#include <repos/idatecolumnadapter.h>

class DateColumnAdapter
        : public IDateColumnAdapter
{
    Q_OBJECT

public:
    DateColumnAdapter(QObject * parent = nullptr);

    // IDateColumnAdapter interface
public:
    bool isCurrent(int column) override;
    bool isSame(int column, const QDateTime &dateTime) override;
    int dateToColumn(const QDateTime &dateTime) override;
    void setScale(TimeScale scale) override;
    TimeScale scale() override { return m_scale; }
    QString columnName(int column) override;
    int columnCount() override;

private:
    QDateTime colToDate(int column);

private:
    TimeScale m_scale = TimeScale::Day;
    int m_year = 2021; //TODO
};

#endif // DATECOLUMNADAPTER_H
