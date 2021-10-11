#include <QtTest/QtTest>
#include <jsonMappers/categoryMappers.h>

class TestCategoryJsonMapper : public QObject {
Q_OBJECT
private slots:

    void TestToJson();
    void TestFromJson();
    void TestParseCategories();
    void TestEmptyDiff();
    void TestNameDiff();
    void TestGroupIdDiff();
    void TestNameAndGroupDiff();
    void TestPatch();

private:
    const Category orig{"name1", "id1", "groupId1"};
    const CategoryRequest origReq{"name1", "groupId1"};
};

using namespace CategoryMappers;

void TestCategoryJsonMapper::TestEmptyDiff() {
    Category newc(orig);
    QVERIFY(diff(orig, newc).isEmpty());
}

void TestCategoryJsonMapper::TestNameDiff() {
    Category newc(orig);
    newc.name = "newname";
    QCOMPARE(diff(newc, orig), QJsonObject({{"name", "newname"}}));
}

void TestCategoryJsonMapper::TestGroupIdDiff() {
    Category newc(orig);
    newc.groupId = "newgroup";
    QCOMPARE(diff(newc, orig), QJsonObject({{"groupId", "newgroup"}}));
}

void TestCategoryJsonMapper::TestNameAndGroupDiff() {
    Category newc(orig);
    newc.name = "newname";
    newc.groupId = "newgroup";
    QCOMPARE(diff(newc, orig),
             QJsonObject({
                                 {"groupId", "newgroup"},
                                 {"name",    "newname"}
                         }));
}

void TestCategoryJsonMapper::TestToJson() {
    QCOMPARE(toJson(origReq),
             QJsonObject({
                                 {"name",    "name1"},
                                 {"groupId", "groupId1"}
                         }));
}

void TestCategoryJsonMapper::TestFromJson() {
    auto cat = categoryFromJson("id1", QJsonObject{
            {"name",    "name1"},
            {"groupId", "groupId1"}
    });
    QCOMPARE(cat.id, orig.id);
    QCOMPARE(cat.name, orig.name);
    QCOMPARE(cat.groupId, orig.groupId);
    QVERIFY(cat == orig);
}

void TestCategoryJsonMapper::TestParseCategories() {
    const auto cat1 = QJsonObject{
            {"name",    "name1"},
            {"groupId", "groupId1"}
    };
    const auto cat2 = QJsonObject{
            {"name",    "name2"},
            {"groupId", "groupId2"}
    };
    auto catsJson = QJsonObject({
        {"id1", cat1},
        {"id2", cat2}
    });
    Categories cats = parseCategories(catsJson);
    QCOMPARE(cats.size(), 2);
    QCOMPARE(cats.front().id, "id1");
}

void TestCategoryJsonMapper::TestPatch() {
    Category cat(orig);
    patch(cat, QJsonObject());
    QCOMPARE(cat.name, orig.name);
    QCOMPARE(cat.groupId, orig.groupId);
    patch(cat, {{"name", "new_name"}});
    QCOMPARE(cat.name, "new_name");
    QCOMPARE(cat.groupId, orig.groupId);
    patch(cat, {{"groupId", "new_groupId"}});
    QCOMPARE(cat.name, "new_name");
    QCOMPARE(cat.groupId, "new_groupId");
}


QTEST_MAIN(TestCategoryJsonMapper)

#include "test_categoryjsonmappers.moc"
