#include "../simplecrypt.h"
#include <QtTest/QtTest>

class TestSimplecrypt : public QObject {

    Q_OBJECT

private slots:
    void TestStringCrypt();
};

void TestSimplecrypt::TestStringCrypt()
{
    QString text = "Some text 123";
    SimpleCrypt crypt(0x123098120398);
    QString enc = crypt.encryptToString(text);
    QVERIFY(text != enc);
    QCOMPARE(text, crypt.decryptToString(enc));
}

QTEST_MAIN(TestSimplecrypt)

#include "test_simplecrypt.moc"