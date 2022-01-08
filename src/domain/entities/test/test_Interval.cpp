#include "../interval.h"
#include <QtTest/QtTest>

class TestInterval : public QObject {
    Q_OBJECT

private slots:
    void TestMonthCurrent();
    void TestMonthFirst();
    void TestMonthSecond();

    void TestWeekCurrent();
    void TestWeekFirst();
    void TestWeekSecond();
};

void TestInterval::TestMonthCurrent()
{
    Interval i(QDate(2022, 2, 5), Interval::Month, 0);

    QVERIFY(!i.inside(QDate(2022, 2, 4)));
    QVERIFY(i.inside(QDate(2022, 2, 5)));
    QVERIFY(i.inside(QDate(2022, 2, 28))); // last day of month
    QVERIFY(!i.inside(QDate(2022, 3, 1)));
}

void TestInterval::TestMonthFirst()
{
    Interval i(QDate(2022, 2, 5), Interval::Month, 1);

    QVERIFY(!i.inside(QDate(2022, 2, 28))); // last day of month
    QVERIFY(i.inside(QDate(2022, 3, 1)));
    QVERIFY(i.inside(QDate(2022, 3, 31))); // last day of month
    QVERIFY(!i.inside(QDate(2022, 4, 1)));
}

void TestInterval::TestMonthSecond()
{
    Interval i(QDate(2022, 2, 5), Interval::Month, 2);

    QVERIFY(!i.inside(QDate(2022, 3, 31))); // last day of prev month
    QVERIFY(i.inside(QDate(2022, 4, 1)));
    QVERIFY(i.inside(QDate(2022, 4, 30)));
    QVERIFY(!i.inside(QDate(2022, 5, 1)));
}

//week 3-9
void TestInterval::TestWeekCurrent()
{
    Interval i(QDate(2022, 1, 7), Interval::Week, 0); // Friday

    QVERIFY(!i.inside(QDate(2022, 1, 6)));
    QVERIFY(i.inside(QDate(2022, 1, 7)));
    QVERIFY(i.inside(QDate(2022, 1, 9)));
    QVERIFY(!i.inside(QDate(2022, 1, 10)));
}

// week 10-16
void TestInterval::TestWeekFirst()
{
    Interval i(QDate(2022, 1, 7), Interval::Week, 1); // Friday

    QVERIFY(!i.inside(QDate(2022, 1, 8)));
    QVERIFY(!i.inside(QDate(2022, 1, 9)));
    QVERIFY(i.inside(QDate(2022, 1, 10)));
    QVERIFY(i.inside(QDate(2022, 1, 16)));
    QVERIFY(!i.inside(QDate(2022, 1, 17)));
}

// week 17-23
void TestInterval::TestWeekSecond()
{
    Interval i(QDate(2022, 1, 7), Interval::Week, 2); // Friday

    QVERIFY(!i.inside(QDate(2022, 1, 16)));
    QVERIFY(i.inside(QDate(2022, 1, 17)));
    QVERIFY(i.inside(QDate(2022, 1, 23)));
    QVERIFY(!i.inside(QDate(2022, 1, 24)));
}

QTEST_MAIN(TestInterval)

#include "test_Interval.moc"