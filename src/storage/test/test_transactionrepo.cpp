#include <QtTest/QtTest>
#include <transactionrepo.h>
#include <jsonMappers/TransactionMapper.h>
#include <jsonMappers/CategoryMapper.h>
#include <jsonMappers/GroupMappers.h>
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
                    QJsonObject{
//                        {"tid1", TransactionJsonMapper::toJson(t1)},
//                        {"tid2", TransactionJsonMapper::toJson(t2)}}
                    });
        }
        else if (path == "/categories")
        {
            return QtFuture::makeReadyFuture(
                    QJsonObject{
//                            {"cid2", CategoryMappers::toJson(c1)}
                    }
            );
        }
        else if (path == "/groups")
        {
//            return QtFuture::makeReadyFuture(
//                    QJsonObject{
//                            {"gid1", GroupMapper::toJson(g1)}
//                    }
//            );
        }
        else if (path == "/predictions")
        {
            return QtFuture::makeReadyFuture(
                    QJsonObject{
//                            {"pid3", TransactionJsonMapper::toJson(p1)}
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
    void testRepo();
};

struct Entity {
    Entity() = delete;
    Entity(const QString & id, int value) : id(id), value(value) {};
    QString id;
    int value;
    bool operator==(const Entity & other) const {
        return id == other.id && value == other.value;
    }
};

class EntityMapper : public IJsonMapper<Entity> {
    Entity fromJson(const QString & id, const QJsonObject & json) override
    {
        return Entity(id, json.value("value").toInt());
    }
    QJsonObject toJson(const Entity & e) override
    {
        return {{"id", e.id}, {"value", e.value}};
    }

    void patch(Entity &t, const QJsonObject &json) override
    {
        t.value = json.contains("value") ? json.value("value").toInt() : t.value;
    }

    QJsonObject diff(const Entity &from, const Entity &to) override
    {
        QJsonObject result;

        if (from.value != to.value)
        {
            result.insert("value", to.value);
        }
        return result;
    }
};

void TestTransactionRepo::testRepo()
{
    std::unique_ptr<ICRUDMethods<Entity>> repo = std::make_unique<CrudRepository<Entity>>("/repo", std::make_unique<EntityMapper>());
    QSignalSpy transactionsSpy(repo.get(), &IRepoObserver::dataChanged);
    QCOMPARE(repo->data().size(), 0);
    repo->create({"1", 11});
    QCOMPARE(repo->data().size(), 1);
    QCOMPARE(transactionsSpy.count(), 1);
    QCOMPARE(transactionsSpy.takeFirst().at(0).toInt(), 0);
    transactionsSpy.clear();

    repo->create({"2", 22});
    QCOMPARE(repo->data().size(), 2);
    QCOMPARE(transactionsSpy.count(), 1);
    QCOMPARE(transactionsSpy.takeFirst().at(0).toInt(), 1);

    QCOMPARE(Entity("1", 11), repo->data().front());
    QCOMPARE(Entity("2", 22), repo->data().back());

}

QTEST_MAIN(TestTransactionRepo)
#include "test_transactionrepo.moc"
