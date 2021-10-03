#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QString>
#include <QDateTime>
#include "interval.h"

struct Transaction {
    Transaction() = delete;
    Transaction(QString category, float amount, QDateTime when, QString who = QString(), QString coment = QString())
        : category(category)
        , amount(amount)
        , when(when)
        , who(who)
        , coment(coment)
    {}

    QString category;
    float amount;
    QDateTime when;
    QString who;
    QString coment;

    bool insideInterval(const Interval & interval) const
    {
        return interval.contains(when);
    }

    bool operator==(const Transaction & other) const {
        return category == other.category
               && amount == other.amount
               && when == other.when
               && coment == other.coment
               && who == other.who;
    }

    QString toString() const {
        return QString("%1 %2 %3 %4 %5").arg(category).arg(who).arg(amount).arg(when.toString()).arg(coment);

    }
};

using Category = QString;
using Categories = std::vector<QString>;
using Transactions = std::vector<Transaction>;

#endif // TRANSACTION_H
