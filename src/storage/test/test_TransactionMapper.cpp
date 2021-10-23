#include <QtTest/QtTest>
#include <jsonMappers/TransactionMapper.h>
#include <entities/transaction.h>

class TestTransactionJsonMapper: public QObject
{
Q_OBJECT
private slots:

    void TestEmptyDiff();
    void TestAmountDiff();
    void TestWhenDiff();
    void TestWhoDiff();
    void TestCommentDiff();
    void TestCategoryIdDiff();
    void TestMultipleFieldDiff();
    void TestFromJson();
    void TestToJson();

private:
    Transaction origT{"id",
                      100,
                      QDateTime::currentDateTime(),
                      "catId",
                      "who",
                      "comment"};
    TransactionMapper m;
};


void TestTransactionJsonMapper::TestEmptyDiff() {
    Transaction newT(origT);
    QVERIFY(m.diff(origT, newT).isEmpty());
}

void TestTransactionJsonMapper::TestAmountDiff() {
    Transaction newT(origT);
    newT.amount = 200;
    auto patch = m.diff(origT, newT);
    QCOMPARE(patch,QJsonObject({{"amount", 200}}) );
}

void TestTransactionJsonMapper::TestWhenDiff() {
    Transaction newT(origT);
    newT.when = QDateTime::fromMSecsSinceEpoch(100000);
    auto patch = m.diff(origT, newT);
    QCOMPARE(patch,QJsonObject({{"when", 100000}}) );
}

void TestTransactionJsonMapper::TestWhoDiff() {
    Transaction newT(origT);
    newT.who = "user";
    auto patch = m.diff(origT, newT);
    QCOMPARE(patch,QJsonObject({{"who", "user"}}) );
}

void TestTransactionJsonMapper::TestCommentDiff() {
    Transaction newT(origT);
    newT.comment = "text";
    auto patch = m.diff(origT, newT);
    QCOMPARE(patch,QJsonObject({{"comment", "text"}}) );
}

void TestTransactionJsonMapper::TestCategoryIdDiff() {
    Transaction newT(origT);
    newT.categoryId = "123";
    auto patch = m.diff(origT, newT);
    QCOMPARE(patch,QJsonObject({{"categoryId", "123"}}) );
}

void TestTransactionJsonMapper::TestMultipleFieldDiff() {
    Transaction newT(origT);
    newT.categoryId = "123";
    newT.amount = 50;
    newT.when = QDateTime::fromMSecsSinceEpoch(1110000);
    auto patch = m.diff(origT, newT);
    QCOMPARE(patch, QJsonObject({
                                        {"categoryId", "123"},
                                        {"amount", 50},
                                        {"when", 1110000}
                                }));
}

void TestTransactionJsonMapper::TestFromJson() {
    QDateTime dt = QDateTime(QDate(2021, 1, 1), QTime(1,1,1));
    long long time = dt.toMSecsSinceEpoch();
    QJsonObject json {
            {"categoryId", "catId1"},
            {"amount", -10.1},
            {"when", time},
            {"comment", "comment1"},
            {"who", "me"}
    };
    Transaction t = m.fromJson("id1", json);
    QCOMPARE(t.categoryId, "catId1");
    QVERIFY(qFuzzyCompare(-10.1f, t.amount));
    QCOMPARE(t.when, dt);
    QCOMPARE(t.comment, "comment1");
    QCOMPARE(t.who, "me");
}

void TestTransactionJsonMapper::TestToJson() {
    auto t = m.fromJson(origT.id, m.toJson(origT));
    QCOMPARE(t.categoryId, origT.categoryId);
    QVERIFY(qFuzzyCompare(t.amount, t.amount));
    QCOMPARE(t.when, origT.when);
    QCOMPARE(t.comment, origT.comment);
    QCOMPARE(t.who, origT.who);

    QCOMPARE(t, origT);
    QVERIFY(m.diff(origT, t).isEmpty());
}

QTEST_MAIN(TestTransactionJsonMapper)

#include "test_TransactionMapper.moc"
