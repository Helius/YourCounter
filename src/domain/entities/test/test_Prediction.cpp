#include "../Prediction.h"
#include <QtTest/QtTest>

class TestPrediction : public QObject {
    Q_OBJECT

private slots:
    void TestGetSinglePredictions();
    void TestGetDatePredictionWithMontMask();
    void TestGetMonthPredictionWithoutDay();
};

void TestPrediction::TestGetSinglePredictions()
{

    PredictionTemplate t = PredictionTemplate::createFromValue(
        "id", "catId",
        QDate(2020, 1, 10),
        0, // month mask
        100,
        false, QString());
    {
        auto p = t.getPredictionForDay(QDate(2020, 1, 9));
        QVERIFY(!p);
    }
    {
        auto p = t.getPredictionForDay(QDate(2020, 1, 10));
        QVERIFY(p);
    }
    {
        auto p = t.getPredictionForDay(QDate(2020, 1, 11));
        QVERIFY(!p);
    }
    {
        auto p = t.getPredictionForDay(QDate(2020, 2, 11));
        QVERIFY(!p);
    }
}

void TestPrediction::TestGetDatePredictionWithMontMask()
{
    PredictionTemplate t = PredictionTemplate::createFromValue(
        "id", "catId",
        QDate(2020, 1, 10),
        5, // month mask 101
        100,
        false, QString());
    {
        auto p = t.getPredictionForDay(QDate(2020, 1, 9));
        QVERIFY(!p);
    }
    {
        auto p = t.getPredictionForDay(QDate(2020, 1, 10));
        QVERIFY(p);
    }
    {
        auto p = t.getPredictionForDay(QDate(2020, 1, 11));
        QVERIFY(!p);
    }
    {
        auto p = t.getPredictionForDay(QDate(2020, 2, 10));
        QVERIFY(!p);
    }
    {
        auto p = t.getPredictionForDay(QDate(2020, 3, 10));
        QVERIFY(p);
    }
    {
        auto p = t.getPredictionForDay(QDate(2020, 4, 10));
        QVERIFY(!p);
    }
    {
        auto p = t.getPredictionForDay(QDate(2021, 3, 10));
        QVERIFY(p);
    }
}

void TestPrediction::TestGetMonthPredictionWithoutDay()
{
    PredictionTemplate t = PredictionTemplate::createFromValue(
        "id", "catId",
        QDate(),
        5, // month mask 101
        100,
        false, QString());

    {
        auto p = t.getPredictionForDay(QDate(2020, 1, 1));
        QVERIFY(!p);
    }
    {
        auto p = t.getPredictionForDay(QDate(2020, 1, 31));
        QVERIFY(p);
    }
    {
        auto p = t.getPredictionForDay(QDate(2020, 2, 28));
        QVERIFY(!p);
    }
    {
        auto p = t.getPredictionForDay(QDate(2021, 3, 31));
        QVERIFY(p);
    }
}

QTEST_MAIN(TestPrediction)

#include "test_Prediction.moc"