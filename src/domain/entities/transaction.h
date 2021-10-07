#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QString>
#include <QDateTime>
#include "interval.h"
#include "Category.h"

class Transaction {

public:
    QString id;
    float amount;
    QDateTime when;
    QString categoryId;
    QString who;
    QString comment;

    bool insideInterval(const Interval & interval) const
    {
        return interval.contains(when);
    }

    bool operator==(const Transaction & other) const {
        return id == other.id;
    }

    Transaction() = delete;
    Transaction(const QString & id, float amount, const QDateTime & when, const QString & categoryId, const QString & who = QString(), const QString & comment = QString())
            : id(id)
            , amount(amount)
            , when(when)
            , categoryId(categoryId)
            , who(who)
            , comment(comment)
    {
        Q_ASSERT(!id.isEmpty());
        Q_ASSERT(!categoryId.isEmpty());
        Q_ASSERT(abs(amount) > 0.001);
    }

//    Transaction(float amount, const QDateTime & when, const QString & categoryId, const QString & who = QString(), const QString & comment = QString())
//            : amount(amount)
//            , when(when)
//            , categoryId(categoryId)
//            , who(who)
//            , comment(comment)
//    {
//        Q_ASSERT(!categoryId.isEmpty());
//        Q_ASSERT(abs(amount) > 0.001);
//    }

};

using Transactions = std::vector<Transaction>;

#endif // TRANSACTION_H
