#include <QtTest>
#include "../src/domain/entities/interval.h"
#include "AutoTest.h"

class test_Interval : public QObject
{
    Q_OBJECT

public:

private slots:
    void test_contains();
    void test_isEmpty();
};

void test_Interval::test_contains()
{
    auto start = QDateTime(QDate(2021, 1, 1), QTime(0, 0, 0));
    Interval i(start, 1);
    QVERIFY(i.contains(start));
    QVERIFY(!i.contains(start.addDays(1)));
    QVERIFY(i.contains(start.addSecs(1000)));
}

void test_Interval::test_isEmpty()
{
    Interval notEmpty(QDateTime::currentDateTime(), 1);
    QVERIFY(!notEmpty.isEmpty());
    Interval empt({});
    QVERIFY(empt.isEmpty());
}

DECLARE_TEST(test_Interval)
#include "test_Interval.moc"
