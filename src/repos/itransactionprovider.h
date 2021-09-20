#ifndef ITRANSACTIONPROVIDER_H
#define ITRANSACTIONPROVIDER_H

#include <QObject>
#include <entities/transaction.h>

class ITransactionProvider : public QObject
{
        Q_OBJECT

public:
        virtual void loadTransactions() = 0;
signals:
        void transactionReady(Transactions transaction);

public:
        virtual ~ITransactionProvider() = default;
        using QObject::QObject;

};

#endif // ITRANSACTIONPROVIDER_H
