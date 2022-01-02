#include <QtTest/QtTest>
#include <jsonMappers/GroupMappers.h>

class TestGroupJsonMapper : public QObject {
    Q_OBJECT
private slots:

    void TestToJson();
    void TestFromJson();
    void TestEmptyDiff();
    void TestNameDiff();
    void TestPatch();

private:
    const Group orig { "id1", "name1" };
};

void TestGroupJsonMapper::TestToJson()
{
    GroupMapper m;
    QCOMPARE(m.toJson(orig),
        QJsonObject({
            { "name", "name1" },
        }));
}

void TestGroupJsonMapper::TestFromJson()
{
    GroupMapper m;
    auto g = m.fromJson("id1", QJsonObject {
                                   { "name", "name1" },
                               });
    QCOMPARE(g.id, orig.id);
    QCOMPARE(g.name, orig.name);
    QVERIFY(g == orig);
}

void TestGroupJsonMapper::TestEmptyDiff()
{
    Group newg(orig);
    GroupMapper m;
    QVERIFY(m.diff(orig, newg).isEmpty());
}

void TestGroupJsonMapper::TestNameDiff()
{
    Group newg(orig);
    GroupMapper m;
    newg.name = "new_name";
    QCOMPARE(m.diff(orig, newg), QJsonObject({ { "name", "new_name" } }));
}

void TestGroupJsonMapper::TestPatch()
{
    GroupMapper m;
    Group g(orig);
    m.patch(g, QJsonObject());
    QCOMPARE(g.name, orig.name);
    m.patch(g, { { "name", "new_name" } });
    QCOMPARE(g.name, "new_name");
}

QTEST_MAIN(TestGroupJsonMapper)
#include "test_GroupMapper.moc"
