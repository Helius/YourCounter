#pragma once

#include <QtCore/QString>
#include <QtCore/QHash>
#include <QtCore/QDateTime>

/*
		"покупка" to Actions.Buying,
        "зачисление аванса" to Actions.AdvancePayment,
        "зачисление зарплаты" to Actions.Salary,
        "отмена покупки" to Actions.Refund,
        "перевод" to Actions.Transfer,
        "списание" to Actions.Paying,
        "оплата" to Actions.Paying,
        "выдача" to Actions.ATM
*/

enum class BankAction {
	Undefined = 0,
	Buying,
	AdvancedPayment,
	Salary,
	Refund,
	Transfer,
	Paying,
	ATM
};

struct ParseResult
{
	QString acc;
	BankAction action;
	int64_t amount;
	int64_t total;
	QString destination;
	QTime time;
	
	ParseResult() = default;
	
	ParseResult(
		const QString & acc,
		BankAction action,
		int64_t amount,
		int64_t total,
		const QString & destination,
		QTime time)
		: acc(acc)
		, action(action)
		, amount(amount)
		, total(total)
		, destination(destination)
		, time(time)
	{}
	
	bool operator==(const ParseResult & other) const
	{
		return acc == other.acc && action == other.action && amount == other.amount &&
			total == other.total && destination == other.destination && time == other.time;
	}
};

class SmsParser
{
public:
	static ParseResult parseSmsText(const QString & text);
	static int64_t parseAmount(const QString & text);

private:
};
