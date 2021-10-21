#include <QtTest/QtTest>
#include <transactionrepo.h>
#include <jsonMappers/transactionjsonmapper.h>
#include <jsonMappers/categoryMappers.h>
#include <jsonMappers/groupMappers.h>
#include <entities/transaction.h>

namespace {
    TransactionRequest t1{100, QDateTime::currentDateTime(), "catId1", "who1", "comment1"};
    TransactionRequest t2{-100, QDateTime::currentDateTime(), "catId2", "who2", "comment2"};
    TransactionRequest t3{-200, QDateTime::currentDateTime(), "catId3", "who3", "comment3"};

    TransactionRequest p1{-50, QDateTime::currentDateTime(), "catId3", "who3", "comment3"};

    CategoryRequest c1{"categoryName", QString()};
    GroupRequest g1{"groupName"};
}

class MockApi : public IFirebaseRtDbApi {

    JsonFuture getObject(const QString & path) override
    {
        if (path == "/transactions")
        {
            return QtFuture::makeReadyFuture(
                    QJsonObject {
                        {"tid1", TransactionJsonMapper::toJson(t1)},
                        {"tid2", TransactionJsonMapper::toJson(t2)}}
                    );
        }
        else if (path == "/categories")
        {
            return QtFuture::makeReadyFuture(
                    QJsonObject{
                            {"cid2", CategoryMappers::toJson(c1)}
                    }
            );
        }
        else if (path == "/groups")
        {
            return QtFuture::makeReadyFuture(
                    QJsonObject{
                            {"gid1", GroupMappers::toJson(g1)}
                    }
            );
        }
        else if (path == "/predictions")
        {
            return QtFuture::makeReadyFuture(
                    QJsonObject{
                            {"pid3", TransactionJsonMapper::toJson(p1)}
                    }
            );
        }
        return QtFuture::makeReadyFuture(QJsonObject());
    };

    JsonFuture addObject(const QString & root, const QJsonObject & object) override
    {
        if (root == "/transactions") {
            return QtFuture::makeReadyFuture(
                    QJsonObject(
                            { {"tid3", object }}
                            ));
        }


        return QtFuture::makeReadyFuture(QJsonObject());
    };

    JsonFuture updateObjectByID(const QString &root, const QString &id, const QJsonObject &patch) override
    {
        if (root == "/transactions") {
            return QtFuture::makeReadyFuture(
                    QJsonObject(
                            { {id, patch}}
                    ));
        }
        return QtFuture::makeReadyFuture(QJsonObject());
    };
};

class TestTransactionRepo: public QObject
{
    Q_OBJECT
private slots:
    void testInitLoad();
    void testAddTransactions();
    void testUpdateObject();
    void testRepo();
};

void TestTransactionRepo::testInitLoad() {
    auto repo = TransactionRepo::getInstance(std::make_unique<MockApi>());
    QSignalSpy transactionsSpy(repo.get(), &TransactionRepo::transactionsChanged);
    QSignalSpy categoriesSpy(repo.get(), &TransactionRepo::categoriesChanged);
    QSignalSpy groupsSpy(repo.get(), &TransactionRepo::groupsChanged);
    QSignalSpy predictionsSpy(repo.get(), &TransactionRepo::predictionsChanged);

    repo->init();

    transactionsSpy.wait(100);
    QCOMPARE(transactionsSpy.count(), 1);
    const auto & transactions = repo->getTransactions();
    QCOMPARE(transactions.size(), 2);

    categoriesSpy.wait(100);
    QCOMPARE(categoriesSpy.count(), 1);
    const auto & categories = repo->getCategories();
    QCOMPARE(categories.size(), 1);

    groupsSpy.wait(100);
    QCOMPARE(groupsSpy.count(), 1);
    const auto & groups = repo->getGroups();
    QCOMPARE(groups.size(), 1);

    predictionsSpy.wait(100);
    QCOMPARE(predictionsSpy.count(), 1);
    const auto & predictions = repo->getGroups();
    QCOMPARE(predictions.size(), 1);
}

