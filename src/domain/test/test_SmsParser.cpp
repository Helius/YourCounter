#include <QtTest/QtTest>
#include <usecases/smsParser/SmsParser.h>

class TestSmsParser : public QObject
{

	Q_OBJECT

private slots:
	void TestParseAmount();
	void TestParseAmount_data();
	
	void TestParseSms();
	void TestParseSms_data();
};

void TestSmsParser::TestParseAmount()
{
	QFETCH(QString, text);
	QFETCH(long, result);
	QCOMPARE(SmsParser::parseAmount(text), result);
}

void TestSmsParser::TestParseAmount_data()
{
	QTest::addColumn<QString>("text");
	QTest::addColumn<long>("result");

	QTest::newRow("1") << "123.12" << 12312L;
	QTest::newRow("2") << "1 123.12" << 112312L;
	QTest::newRow("3") << "1 123.00" << 112300L;
	QTest::newRow("4") << "1 123,10" << 112310L;
	QTest::newRow("5") << "1 123" << 112300L;
	QTest::newRow("6") << "1123" << 112300L;
}

void TestSmsParser::TestParseSms() 
{
	QFETCH(QString, text);
	QFETCH(ParseResult, result);
	auto r = SmsParser::parseSmsText(text);
	QCOMPARE(r.acc, result.acc);
	QCOMPARE(r.action, result.action);
	QCOMPARE(r.amount, result.amount);
	QCOMPARE(r.total, result.total);
	QCOMPARE(r.destination, result.destination);
	
}

void TestSmsParser::TestParseSms_data() 
{
	QTest::addColumn<QString>("text");
	QTest::addColumn<ParseResult>("result");

	QTest::newRow("покупка 1")
		<< "ECMC8283 16:22 Покупка 481.74р BYSTRONOM Баланс: 1941.46р"
		<< ParseResult("ECMC8283", BankAction::Buying, 48174, 194146, "BYSTRONOM", QTime(16, 22));

	QTest::newRow("покупка 2") << "MIR-2924 06:28 Покупка 1045.30р ALIEXPRESS Баланс: 16 412.95р"
							   << ParseResult(
									  "MIR-2924",
									  BankAction::Buying,
									  104530,
									  1641295,
									  "ALIEXPRESS",
									  QTime(06, 28));

	QTest::newRow("аванс") << "ECMC8283 05:36 Зачисление аванса 14258.75р Баланс: 33730.21р"
						   << ParseResult(
								  "ECMC8283",
								  BankAction::AdvancedPayment,
								  1425875,
								  3373021,
								  "",
								  QTime(05, 36));

	QTest::newRow("зп")
		<< "ECMC8283 05:57 Зачисление зарплаты 15 164р Баланс: 24611.89р"
		<< ParseResult("ECMC8283", BankAction::Salary, 1516400, 2461189, "", QTime(05, 57));

	QTest::newRow("отмена покупки")
		<< "ECMC8283 08:56 Отмена покупки 34.08р AZS OPTI Баланс: 20291.20р"
		<< ParseResult("ECMC8283", BankAction::Refund, 3408, 2029120, "AZS OPTI", QTime(8, 56));

	QTest::newRow("списание")
		<< "ECMC8283 08:23 списание 8143.86р за кредит Баланс: 29475.54р"
		<< ParseResult("ECMC8283", BankAction::Paying, 814386, 2947554, "за кредит", QTime(8, 23));

	QTest::newRow("оплата 1")
		<< "ECMC8283 06:07 Оплата 250р Автоплатёж рег. 250 мне ТЕЛЕ2 Баланс: 22352.95р"
		<< ParseResult("ECMC8283", BankAction::Paying, 25000, 2235295, "Автоплатёж рег. 250 мне ТЕЛЕ2", QTime(6, 07));

	QTest::newRow("оплата 2")
		<< "ECMC8283 01:13 Оплата 70р за уведомления. Следующее списание 17.04.23. Баланс 35462,23р"
		<< ParseResult("ECMC8283", BankAction::Paying, 7000, 3546223, "за уведомления. Следующее списание 17.04.23.", QTime(1, 13));

	QTest::newRow("перевод")
		<< "ECMC8283 07:27 перевод 50р Баланс: 36860.21р"
		<< ParseResult("ECMC8283", BankAction::Transfer, 5000, 3686021, "", QTime(7, 27));

	QTest::newRow("выдача")
		<< "ECMC8283 08:45 Выдача 1400р ATM 60027701 Баланс: 33289.40р"
		<< ParseResult("ECMC8283", BankAction::ATM, 140000, 3328940, "ATM 60027701", QTime(8, 45));
}

QTEST_MAIN(TestSmsParser)

#include "test_SmsParser.moc"
