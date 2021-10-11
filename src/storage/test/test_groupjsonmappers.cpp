#include <QtTest/QtTest>
#include <jsonMappers/groupMappers.h>

class TestGroupJsonMapper : public QObject {
Q_OBJECT
private slots:

    void TestToJson();
    void TestFromJson();
    void TestParseGroups();
    void TestEmptyDiff();
    void TestNameDiff();
    void TestPatch();

private:
    const Group orig{"id1", "name1"};
    const GroupRequest origReq{"name2"};
};

using namespace GroupMappers;

void TestGroupJsonMapper::TestToJson() {
    QCOMPARE(toJson(origReq),
             QJsonObject({
                                 {"name",    "name2"},
                         }));
}

void TestGroupJsonMapper::TestFromJson() {

    auto g = groupFromJson("id1", QJsonObject{
            {"name",    "name1"},
    });
    QCOMPARE(g.id, orig.id);
    QCOMPARE(g.name, orig.name);
    QVERIFY(g == orig);
}

void TestGroupJsonMapper::TestParseGroups() {
    const auto g1 = QJsonObject{
            {"name",    "name1"}
    };
    const auto g2 = QJsonObject{
            {"name",    "name2"}
    };
    auto catsJson = QJsonObject({
                                        {"id1", g1},
                                        {"id2", g2}
                                });
    Groups gs = parseGroups(catsJson);
    QCOMPARE(gs.size(), 2);
    QCOMPARE(gs.front().id, "id1");
}

void TestGroupJsonMapper::TestEmptyDiff() {
    Group newg(orig);
    QVERIFY(diff(orig, newg).isEmpty());
}

void TestGroupJsonMapper::TestNameDiff() {
    Group newg(orig);
    newg.name = "new_name";
    QCOMPARE(diff(newg, orig), QJsonObject({{"name", "new_name"}}));
}

void TestGroupJsonMapper::TestPatch() {
    Group g(orig);
    patch(g, QJsonObject());
    QCOMPARE(g.name, orig.name);
    patch(g, {{"name", "new_name"}});
    QCOMPARE(g.name, "new_name");
}


QTEST_MAIN(TestGroupJsonMapper)
#include "test_groupjsonmappers.moc"
