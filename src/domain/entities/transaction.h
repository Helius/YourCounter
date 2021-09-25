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
};

using Transactions = std::vector<Transaction>;

#endif // TRANSACTION_H