void TestTransactionRepo::testAddTransactions() {
    auto repo = TransactionRepo::getInstance(std::make_unique<MockApi>());
    repo->init();
    QSignalSpy transactionsSpy(repo.get(), &TransactionRepo::transactionsChanged);

    transactionsSpy.wait(100);
    QCOMPARE(transactionsSpy.count(), 1);
    const auto & transactions = repo->getTransactions();
    QCOMPARE(transactions.size(), 2);
    transactionsSpy.clear();

    repo->addTransaction(t3);
    transactionsSpy.wait(100);
    QCOMPARE(transactionsSpy.count(), 1);
    QCOMPARE(transactions.size(), 3);
    QCOMPARE(transactions[0].id, "tid1");
    QCOMPARE(transactions[1].id, "tid2");
    QCOMPARE(transactions[2].id, "tid3");
}

void TestTransactionRepo::testUpdateObject() {

    auto repo = TransactionRepo::getInstance(std::make_unique<MockApi>());
    repo->init();
    QSignalSpy transactionsSpy(repo.get(), &TransactionRepo::transactionsChanged);

    transactionsSpy.wait(100);
    QCOMPARE(transactionsSpy.count(), 1);
//    const auto & transactions = repo->getTransactions();
//    QCOMPARE(transactions.size(), 2);
//    transactionsSpy.clear();
//
//    Transaction newT (transactions[1]);
//    QCOMPARE(newT, transactions[1]);
//    QCOMPARE(newT.id, "tid2");
//    newT.amount = -15;
//    newT.categoryId = "newCat";
//    repo->updateTransaction(newT);
//    transactionsSpy.wait(100);
//    QCOMPARE(transactionsSpy.count(), 1);
//    QCOMPARE(transactions.size(), 2);
//
//    QCOMPARE(transactions[0].id, "tid1");
//
//    QCOMPARE(transactions[1].id, "tid2");
//    QCOMPARE(transactions[1].amount, -15);
//    QCOMPARE(transactions[1].categoryId, "newCat");

}

struct Entity {
    Entity() = delete;
    Entity(int id, int value) : id(id), value(value) {};
    int id;
    int value;
    bool operator==(const Entity & other) const {
        return id == other.id && value == other.value;
    }
};

class EntityMapper : public IJsonMapper<Entity> {
    Entity fromJson(const QJsonObject & json) override
    {
        return Entity(json.value("id").toInt(), json.value("value").toInt());
    }
    QJsonObject toJson(const Entity & e) override
    {
        return {{"id", e.id}, {"value", e.value}};
    }
    QJsonObject patch(const Entity & , const Entity & to) override
    {
        return {{"value", to.value}};
    }
};

void TestTransactionRepo::testRepo()
{
    std::unique_ptr<ICRUDMethods<Entity>> repo = std::make_unique<CrudRepository<Entity>>("/repo", std::make_unique<EntityMapper>());
    QSignalSpy transactionsSpy(repo.get(), &IRepoObserver::dataChanged);
    QCOMPARE(repo->data().size(), 0);
    repo->create({1, 11});
    QCOMPARE(repo->data().size(), 1);
    QCOMPARE(transactionsSpy.count(), 1);
    QCOMPARE(transactionsSpy.takeFirst().at(0).toInt(), 0);
    transactionsSpy.clear();

    repo->create({2, 22});
    QCOMPARE(repo->data().size(), 2);
    QCOMPARE(transactionsSpy.count(), 1);
    QCOMPARE(transactionsSpy.takeFirst().at(0).toInt(), 1);

    QCOMPARE(Entity(1, 11), repo->data().front());
    QCOMPARE(Entity(2, 22), repo->data().back());

}

QTEST_MAIN(TestTransactionRepo)
#include "test_transactionrepo.moc"