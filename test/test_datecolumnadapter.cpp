#include <QtTest>
#include "../src/app/repos/datecolumnadapter.h"
#include "AutoTest.h"

class test_DateColumnAdapter : public QObject
{
    Q_OBJECT

public:
    test_DateColumnAdapter();
    ~test_DateColumnAdapter();

private slots:
    void test_init_state();
    void test_set_scale();
    void test_check_column_count();
    void test_isSame_week();
    void test_isSame_month();
private:
    std::unique_ptr<DateColumnAdapter> adapter;
};


test_DateColumnAdapter::test_DateColumnAdapter()
{
    adapter = std::make_unique<DateColumnAdapter>();
}

test_DateColumnAdapter::~test_DateColumnAdapter()
{

}

void test_DateColumnAdapter::test_init_state()
{
    QTEST_ASSERT(adapter);
}

void test_DateColumnAdapter::test_set_scale()
{
    QTEST_ASSERT(adapter);
    adapter->setScale(DateColumnAdapter::TimeScale::Day);

    QSignalSpy spy(adapter.get(), &DateColumnAdapter::scaleChanged);

    QCOMPARE(adapter->scale(), DateColumnAdapter::TimeScale::Day);
    QCOMPARE(spy.count(), 0);

    adapter->setScale(DateColumnAdapter::TimeScale::Month);
    QCOMPARE(adapter->scale(), DateColumnAdapter::TimeScale::Month);
    QCOMPARE(spy.count(), 1);
    spy.clear();

    adapter->setScale(DateColumnAdapter::TimeScale::Week);
    QCOMPARE(adapter->scale(), DateColumnAdapter::TimeScale::Week);
    QCOMPARE(spy.count(), 1);
    spy.clear();

    adapter->setScale(DateColumnAdapter::TimeScale::Day);
    QCOMPARE(adapter->scale(), DateColumnAdapter::TimeScale::Day);
    QCOMPARE(spy.count(), 1);
}

void test_DateColumnAdapter::test_check_column_count()
{
    QTEST_ASSERT(adapter);
    adapter->setScale(DateColumnAdapter::TimeScale::Month);
    QCOMPARE(adapter->columnCount(), 12);
    adapter->setScale(DateColumnAdapter::TimeScale::Week);
    QCOMPARE(adapter->columnCount(), 12*4);
    adapter->setScale(DateColumnAdapter::TimeScale::Day);
    QCOMPARE(adapter->columnCount(), 365);
}

void test_DateColumnAdapter::test_isSame_week()
{
    QTEST_ASSERT(adapter);
    adapter->setScale(DateColumnAdapter::TimeScale::Week);
    QVERIFY(adapter->isSame(0, QDateTime(QDate(2021,1,4), QTime())));
    QVERIFY(adapter->isSame(0, QDateTime(QDate(2021,1,9), QTime())));
    QVERIFY(adapter->isSame(1, QDateTime(QDate(2021,1,11), QTime())));
    QVERIFY(adapter->isSame(37, QDateTime(QDate(2021,9,21), QTime())));
}

void test_DateColumnAdapter::test_isSame_month()
{
    QTEST_ASSERT(adapter);
    adapter->setScale(DateColumnAdapter::TimeScale::Month);
    QVERIFY(adapter->isSame(0, QDateTime(QDate(2021,1,4), QTime())));
    QVERIFY(adapter->isSame(0, QDateTime(QDate(2021,1,31), QTime())));
    QVERIFY(adapter->isSame(1, QDateTime(QDate(2021,2,1), QTime())));

}

DECLARE_TEST(test_DateColumnAdapter)


#include "test_datecolumnadapter.moc"
