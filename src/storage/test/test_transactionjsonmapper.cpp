#include <QtTest/QtTest>
#include <jsonMappers/transactionjsonmapper.h>
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

private:
    Transaction origT{"id", 100, QDateTime::currentDateTime(), "catId", "who", "comment"};
};

using namespace TransactionJsonMapper;

void TestTransactionJsonMapper::TestEmptyDiff() {
    Transaction newT(origT);
    QVERIFY(diff(origT, newT).isEmpty());
}

void TestTransactionJsonMapper::TestAmountDiff() {
    Transaction newT(origT);
    newT.amount = 200;
    auto patch =diff(newT, origT);
    QCOMPARE(patch,QJsonObject({{"amount", 200}}) );
}

void TestTransactionJsonMapper::TestWhenDiff() {
    Transaction newT(origT);
    newT.when = QDateTime::fromSecsSinceEpoch(100000);
    auto patch =diff(newT, origT);
    QCOMPARE(patch,QJsonObject({{"when", 100000}}) );
}

void TestTransactionJsonMapper::TestWhoDiff() {
    Transaction newT(origT);
    newT.who = "user";
    auto patch =diff(newT, origT);
    QCOMPARE(patch,QJsonObject({{"who", "user"}}) );
}

void TestTransactionJsonMapper::TestCommentDiff() {
    Transaction newT(origT);
    newT.comment = "text";
    auto patch =diff(newT, origT);
    QCOMPARE(patch,QJsonObject({{"comment", "text"}}) );
}

void TestTransactionJsonMapper::TestCategoryIdDiff() {
    Transaction newT(origT);
    newT.categoryId = "123";
    auto patch =diff(newT, origT);
    QCOMPARE(patch,QJsonObject({{"categoryId", "123"}}) );
}

void TestTransactionJsonMapper::TestMultipleFieldDiff() {
    Transaction newT(origT);
    newT.categoryId = "123";
    newT.amount = 50;
    newT.when = QDateTime::fromSecsSinceEpoch(111000);
    auto patch =diff(newT, origT);
    QCOMPARE(patch, QJsonObject({
                                        {"categoryId", "123"},
                                        {"amount", 50},
                                        {"when", 111000}
                                }));
}

QTEST_MAIN(TestTransactionJsonMapper)

#include "test_transactionjsonmapper.moc"
