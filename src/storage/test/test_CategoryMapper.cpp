#include <QtTest/QtTest>
#include <jsonMappers/CategoryMapper.h>

class TestCategoryJsonMapper : public QObject {
Q_OBJECT
private slots:

    void TestToJson();
    void TestFromJson();
    void TestEmptyDiff();
    void TestNameDiff();
    void TestGroupIdDiff();
    void TestNameAndGroupDiff();
    void TestPatch();

private:
    const Category orig{"name1", "id1", "groupId1"};
    CategoryMapper m;
};

void TestCategoryJsonMapper::TestEmptyDiff() {
    Category newc(orig);
    QVERIFY(m.diff(orig, newc).isEmpty());
}

void TestCategoryJsonMapper::TestNameDiff() {
    Category newc(orig);
    newc.name = "newname";
    QCOMPARE(m.diff(orig, newc), QJsonObject({{"name", "newname"}}));
}

void TestCategoryJsonMapper::TestGroupIdDiff() {
    Category newc(orig);
    newc.groupId = "newgroup";
    QCOMPARE(m.diff(orig, newc), QJsonObject({{"groupId", "newgroup"}}));
}

void TestCategoryJsonMapper::TestNameAndGroupDiff() {
    Category newc(orig);
    newc.name = "newname";
    newc.groupId = "newgroup";
    QCOMPARE(m.diff(orig, newc),
             QJsonObject({
                                 {"groupId", "newgroup"},
                                 {"name",    "newname"}
                         }));
}

void TestCategoryJsonMapper::TestToJson() {
    QCOMPARE(m.toJson(orig),
             QJsonObject({
                                 {"name",    "name1"},
                                 {"groupId", "groupId1"}
                         }));
}

void TestCategoryJsonMapper::TestFromJson() {
    auto cat = m.fromJson("id1", QJsonObject{
            {"name",    "name1"},
            {"groupId", "groupId1"}
    });
    QCOMPARE(cat.id, orig.id);
    QCOMPARE(cat.name, orig.name);
    QCOMPARE(cat.groupId, orig.groupId);
    QVERIFY(cat == orig);
}

void TestCategoryJsonMapper::TestPatch() {
    Category cat(orig);
    m.patch(cat, QJsonObject());
    QCOMPARE(cat.name, orig.name);
    QCOMPARE(cat.groupId, orig.groupId);
    m.patch(cat, {{"name", "new_name"}});
    QCOMPARE(cat.name, "new_name");
    QCOMPARE(cat.groupId, orig.groupId);
    m.patch(cat, {{"groupId", "new_groupId"}});
    QCOMPARE(cat.name, "new_name");
    QCOMPARE(cat.groupId, "new_groupId");
}


QTEST_MAIN(TestCategoryJsonMapper)

#include "test_CategoryMapper.moc"
