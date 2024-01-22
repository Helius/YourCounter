#include "SmsParser.h"
#include <QtCore/QRegularExpression>

namespace {



} // namespace

ParseResult SmsParser::parseSmsText(const QString & text)
{
    static QRegularExpression re (R"~(([-\w\d]+)\s(\d\d:\d\d)\s([а-яА-Я\s]+)([\.\,\d\s]+)р(.*)\sБаланс:?\s([\d\s.,]+)р)~");

	QHash<QString, BankAction> actions = {
		{QString("покупка"), BankAction::Buying},
		{QString("зачисление аванса"), BankAction::AdvancedPayment},
		{QStringLiteral("зачисление зарплаты"), BankAction::Salary},
		{QStringLiteral("отмена покупки"), BankAction::Refund},
		{QStringLiteral("перевод"), BankAction::Transfer},
		{QStringLiteral("списание"), BankAction::Paying},
		{QStringLiteral("оплата"), BankAction::Paying},
		{QStringLiteral("выдача"), BankAction::ATM}
	};
	
	ParseResult result;

	QRegularExpressionMatch match = re.match(text);
	if (match.hasMatch()) {
		result.acc = match.captured(1);
		auto timeStrParts = match.captured(2).split(":");
		result.time = QTime(timeStrParts.at(0).toInt(), timeStrParts.at(1).toInt());
		auto act = match.captured(3).toLower().trimmed();
		result.action = actions.value(act);
		result.amount = parseAmount(match.captured(4));
		result.destination = match.captured(5).trimmed();
		result.total = parseAmount(match.captured(6));
	}
	return result;
}

int64_t SmsParser::parseAmount(const QString &text)
{
	static auto re = QRegularExpression("[,.]");
	auto str = text.simplified().trimmed();
	str.replace(" ", "");
	auto parts = str.trimmed().split(re);
	
	if (parts.size() > 1)
	{
		return parts.at(0).toLong() * 100 + parts.at(1).toInt();
	}
	else if (parts.size())
	{
		return parts.at(0).toLong() * 100;
	}
	return 0;
}
