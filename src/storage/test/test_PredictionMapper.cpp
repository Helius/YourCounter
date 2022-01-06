#include <QtTest/QtTest>
#include <entities/Prediction.h>
#include <jsonMappers/PredictionMapper.h>

class TestPredictionJsonMapper : public QObject {

    Q_OBJECT

private slots:
    void TestEmptyDiff();
    void TestCategoryIdDiff();
    void TestStartDiff();
    void TestMonthMaskDiff();
    void TestCumulativeDiff();
    void TestAmountDiff();
    void TestCommentDiff();
    void TestMultipleFieldDiff();
    void TestFromJson();
    void TestToJson();

private:
    Prediction orig = Prediction::createFromValue(
        "id",
        "catId",
        QDate::currentDate(),
        5, // monthMask
        100, // amount
        false, // cumulative
        "comment");
    PredictionMapper m;
};

void TestPredictionJsonMapper::TestEmptyDiff()
{
    Prediction p(orig);
    QVERIFY(m.diff(orig, p).isEmpty());
}

void TestPredictionJsonMapper::TestCategoryIdDiff()
{
    Prediction p(orig);
    p.categoryId = "123";
    auto patch = m.diff(orig, p);
    QCOMPARE(patch, QJsonObject({ { "categoryId", "123" } }));
}

void TestPredictionJsonMapper::TestAmountDiff()
{
    Prediction p(orig);
    p.amount = 200;
    auto patch = m.diff(orig, p);
    QCOMPARE(patch, QJsonObject({ { "amount", 200 } }));
}

void TestPredictionJsonMapper::TestStartDiff()
{
    Prediction p(orig);
    p.start.setDate(2020, 2, 3);
    auto patch = m.diff(orig, p);
    QCOMPARE(patch, QJsonObject({ { "start", "20200203" } }));
}

void TestPredictionJsonMapper::TestMonthMaskDiff()
{
    Prediction p(orig);
    p.monthMask = 7;
    auto patch = m.diff(orig, p);
    QCOMPARE(patch, QJsonObject({ { "monthMask", 7 } }));
}

void TestPredictionJsonMapper::TestCumulativeDiff()
{
    Prediction p(orig);
    p.cumulative = true;
    auto patch = m.diff(orig, p);
    QCOMPARE(patch, QJsonObject({ { "cumulative", true } }));
}

void TestPredictionJsonMapper::TestCommentDiff()
{
    Prediction p(orig);
    p.comment = "text";
    auto patch = m.diff(orig, p);
    QCOMPARE(patch, QJsonObject({ { "comment", "text" } }));
}

void TestPredictionJsonMapper::TestMultipleFieldDiff()
{
    Prediction p(orig);
    p.categoryId = "123";
    p.amount = 50;
    p.start.setDate(2020, 4, 5);
    auto patch = m.diff(orig, p);
    QCOMPARE(patch, QJsonObject({ { "categoryId", "123" }, { "amount", 50 }, { "start", "20200405" } }));
}

void TestPredictionJsonMapper::TestFromJson()
{
    QDate date = QDate(2021, 1, 2);
    QJsonObject json {
        { "categoryId", "catId1" },
        { "start", "20210102" },
        { "monthMask", 9 },
        { "amount", -11 },
        { "comment", "comment1" },
        { "cumulative", true }
    };
    Prediction p = m.fromJson("id1", json);
    QCOMPARE(p.categoryId, "catId1");
    QCOMPARE(p.amount, -11);
    QCOMPARE(p.start, date);
    QCOMPARE(p.monthMask, 9);
    QCOMPARE(p.comment, "comment1");
    QCOMPARE(p.cumulative, true);
}

void TestPredictionJsonMapper::TestToJson()
{
    auto p = m.fromJson(orig.id, m.toJson(orig));
    QCOMPARE(p.id, orig.id);
    QCOMPARE(p.categoryId, orig.categoryId);
    QCOMPARE(p.start, orig.start);
    QCOMPARE(p.monthMask, orig.monthMask);
    QCOMPARE(p.amount, orig.amount);
    QCOMPARE(p.comment, orig.comment);
    QCOMPARE(p.cumulative, orig.cumulative);
}

QTEST_MAIN(TestPredictionJsonMapper)

#include "test_PredictionMapper.moc"