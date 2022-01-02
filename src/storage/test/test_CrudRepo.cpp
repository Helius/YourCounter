#include <CrudRepoImpl.h>
#include <QtTest/QtTest>
#include <entities/Transaction.h>
#include <jsonMappers/CategoryMapper.h>
#include <jsonMappers/GroupMappers.h>
#include <jsonMappers/TransactionMapper.h>

namespace {

QLatin1String Path("/path");
}
struct Entity {
    Entity() = delete;
    Entity(const QString& id_, const QString& value_)
        : id(id_)
        , value(value_) {};
    QString id;
    QString value;
    bool operator==(const Entity& other) const
    {
        return id == other.id && value == other.value;
    }
    operator bool() const
    {
        return !id.isEmpty() && !value.isEmpty();
    }
};

class EntityMapper : public IJsonMapper<Entity> {
    Entity fromJson(const QString& id, const QJsonObject& json) override
    {
        return Entity(id, json.value("value").toString());
    }
    QJsonObject toJson(const Entity& e) override
    {
        return { { "id", e.id }, { "value", e.value } };
    }

    void patch(Entity& t, const QJsonObject& json) override
    {
        t.value = json.contains("value") ? json.value("value").toString() : t.value;
    }

    QJsonObject diff(const Entity& from, const Entity& to) override
    {
        QJsonObject result;

        if (from.value != to.value) {
            result.insert("value", to.value);
        }
        return result;
    }
};

class MockApi : public IFirebaseRtDbApi {
public:
    JsonFuture getObject(const QString& path) override
    {
        if (path == Path) {
            return QtFuture::makeReadyFuture(response);
        }
        return QtFuture::makeReadyFuture(QJsonObject());
    };

    JsonFuture addObject(const QString& root, const QJsonObject& object) override
    {
        Q_ASSERT(!object.isEmpty());
        Q_ASSERT(object.contains("value"));
        if (root == Path) {
            return QtFuture::makeReadyFuture(response);
        }
        return QtFuture::makeReadyFuture(QJsonObject());
    };

    JsonFuture updateObject(const QString& root, const QString& id, const QJsonObject& patch) override
    {
        Q_ASSERT(!patch.isEmpty());
        Q_ASSERT(!id.isEmpty());
        if (root == Path) {
            return QtFuture::makeReadyFuture(response);
        }
        return QtFuture::makeReadyFuture(QJsonObject());
    };

    JsonFuture deleteObject(const QString& root, const QString& id) override
    {
        Q_ASSERT(!id.isEmpty());
        if (root == Path) {
            return QtFuture::makeReadyFuture(response);
        }
        return QtFuture::makeReadyFuture(QJsonObject());
    }

public:
    QJsonObject response;
};

class TestTransactionRepo : public QObject {
    Q_OBJECT
public:
    TestTransactionRepo()
    {
        mapper = std::make_shared<EntityMapper>();
    }
private slots:
    void testCRUD();

private:
    std::shared_ptr<EntityMapper> mapper;
};

void TestTransactionRepo::testCRUD()
{

    // test add

    auto api = std::make_shared<MockApi>();
    std::shared_ptr<ICRUDRepo<Entity>> repo = std::make_shared<CrudRepository<Entity>>(
        Path,
        api,
        mapper);

    QSignalSpy dataChangedSpy(repo.get(), &IRepoObserver::dataChanged);
    QSignalSpy onErrorSpy(repo.get(), &IRepoObserver::onError);

    api->response = {
        { "name", "id0" }
    };
    QCOMPARE(repo->data().size(), 0);
    repo->create({ "1", "first" });
    QCOMPARE(repo->data().size(), 1);
    QCOMPARE(onErrorSpy.count(), 0);
    QCOMPARE(dataChangedSpy.count(), 1);
    QCOMPARE(dataChangedSpy.at(0).at(0).toInt(), IRepoObserver::Inserted);
    QCOMPARE(dataChangedSpy.at(0).at(1).toInt(), 0);
    QCOMPARE(dataChangedSpy.at(0).at(2).toInt(), 1);
    QCOMPARE(Entity("id0", "first"), repo->data().front());
    dataChangedSpy.clear();

    api->response = {
        { "name", "id1" }
    };
    repo->create({ "1", "second" });
    QCOMPARE(repo->data().size(), 2);
    QCOMPARE(onErrorSpy.count(), 0);
    QCOMPARE(dataChangedSpy.count(), 1);
    QCOMPARE(dataChangedSpy.at(0).at(0).toInt(), IRepoObserver::Inserted);
    QCOMPARE(dataChangedSpy.at(0).at(1).toInt(), 1);
    QCOMPARE(dataChangedSpy.at(0).at(2).toInt(), 1);

    QCOMPARE(Entity("id0", "first"), repo->data().front());
    QCOMPARE(Entity("id1", "second"), repo->data().back());

    // test update
    onErrorSpy.clear();
    dataChangedSpy.clear();
    api->response = {
        QJsonObject({ { "value", "ttt" } })
    };
    auto e = repo->data()[1];
    QCOMPARE(e.id, "id1");
    e.value = "ttt";
    repo->update(e);
    QCOMPARE(onErrorSpy.count(), 0);
    QCOMPARE(dataChangedSpy.count(), 1);
    QCOMPARE(dataChangedSpy.at(0).at(0).toInt(), IRepoObserver::Changed);
    QCOMPARE(dataChangedSpy.at(0).at(1).toInt(), 1);
    QCOMPARE(dataChangedSpy.at(0).at(2).toInt(), 1);
    QCOMPARE(repo->data().size(), 2);
    QCOMPARE(Entity("id1", "ttt"), repo->data().back());

    // test delete
    api->response = {};
    dataChangedSpy.clear();
    repo->remove(repo->data()[0]);
    QCOMPARE(dataChangedSpy.count(), 1);
    QCOMPARE(dataChangedSpy.at(0).at(0).toInt(), IRepoObserver::Removed);
    QCOMPARE(dataChangedSpy.at(0).at(1).toInt(), 0);
    QCOMPARE(dataChangedSpy.at(0).at(2).toInt(), 1);
    QCOMPARE(repo->data().size(), 1);
    QCOMPARE(Entity("id1", "ttt"), repo->data().front());

    dataChangedSpy.clear();
    repo->remove(repo->data()[0]);
    QCOMPARE(dataChangedSpy.count(), 1);
    QCOMPARE(dataChangedSpy.at(0).at(0).toInt(), IRepoObserver::Removed);
    QCOMPARE(dataChangedSpy.at(0).at(1).toInt(), 0);
    QCOMPARE(dataChangedSpy.at(0).at(2).toInt(), 1);
    QCOMPARE(repo->data().size(), 0);
}

QTEST_MAIN(TestTransactionRepo)
#include "test_CrudRepo.moc"
