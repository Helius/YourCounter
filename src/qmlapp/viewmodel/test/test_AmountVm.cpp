#include "../AmountVm.h"
#include <QtTest/QtTest>
class TestAmountVm : public QObject {

    Q_OBJECT

private slots:
    void TestAmountToString();
    void TestStringToAmount();
};

using namespace AmountVM;

void TestAmountVm::TestAmountToString()
{
    QCOMPARE(formatAmount(0), "0,00");
    QCOMPARE(formatAmount(1), "0,01");
    QCOMPARE(formatAmount(10), "0,10");
    QCOMPARE(formatAmount(1'11), "1,11");
    QCOMPARE(formatAmount(11'11), "11,11");
    QCOMPARE(formatAmount(111'11), "111,11");
    QCOMPARE(formatAmount(1111'11), "1\u00A0111,11");
    QCOMPARE(formatAmount(9999'99), "9\u00A0999,99");

    QCOMPARE(formatAmount(-1), "-0,01");
    QCOMPARE(formatAmount(-10), "-0,10");
    QCOMPARE(formatAmount(-1'11), "-1,11");
    QCOMPARE(formatAmount(-11'11), "-11,11");
    QCOMPARE(formatAmount(-111'11), "-111,11");
    QCOMPARE(formatAmount(-1111'11), "-1\u00A0111,11");
    QCOMPARE(formatAmount(-9999'99), "-9\u00A0999,99");
}

void TestAmountVm::TestStringToAmount()
{
    QCOMPARE(amountFromString("0,000"), 0);
    QCOMPARE(amountFromString("0,00"), 0);
    QCOMPARE(amountFromString("0,0"), 0);
    QCOMPARE(amountFromString("0"), 0);

    QCOMPARE(amountFromString("0,01"), 1);
    QCOMPARE(amountFromString("-0,01"), -1);

    QCOMPARE(amountFromString("1"), 100);
    QCOMPARE(amountFromString("-1"), -100);

    QCOMPARE(amountFromString("1,0"), 100);
    QCOMPARE(amountFromString("1,00"), 100);
    QCOMPARE(amountFromString("1,000"), 100);

    QCOMPARE(amountFromString("1,001"), 100);

    QCOMPARE(amountFromString("10,01"), 1001);
    QCOMPARE(amountFromString("10.01"), 1001);

    QCOMPARE(amountFromString("100,99"), 10099);
    QCOMPARE(amountFromString("999,99"), 99999);
    QCOMPARE(amountFromString("-999,99"), -99999);
    QCOMPARE(amountFromString("-999.99"), -99999);

    QCOMPARE(amountFromString("1 000,99"), 100099);
    QCOMPARE(amountFromString("10 000,99"), 1000099);

    QCOMPARE(amountFromString("10000,99"), 1000099);

    QCOMPARE(amountFromString("-12378,67"), -1237867);
    // hard cases
    QCOMPARE(amountFromString("567.06"), 56706);
}

QTEST_MAIN(TestAmountVm)

#include "test_AmountVm.moc"
