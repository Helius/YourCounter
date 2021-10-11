#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QString>
#include <QDateTime>
#include <utility>
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
        Q_ASSERT(!this->id.isEmpty());
        Q_ASSERT(!this->categoryId.isEmpty());
        Q_ASSERT(abs(this->amount) > 0.001);
    }
    Transaction(const Transaction & other) = default;

};

using Transactions = std::vector<Transaction>;

#endif // TRANSACTION_H
