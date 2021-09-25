#ifndef ITRANSACTIONPROVIDER_H
#define ITRANSACTIONPROVIDER_H

#include <QObject>
#include <domain/entities/transaction.h>


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

using ITransactionProviderUnq = std::unique_ptr<ITransactionProvider>;

#endif // ITRANSACTIONPROVIDER_H
