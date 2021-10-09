#include <QtTest/QtTest>
#include <transactionrepo.h>
#include <transactionjsonmapper.h>
#include <entities/transaction.h>

namespace {
    TransactionRequest t1{100, QDateTime::currentDateTime(), "catId1", "who1", "comment1"};
    TransactionRequest t2{-100, QDateTime::currentDateTime(), "catId2", "who2", "comment2"};
}

class MockApi : public IFirebaseRtDbApi {

    JsonFuture getObject(const QString & path) override
    {
        if(path == "/transactions")
        {
            return QtFuture::makeReadyFuture(
                    QJsonObject{
                        {"id1", TransactionJsonMapper::toJson(t1)},
                        {"id2", TransactionJsonMapper::toJson(t2)}}
                    );
        }
        return QtFuture::makeReadyFuture(QJsonObject());
    };

    JsonFuture addObject(const QString & root, const QJsonObject & object) override
    {
        Q_UNUSED(root);
        Q_UNUSED(object);
        return QtFuture::makeReadyFuture(QJsonObject());
    };

    JsonFuture updateObjectByID(const QString &root, const QString &id, const QJsonObject &patch) override
    {
        Q_UNUSED(root);
        Q_UNUSED(id);
        Q_UNUSED(patch);
        return QtFuture::makeReadyFuture(QJsonObject());
    };
};

class TestTransactionRepo: public QObject
{
    Q_OBJECT
private slots:
    void testAddTransaction();
};

void TestTransactionRepo::testAddTransaction() {
    auto repo = TransactionRepo::getInstance(std::make_unique<MockApi>());
    QSignalSpy changeSpy(repo.get(), &TransactionRepo::transactionsChanged);
    repo->getCategories();
    changeSpy.wait(100);
    QCOMPARE(changeSpy.count(), 1);
    const auto & transactions = repo->getTransactions();
    QCOMPARE(transactions.size(), 2);
}

QTEST_MAIN(TestTransactionRepo)
#include "test_transactionrepo.moc"