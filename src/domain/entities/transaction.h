#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QString>
#include <QDateTime>

struct Transaction {
    Transaction(QString category, float amount, QDateTime when, QString coment = QString())
        :category(category)
        ,amount(amount)
        ,when(when)
        ,coment(coment)
    {}

    QString category;
    float amount;
    QDateTime when;
    QString coment;

    bool operator==(const Transaction & other) const {
        return category == other.category
               && amount == amount
               && when == when
               && coment == coment;
    }

    QString toString() const {
        return QString("%1 %2 %3 %4").arg(category).arg(amount).arg(when.toString()).arg(coment);

    }
};

using Transactions = std::vector<Transaction>;

#endif // TRANSACTION_H
